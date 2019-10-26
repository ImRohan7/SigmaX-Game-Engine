#pragma once
#include "../Actor/GameObject.h"


// Intefcae class (Interface Inheritance)
class IGameObjectController
{
public:
	//pure virtual function. Forces subclass to define their own methods.
	virtual void SetGameObject(GameObject * i_pObject) = 0; 
	virtual void UpdateGameObject() = 0;
};