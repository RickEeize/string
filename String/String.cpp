#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <string.h>

size_t string::_string_count = 0;
/*
	��������� �� ���� ����� ���������� ���������� ������ � �������� ������
*/
void string::allocate_and_cpy(size_t new_max_length)
{
	if (_max_length == new_max_length) return;
	char* tmp = new char[_length + 1]; // �������� ������
	strcpy(tmp, _str);
	delete _str;
	_str = new char[new_max_length + 1]; // ��������� ������� ������
	strcpy(_str, tmp);
	delete[] tmp;
}
/*
	�����������
*/
string::string()
{
	_string_count++;
	_max_length = initial_max_length;
	_length = 0;
	_str = new char[_max_length + 1];
	*_str = '\0';
}
/*
	�����������
*/
string::string(const char* str)
{
	_string_count++;
	_max_length = initial_max_length;
	size_t len = strlen(str);
	while (len > _max_length) _max_length *= 2; // ���� ����� ����������� ������ ������ ��� ���������� ������ 
	_length = len;
	_str = new char[_max_length + 1]; 
	strcpy(_str, str);
}
/*
	�����������
*/
string::string(const string& str)
{
	_string_count++;
	_max_length = str._max_length;
	_length = str._length;
	_str = new char[_max_length];
	strcpy(_str, str._str);
}
/*
	����������
*/
string::~string()
{
	_string_count--;
	delete[] _str;
}

/*
	��������� �������� ��������� � ����� ������
*/
void string::append(const char* str)
{
	size_t len = strlen(str);
	if (len + _length > _max_length){ // ������ ���� ��������� ����� ������ ���������� ������
		while (len + _length > _max_length) _max_length *= 2; // ����������� ���������� ������
		allocate_and_cpy(_max_length);
		char* tmp = _str + _length; // ������ ��������� �� ����� ������� ������
		for (size_t i = 0; i < len; i++) { //���������� �������� ������ � ����� �������
			*(tmp + i) = *(str + i);
		}
		_length += len;
		*(_str + _length) = '\0';
	}
	else {
		char* tmp = _str + _length; // ������ ��������� �� ����� ������� ������
		for (size_t i = 0; i < len; i++) { // ���������� �������� ������ � ����� �������
			*(tmp + i) = *(str + i);
		}
		_length += len;
		*(_str + _length) = '\0';
	}
}
/*
	��������� �������� ��������� � ����� ������
*/
void string::append(const string& str)
{
	append(str._str); // �������� ���������� ����� ��������� char*
}
/*
	����� ������
*/
size_t string::length() const
{
	return _length;
}
/*
	������ ���������� ������
*/
size_t string::max_length() const
{
	return _max_length;
}
/*
	������� ������
*/
void string::clear()
{
	_length = 0;
	delete _str; // �������� ������
	_str = new char[_max_length + 1]; // ��������� ������ ��� �����
	*_str = '\0';
}
/*
	�������� �� �������
*/
bool string::empty() const
{
	return _length == 0;
}
/*
	��������� ������ ��������
*/
void string::assign(const char* str)
{
	_length = strlen(str);
	while (_length > _max_length) _max_length *= 2; // ���������� ������������ ������, ���� �����
	allocate_and_cpy(_max_length); // ��������� ���� ����� ������
	strcpy(_str, str); // ����������� �����
}
/*
	��������� ������ ��������
*/
void string::assign(const string& str)
{
	assign(str._str); // �������� ���������� �����, ��������� char*
}
/*
	������� ������ ������ �������
*/
void string::insert(size_t pos, const char* str)
{
	if (pos > _length - 1) throw str_exception("incorrect position"); // �������� ������������ ���������� ������
	size_t len = strlen(str);
	while (len + _length > _max_length) _max_length *= 2; // ���������� ������������ ������ 
	allocate_and_cpy(_max_length); // ��������� ���� ����� ������

	char* second = new char[_length - pos + 1]; // ����� ��� ������ �������� ������� ������
	strcpy(second, _str + pos); // ����������� ������ �������� � �����
	strcpy(_str + pos, str); // ����������� ���������� ������ �� ����� �����
	strcpy(_str + pos + strlen(str), second); // ���������� ������ �������� ������� � ������ ����� ������ ���������
	delete[] second; // �������� ������
}
/*
	������� ������ ������ �������
*/
void string::insert(size_t pos, const string& str)
{
	insert(pos, str._str); // �������� ���������� �����, ��������� char*
}
/*
	����� ������� ������� ��������� ���������
*/
size_t string::find(const char* str) const
{
	size_t len = strlen(str);
	for (size_t i = 0, j = 0; i < _length; i++, j = 0) { // ������ �� �������� ������� ������
		while (*(_str + i + j) == *(str + j)) j++; // ���� ������� ������ � ��������� ��������� ������� �������������
		if (j >= len) return i; // ���� ������� ����� ����� ���������, �� �� ����� ������ ���������
	}
	throw str_exception("no such substring"); // ���� ������ �� ����� ����������� ��������� �� ����
}
/*
	����� ������� ������� ��������� ���������
*/
size_t string::find(const string& str) const
{
	return find(str._str); // �������� ���������� �����, ��������� char*
}
/*
	��������� ��������� �� ������� ������
*/
string string::substr(size_t pos_begin, size_t length) const
{
	if (pos_begin + length > _length) throw str_exception("incorrect parameters"); // �������� ������������ ���������� ������
	char* str = new char[length + 1]; // ��������� ������ ��� ���������
	for (size_t i = 0; i < length; i++) // ��������������� �������� ������� � ���������
		*(str + i) = *(_str + pos_begin + i); 
	*(str + length) = '\0';
	string s(str);
	delete[] str;
	return s;

}
/*
	����������� ��������� �� char ��� ������� ������ 
*/
char* string::c_str() const
{
	char* str = new char[_length + 1];
	strcpy(str, _str);
	return str;
}
/*
	����� �� �����
*/
void string::print() const
{
	std::cout << _str << std::endl;
}

size_t string::get_string_count()
{
	return _string_count;
}

string string::operator+(const char* str)
{
	string s;
	s.assign(this->_str);
	s.append(str);
	return string(s);
}

string string::operator+(const string& str)
{
	return *this + str._str;
}

string string::operator-(const char* str)
{
	try {
		size_t len = strlen(str);
		size_t pos = this->find(str);
		string s;
		s.assign(this->substr(0, pos));
		s.append(this->substr(pos + len, _length - pos - len));
		return s;
	}
	catch (const char*) {
		return *this;
	}
}

string string::operator-(const string& str)
{
	return *this - str._str;
}

char& string::operator[](const size_t pos)
{
	return *(_str + pos);
}

string& string::operator=(const char* str)
{
	if (strcmp(this->_str, str) != 0) this->assign(str);
	return *this;
}

string& string::operator=(const string& str)
{
	if (strcmp(this->_str, str._str) != 0) this->assign(str);
	return *this;
}

void string::write_binary(std::ofstream& out)
{
	out.write((char*)&_max_length, sizeof(_max_length));
	out.write((char*)&_length, sizeof(_length));
	out.write(_str, (std::streamsize)_length + 1);
}

void string::read_binary(std::ifstream& in)
{
	in.read((char*)&_max_length, sizeof(_max_length));
	in.read((char*)&_length, sizeof(_length));
	delete _str;
	_str = new char[_length + 1];
	in.read(_str, (std::streamsize)_length + 1);
}

std::ostream& operator<<(std::ostream& out, const string& str)
{
	out << str._str;
	return out;
}

std::istream& operator>>(std::istream& in, string& str)
{
	char* buf = new char[128];
	in.getline(buf, 128);
	str.assign(buf);
	delete[] buf;
	return in;
}

