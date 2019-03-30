#pragma once
#include "stdafx.h"
#include "IGameObjectController.h"
#include "stdlib.h"
#include "Point2D.h"
#include "MyString.h"

class ZombieController : public IGameObjectController
{
public:

	void SetGameObject(GameObject * i_pObject) override { m_pObject = i_pObject; }
	void SetFocusObject(GameObject * i_pFocus) { m_pFocus = i_pFocus; }

	void UpdateGameObject() override
	{
		lifetime = lifetime + rand() % 3 - 1;
		Point2D Direction;
		if (m_pFocus)
		{
			Direction = m_pFocus->GetPosition() - m_pObject->GetPosition();
			Direction.coolDown();
		}
		else
		{
			Direction = randomDirectionGenerator();
		}
		m_pObject->SetPosition(m_pObject->GetPosition() + Direction);
	}

	Point2D randomDirectionGenerator()
	{
		Point2D tempRand(0.0f, 0.0f);
		tempRand.Rand_Shuffle(-5, 5);
		return tempRand;
	}

	char* getName() {
		return mName.getName();
	}

	Point2D getPos() {
		return m_pObject->GetPosition();
	}

	int getLife() { return lifetime; }

private:
	GameObject * m_pObject;
	GameObject * m_pFocus;
	MyString mName;
	int lifetime = 0;
};