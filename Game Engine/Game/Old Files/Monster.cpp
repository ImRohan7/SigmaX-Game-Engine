
#include "Monster.h"
#include "iostream"
#include "Math.h"


Monster::Monster()
{

}

Monster::~Monster()
{
	if (name != NULL) {
		delete[] name;
	}
}
