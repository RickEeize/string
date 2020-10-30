#include <iostream>
#include "Tests.h"
#include "String.h"

/*
	≈сли не выкинулось исключение и полученые данные совпали с ожидаемыми возвращаем true иначе false
*/

bool insert_test(insert_data& d) { 
	try {
		d.s.insert(d.pos, d.substr);
	}
	catch (const char* ex) { return false; }
	
	return strcmp(d.s.c_str(), d.expected.c_str()) == 0;
}

bool find_test(find_data& d) { // "123456789" find("3456")
	size_t ans;
	try
	{
		ans = d.s.find(d.substr);
	}
	catch (const char* ex)
	{
		return false;
	}
	return ans == d.expected;
}

bool substr_test(substr_data& d)
{
	string s;
	try
	{
		s.assign(d.s.substr(d.pos, d.length));
	}
	catch (const char* ex)
	{
		return false;
	}
	return strcmp(s.c_str(), d.expected.c_str()) == 0;
}
