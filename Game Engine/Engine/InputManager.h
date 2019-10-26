#pragma once
#include "iostream"
#include "ConsolePrint.h"

enum KeyId
{
	W = 'W',
	S = 'S',
	A = 'A',
	D = 'D',
	Q = 'Q',
	Space = '20',
	num_1 = '1',
	num_2 = '2',
	num_3 = '3'
};


namespace InputManager {

	void InitService();
	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);

	bool getKeyDown(char i_Key); // WHile pressed state
	bool getKeyUP(char i_key); // WHile UP(normal) state
	
};