#pragma once
#include "iostream"

int m_countLength(char string[50]);

class MyString {

public:
	MyString();

	// Get
	char* getName() const { return m_name; }
	int getLength() const { return m_length; }

	// Destructor
	~MyString();

private:
	int m_length;
	char * m_name = new char[m_length];
};

