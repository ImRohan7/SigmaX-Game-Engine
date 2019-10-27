#include "Player.h"
#include "Map.h"
#include "iostream"
#include "assert.h"
#include "Mystring/MyString.h"

Player::Player()
{
	/*char pos;
	char temp[50];

	std::cout << "Enter the name of the Player (not more than 50 characters) : \n";
	std::cin >> temp;
	
	assert(temp != NULL);

	name = new char[m_countLength(temp)+1];
	memcpy(name, temp, m_countLength(temp) + 1);

	std::cout << "Enter the initial position for player to start on the map. \n"
		"There will be 3 positions. choose one of them \n"
		"Press any of the following three keys. \n"
		"\n G - Top  H - middle  J - End ";
	std::cin >> pos;
	
	if (pos == 'G' || 'g') {  position.x(5); position.y(10); }
	if (pos == 'H' || 'h') {  position.x(10); position.y(12); }
	if (pos == 'J' || 'j') {  position.x(18); position.y(16); }
	else { std::cout << std::endl<< "Wrong entry"; }*/
}

Player::~Player()
{
	std::cout << "\nDeleting player";
	if (name != NULL) {
		delete[] name;
		
	}
}
