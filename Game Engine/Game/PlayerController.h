#pragma once
#include "IGameObjectController.h"
#include "MyString.h"
#include "Vector2.h"

class PlayerController : public IGameObjectController
{

public:
	void SetGameObject(GameObject* i_pObject) override
	{
		m_pObject = i_pObject;
	}

	GameObject* getGameOject()
	{
		return m_pObject;
	}

	void UpdateGameObject() override
	{
		if (m_pObject)
		{
			Vector2 Direction = GetDirectionFromUserInput();
			m_pObject->SetPosition(m_pObject->GetPosition() + Direction);
		}
	}

	Vector2 GetDirectionFromUserInput()
	{
		Vector2 temp(0.0f, 0.0f);
		char dir;
		std::cout << "Where you want to move ? \n";
		std::cout << "	W: UP		S: DOWN		A: LEFT		D: RIGHT	\n";
		std::cout << "Enter your movement:";
		std::cin >> dir;

		switch (dir)
		{
		case 'W':
		case 'w':
			temp.x(0.0f);
			temp.y(1.0f);
			return temp;
			break;

		case 'S':
		case 's':
			temp.x(0.0f);
			temp.y(-1.0f);
			return temp;
			break;

		case 'A':
		case 'a':
			temp.x(-1.0f);
			temp.y(0.0f);
			return temp;
			break;

		case 'D':
		case 'd':
			temp.x(1.0f);
			temp.y(0.0f);
			return temp;
			break;

		default:
			std::cout << "\n Wrong Entry I think you are confused let me play for you..."
				"Choosing a default direction";
			temp.x((float)(rand() % 1 + 3));
			temp.y((float)(rand() % 1 + 3));
			return temp;
			break;
		}
	}

	char* getName() {
		return mName.getName();
	}

	Vector2 getPos() { return m_pObject->GetPosition(); }

private:
	GameObject * m_pObject;
	MyString mName;
};