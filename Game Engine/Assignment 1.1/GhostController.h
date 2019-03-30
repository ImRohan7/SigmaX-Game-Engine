#pragma once
#include "stdafx.h"
#include "IGameObjectController.h"
#include "Point2D.h"

// Ghost will haunt either Player or Monster. Whoever is caught, becomes ghost. Probably for sometime or forever...who knmows. There is no way to escape !!!

class GhostController : public IGameObjectController
{
public:

	void SetGameObject(GameObject * i_pObject) override { m_pObject = i_pObject; }
	void setToHaunt(GameObject * i_phaunt) { m_pHaunt = i_phaunt; }

	void UpdateGameObject()
	{
		if (m_pHaunt)
		{
			m_pObject->SetPosition(m_pHaunt->GetPosition() + Point2D::Unit);
		}
		else
		{
			Point2D temp(5.6f, 6.88f);
			m_pObject->SetPosition(temp);
		}
	}

	Point2D randomDirectionGenerator()
	{
		Point2D tempRand(0.0f, 0.0f);
		tempRand.Rand_Shuffle(-5, 5);
		return tempRand;
	}

private:
	GameObject * m_pObject;
	GameObject * m_pHaunt;
};