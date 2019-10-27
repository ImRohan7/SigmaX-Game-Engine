#pragma once
#include "iostream"

/* Very simple string class with limited functionalities
 *	for my Engine to use
*/


class MyString {

public:

	MyString();
	MyString(const char *);
	MyString(const MyString&);
	
	MyString operator=(const MyString&);
	MyString operator=(const char*);

	bool operator==(const MyString&);
	bool operator==(const char*);

	// Get
	inline char* getName() const { return data; }
	inline int getLength() const { return length; }

	// Destructor
	~MyString();

private:
	int length;
	char * data;
};

