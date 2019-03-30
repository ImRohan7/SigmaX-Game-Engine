#pragma once
#include "GameObject.h"
#include "SmartPtr.h"
#include "WeakPtr.h"
#include "GLib.h"

namespace Engine {
	namespace Renderer {
		
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	}
}

class Renderable
{

public:
	
	// Constructor
	Renderable(const SmartPtr<GameObject> i_Obj, GLib::Sprites::Sprite* i_sprite):
		m_pObject(i_Obj), m_pSprite(i_sprite)
	{}

	// Draw 
	// ??? : Do I want to move this to namespace instaead of class
	void Draw();

	~Renderable();

private:

	WeakPtr<GameObject> m_pObject;
	GLib::Sprites::Sprite * m_pSprite;

};