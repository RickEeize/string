#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <ctime>

class todo_string : public string {

public:
	todo_string();
	todo_string(const char* task);
	void start();
	void finish();
	bool finished() const;
	bool started() const;
	time_t when_started() const;
	time_t when_finished() const;

	todo_string& operator=(const todo_string& other);
	todo_string& operator=(const char* other);

	friend std::ostream& operator<<(std::ostream& out, const todo_string& task);
	friend std::istream& operator>>(std::istream& in, todo_string& task);

private:
	time_t _start;
	time_t _end;
};