#pragma once
#include "String.h"

/*
	Структуры - заготовки для данных передаваемых функциям тестам
*/

struct insert_data {
	size_t pos;
	string substr;
	string s;
	string expected;
};

struct find_data {
	string substr;
	string s;
	size_t expected;
};

struct substr_data {
	size_t pos;
	size_t length;
	string s;
	string expected;
};


bool insert_test(insert_data& d);
bool find_test(find_data& d);
bool substr_test(substr_data& d);