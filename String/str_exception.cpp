#define _CRT_SECURE_NO_WARNINGS
#include "str_exception.h"

str_exception::str_exception() :
	_message(nullptr)
{
	_message = (char*)"something gone wrong"; // ������� ���������
}

str_exception::str_exception(const char* mes) :
	_message(nullptr)
{
	_message = new char[strlen(mes) + 1]; // ���������� ���������
	strcpy(_message, mes);
}

const char* str_exception::what() const // �������, ��� �� ���
{
	return _message;
}
