#include "MyString/MyString.h"


// default
MyString::MyString()
{
	data = nullptr;
	length = 0;
}

// string
MyString::MyString(const char* i_string)
{
	int n = 0;
	while (i_string[n] != '\0') {
		n++;
	}

	n += 1; // count the \0
	data = new char[n];
	length = n;
	memcpy(data, i_string, n);
}

// copy ()
MyString::MyString(const MyString& i_oth)
{
	length = i_oth.length;
	data = new char[length];
	memcpy(data, i_oth.data, length);
}

// copy =
MyString MyString::operator=(const MyString& i_other)
{
	data = i_other.data;		// note the difference between 
	length = i_other.length;	//copy() and copy=

	return *this;
}


// destructor
MyString::~MyString()
{
	if (data != NULL)
	{
		delete[] data;
		data = nullptr;
	}
}