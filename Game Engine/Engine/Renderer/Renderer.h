#pragma once
#include "../Actor/GameObject.h"
#include "../PointerManagment/SmartPtr.h"
#include "../PointerManagment/WeakPtr.h"
#include "GLib.h"

namespace Engine {
	namespace Renderer {
		
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename, float &, float &);
		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	}
}

class Renderable
{

public:
	
	// Constructor
	Renderable(const SmartPtr<GameObject> i_Obj, GLib::Sprites::Sprite* i_sprite, Vector2 i_Dim):
		m_pObject(i_Obj), m_pSprite(i_sprite), m_Dimesnions(i_Dim)
	{}

	~Renderable();

	GLib::Sprites::Sprite *getSprite() { return m_pSprite; }
	Vector2 getSpriteDimensions() { return m_Dimesnions; }

	WeakPtr<GameObject> getObj() { return m_pObject; }


private:

	WeakPtr<GameObject> m_pObject;
	GLib::Sprites::Sprite * m_pSprite;	// Create a struct
	Vector2 m_Dimesnions; // Width, Height;
};