#pragma once
#include "GameObject.h"


// Intefcae class (Interface Inheritance)
class IGameObjectController
{
public:
	//pure virtual function. Forces subclass to define their own methods. Whichver class extend this has to implemet this methods !!!
	virtual void SetGameObject(GameObject * i_pObject) = 0; 
	virtual void UpdateGameObject() = 0;
};