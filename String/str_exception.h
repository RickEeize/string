#pragma once
#include <iostream>

class str_exception {

public:
	str_exception();
	str_exception(const char* mes);

	const char* what() const;
private:
	char* _message;
};