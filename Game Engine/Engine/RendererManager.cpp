#include "RendererManager.h"
#include <vector>

#define PI 3.14159265
#define	D ( PI / 180.0 )				// for radian to degree


namespace Engine {
	namespace Renderer {
		void RendererManager::Draw()
		{
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();

			std::vector<Renderable*> r = Engine::getRenderables();
			
			for (unsigned i = 0; i < r.size(); i++)
			{
				Renderable * toDraw = r.at(i);
				WeakPtr<GameObject> m_pObject = toDraw->getObj();


					if (m_pObject)
					{
						SmartPtr<GameObject> _tempObject = m_pObject.AquireOwnership();

						GLib::Point2D pos = { _tempObject->m_Physics->getPosition().x(),  _tempObject->m_Physics->getPosition().y() };
						float RotX = _tempObject->m_Physics->getRotationZ();
						// if underlying pointer is available draw it
						float Radians = RotX * D;
						GLib::Sprites::RenderSprite(*toDraw->getSprite(), pos, Radians);
					}
					else
					{
						// Need to destroy this Renderable since the GameObject has been released
					}

			}

			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}
	}
}
