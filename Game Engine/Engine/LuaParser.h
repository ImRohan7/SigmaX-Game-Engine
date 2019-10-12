#pragma once

#include "src/lua.hpp"
#include "src/lua.h"
#include "src/lualib.h"
#include "src/lauxlib.h"
#include "src/luaconf.h"
#include "SmartPtr.h"
#include "Engine.h"


#define FPath "../Data/"

namespace Engine {

	namespace
	{
		// helper functions
		void get_2DInfo(lua_State* i_state, const char* i_key, float* val);
	}

	class LuaParser {
	public:

		LuaParser()
		{}

		// initialize object insatnce from reading lua file and add instance to the engine
		static bool createObject_and_addToScene(SmartPtr<GameObject> i_obj, const char* i_file)
		{
			// Create a State
			lua_State* L_state = luaL_newstate();
			assert(L_state);

			luaL_openlibs(L_state); // open Libs

			size_t 		sizeFile = 0;
			uint8_t* pFileContents = static_cast<uint8_t*>(Engine::Renderer::LoadFile(i_file, sizeFile));

			if (pFileContents && sizeFile)
			{
				int  result = 0;

				// Necessary stuff to process our data
				result = luaL_loadbuffer(L_state, reinterpret_cast<char*>(pFileContents), sizeFile, nullptr);
				assert(result == 0);

				result = lua_pcall(L_state, 0, 0, 0);
				assert(result == 0);

				result = lua_getglobal(L_state, "Player");
				assert(result == LUA_TTABLE);

				lua_pushstring(L_state, "Name");

				int type = lua_gettable(L_state, -2);
				assert(type == LUA_TSTRING);

				const char* _name = lua_tostring(L_state, -1);
				lua_pop(L_state, 1);

				float* getter = new float[2];  // DELETE THIS !!!


				get_2DInfo(L_state, "Position", getter);
				Vector2 _pos(getter[0], getter[1]);

				get_2DInfo(L_state, "Velocity", getter);
				Vector2 _velocity(getter[0], getter[1]);

				

				lua_pushstring(L_state, "Physics");

				// getting mass from table Physics = { mass = xx.yy }	
				type = lua_gettable(L_state, -2);
				assert(type == LUA_TTABLE); // 5

				//lua_pushstring(L_state, "mass");
				lua_pushnil(L_state);
				lua_next(L_state, -2);

				int t1 = lua_type(L_state, -2);
				int t2 = lua_type(L_state, -1);
				assert(t1 == LUA_TSTRING);  // 4

				float _mass;
				//assert(t2 == LUA_TNUMBER); // 3
				if (t2 == LUA_TNUMBER)
				{
					_mass = static_cast<float>(lua_tonumber(L_state, -1));
				}
				else
				{
					_mass = 25.0f;
				}
				lua_pop(L_state, 2);
				// getting drag from table Physics = { drag = {,}}
				get_2DInfo(L_state, "drag", getter);
				Vector2 _drag(getter[0], getter[1]);

				lua_pop(L_state, 1);

				// Init OBJECT AND Create PHYSICS Component--------------------
				// ============================================
		
				i_obj->setFromFile(_name);	// init name for now
				Engine::push_ObjectToList(i_obj); // push to engine

				PhysicsComponent* pComp = new PhysicsComponent(_pos, _velocity, _mass, _drag);
				Engine::push_PhysicsComponentToList(pComp);
				i_obj->m_Physics = pComp;

				// RENDERER

				lua_pushstring(L_state, "Renderer");

				// getting path from table Renderer = { mass = xx.yy }	
				type = lua_gettable(L_state, -2);
				assert(type == LUA_TTABLE); // 5

				lua_pushnil(L_state);
				lua_next(L_state, -2);

				t1 = lua_type(L_state, -2);
				t2 = lua_type(L_state, -1);
				assert(t1 == LUA_TSTRING);  // 4
				assert(t2 == LUA_TSTRING); // 3

				const char* path = lua_tostring(L_state, -1);

				// getting dimensions
				float width, height;
				GLib::Sprites::Sprite* pGoodGuy = Engine::Renderer::CreateSprite(path, width, height);
				Vector2 Dimensions(width, height);
				
				// Create Rendering Component-------------------------------------------------
				Renderable* pRenderer = new Renderable(i_obj, pGoodGuy, Dimensions);

				if (pRenderer)
					Engine::push_RendererToList(pRenderer);
				
				// Set AABB
				i_obj->setAABB(Dimensions);

				delete [] getter;


				// close state
				lua_close(L_state);

				return true;

			}
			else
			{
				DEBUG_PRINT("Error Loading a file");
				assert(false);

				return false;
			}
		}

		// =========
		// OLD
		// =======
		// Parse .lua file and creates GameObject, PhysicsComponents and RendererComponent
		static SmartPtr<GameObject> createObject(const char* i_file)
		{
			// Create a State
			lua_State * L_state = luaL_newstate();
			assert(L_state);

			luaL_openlibs(L_state); // open Libs

			size_t 		sizeFile = 0;
			uint8_t * 	pFileContents = static_cast<uint8_t*>(Engine::Renderer::LoadFile(i_file, sizeFile));

			if (pFileContents  && sizeFile)
			{
				int  result = 0;

				// Necessary stuff to process our data
				result = luaL_loadbuffer(L_state, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
				assert(result == 0);

				result = lua_pcall(L_state, 0, 0, 0);
				assert(result == 0);

				result = lua_getglobal(L_state, "Player");
				assert(result == LUA_TTABLE);

				lua_pushstring(L_state, "Name");

				int type = lua_gettable(L_state, -2);
				assert(type == LUA_TSTRING);

				const char * _name = lua_tostring(L_state, -1);
				lua_pop(L_state,1);

				float * getter = new float[2];  // DELETE THIS !!!
				

				get_2DInfo(L_state, "Position", getter);
				Vector2 _pos(getter[0],getter[1]);

				get_2DInfo(L_state, "Velocity", getter);
				Vector2 _velocity(getter[0], getter[1]);

			// create Player	
				SmartPtr<GameObject> player;// = GameObject::Create(_pos, _name, _velocity);
				Engine::push_ObjectToList(player);

				lua_pushstring(L_state, "Physics");
			
				// getting mass from table Physics = { mass = xx.yy }	
				type = lua_gettable(L_state, -2);
				assert(type == LUA_TTABLE); // 5

				//lua_pushstring(L_state, "mass");
				lua_pushnil(L_state);
				lua_next(L_state, -2);
				
				int t1 = lua_type(L_state, -2);
				int t2 = lua_type(L_state, -1);
				assert(t1 == LUA_TSTRING);  // 4
				
				float _mass;
				//assert(t2 == LUA_TNUMBER); // 3
				if (t2 == LUA_TNUMBER)
				{
					 _mass = static_cast<float>(lua_tonumber(L_state, -1));
				}
				else
				{
					_mass = 25.0f;
				}
				lua_pop(L_state, 2);
			// getting drag from table Physics = { drag = {,}}
				get_2DInfo(L_state, "drag", getter);
				Vector2 _drag(getter[0],getter[1]);

				lua_pop(L_state, 1);

				// Create Physics Component
				PhysicsComponent* pComp;// = new PhysicsComponent(player, _mass, _drag);
				Engine::push_PhysicsComponentToList(pComp);
			
			// RENDERER
				
				lua_pushstring(L_state, "Renderer");

				// getting path from table Renderer = { mass = xx.yy }	
				type = lua_gettable(L_state, -2);
				assert(type == LUA_TTABLE); // 5

				lua_pushnil(L_state);
				lua_next(L_state, -2);

				t1 = lua_type(L_state, -2);
				t2 = lua_type(L_state, -1);
				assert(t1 == LUA_TSTRING);  // 4
				assert(t2 == LUA_TSTRING); // 3

				const char * path = lua_tostring(L_state, -1);

				// getting dimensions
				float width, height;
				GLib::Sprites::Sprite * pGoodGuy = Engine::Renderer::CreateSprite(path, width, height);
				Vector2 Dimensions(width,height);
				Renderable *pRenderer = new Renderable(player, pGoodGuy, Dimensions);
				
				if(pRenderer)
					Engine::push_RendererToList(pRenderer);
				// Set AABB
				player->setAABB(Dimensions);


				delete [] getter;
			
				// close state
				lua_close(L_state);
				// return SmartPtr to GameObject
				return player;

			}
			else
			{
				DEBUG_PRINT("Error Loading a file");
				assert(false);

				return nullptr;
			}
		}

		

	};

	namespace 
	{

		void get_2DInfo(lua_State* i_state, const char* i_key, float* val)
		{
			lua_pushstring(i_state, i_key);
			int type = lua_gettable(i_state, -2);
			assert(type == LUA_TTABLE);

			lua_pushnil(i_state);
			int i = 0;

			while (lua_next(i_state, -2) != 0) // getting Position(2D)
			{
				int t1 = lua_type(i_state, -2);
				int t2 = lua_type(i_state, -1);

				assert(t2 == LUA_TNUMBER);

				val[i] = (float)lua_tonumber(i_state, -1);
				lua_pop(i_state, 1);
				i++;
				if (i > 2)
				{
					DEBUG_PRINT("Overflowing while searching for 2D");
					assert(false);
				}
			}
			lua_pop(i_state, 1);
		}
	}
}