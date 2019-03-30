#include "MyString.h"

MyString::MyString(const char * i_string) {
		
		m_length = m_countLength_(i_string) + 1;
		m_name = new char[m_length]; // OOOOOooo.. solvinf the 1st sem stupid error
		
		memcpy(m_name, i_string, m_length);
}

//MyString::MyString() {
//	char temp[50];
//	std::cout << "Enter the name : \n";
//	std::cin >> temp;
//	m_length = m_countLength(temp) + 1;
//	memcpy(m_name, temp, m_length);
//}

MyString::~MyString()
{
	if (m_name != NULL)
	{
		delete[] m_name;
	}
}


int m_countLength_(const char * string)
{
	int length = 0;

	while (string[length] != '\0') {
		length++;
	}

	return length;
}

int m_countLength(char string[50])
{
	int length = 0;

	while (string[length] != '\0') {
		length++;
	}

	return length;
}