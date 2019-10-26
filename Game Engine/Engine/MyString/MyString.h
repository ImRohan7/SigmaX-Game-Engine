#pragma once
#include "iostream"

int m_countLength(char string[50]);
int m_countLength_(const char *);

class MyString {

public:
	MyString(const char *);

	// Get
	char* getName() const { return m_name; }
	int getLength() const { return m_length; }

	// Destructor
	~MyString();

private:
	int m_length;
	char * m_name; // = new char[m_length]; << This was wrong for the Entire First Semester
					// Should have listened to joe and implemented guardbanding 
};

