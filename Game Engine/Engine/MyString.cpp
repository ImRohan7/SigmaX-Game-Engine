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
	length = n-1;
	memcpy(data, i_string, n);
}

// copy ()
MyString::MyString(const MyString& i_oth)
{
	length = i_oth.length;
	data = new char[length+1];
	memcpy(data, i_oth.data, length+1); // remember the '\0'
}

// copy =
MyString MyString::operator=(const MyString& i_other)
{
	data = i_other.data;		// note the difference between 
	length = i_other.length;	//copy() and copy=

	return *this;
}

// copy = char*
MyString MyString::operator=(const char* i_char)
{
	MyString tmp(i_char);
	length = tmp.length;
	data = new char[length+1];
	memcpy(data, tmp.data, length+1);

	return *this;
}

// ==
bool MyString::operator==(const MyString& i_other)
{
	if (length != i_other.length)
	{
		return false;
	}

	for (int i = 0; i <= length; i++)
	{
		if (data[i] != i_other.data[i])
		{
			return false;
		}
	}

	return true;
}

// == char*
bool MyString::operator==(const char* c)
{
	MyString tmp(c);
	return (*this == tmp);
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