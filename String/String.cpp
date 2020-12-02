#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <string.h>

size_t string::_string_count = 0;
/*
	Принимает на вход новое количество выделенной памяти и копирует строку
*/
void string::allocate_and_cpy(size_t new_max_length)
{
	if (_max_length == new_max_length) return;
	char* tmp = new char[_length + 1]; // создание буфера
	strcpy(tmp, _str);
	delete _str;
	_str = new char[new_max_length + 1]; // выделение бОльшей памяти
	strcpy(_str, tmp);
	delete[] tmp;
}
/*
	Конструктор
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
	Конструктор
*/
string::string(const char* str)
{
	_string_count++;
	_max_length = initial_max_length;
	size_t len = strlen(str);
	while (len > _max_length) _max_length *= 2; // если длина принимаемой строки больше чем выделенная память 
	_length = len;
	_str = new char[_max_length + 1]; 
	strcpy(_str, str);
}
/*
	Конструктор
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
	Деструктор
*/
string::~string()
{
	_string_count--;
	delete[] _str;
}

/*
	Добавляет значение аргумента в конец строки
*/
void string::append(const char* str)
{
	size_t len = strlen(str);
	if (len + _length > _max_length){ // случай если суммарная длина больше выделенной памяти
		while (len + _length > _max_length) _max_length *= 2; // увеличиваем выделенную память
		allocate_and_cpy(_max_length);
		char* tmp = _str + _length; // ставит указатель на конец текущей строки
		for (size_t i = 0; i < len; i++) { //дописывает принятую строку в конец текущей
			*(tmp + i) = *(str + i);
		}
		_length += len;
		*(_str + _length) = '\0';
	}
	else {
		char* tmp = _str + _length; // ставит указатель на конец текущей строки
		for (size_t i = 0; i < len; i++) { // дописывает принятую строку в конец текущей
			*(tmp + i) = *(str + i);
		}
		_length += len;
		*(_str + _length) = '\0';
	}
}
/*
	Добавляет значение аргумента в конец строки
*/
void string::append(const string& str)
{
	append(str._str); // вызывает предыдущий метод передавая char*
}
/*
	Длина строки
*/
size_t string::length() const
{
	return _length;
}
/*
	Размер выделенной памяти
*/
size_t string::max_length() const
{
	return _max_length;
}
/*
	Очистка строки
*/
void string::clear()
{
	_length = 0;
	delete _str; // удаление данных
	_str = new char[_max_length + 1]; // выделение памяти под новые
	*_str = '\0';
}
/*
	Проверка на пустоту
*/
bool string::empty() const
{
	return _length == 0;
}
/*
	Установка нового значения
*/
void string::assign(const char* str)
{
	_length = strlen(str);
	while (_length > _max_length) _max_length *= 2; // увеличение максимальной памяти, если нужно
	allocate_and_cpy(_max_length); // выделение этой новой памяти
	strcpy(_str, str); // копирование строк
}
/*
	Установка нового значения
*/
void string::assign(const string& str)
{
	assign(str._str); // вызывает предыдущий метод, передавая char*
}
/*
	Вставка строки внутрь текущей
*/
void string::insert(size_t pos, const char* str)
{
	if (pos > _length - 1) throw str_exception("incorrect position"); // проверка правильности переданных данных
	size_t len = strlen(str);
	while (len + _length > _max_length) _max_length *= 2; // увеличение максимальной памяти 
	allocate_and_cpy(_max_length); // выделение этой новой памяти

	char* second = new char[_length - pos + 1]; // буфер для второй половины текущей строки
	strcpy(second, _str + pos); // копирование второй половины в буфер
	strcpy(_str + pos, str); // копирование переданной строки на новое место
	strcpy(_str + pos + strlen(str), second); // добавление второй половины обратно в строку после нового фрагмента
	delete[] second; // удаление буфера
}
/*
	Вставка строки внутрь текущей
*/
void string::insert(size_t pos, const string& str)
{
	insert(pos, str._str); // вызывает предыдущий метод, передавая char*
}
/*
	Поиск позиции первого вхождения подстроки
*/
size_t string::find(const char* str) const
{
	size_t len = strlen(str);
	for (size_t i = 0, j = 0; i < _length; i++, j = 0) { // Проход по символам текущей строки
		while (*(_str + i + j) == *(str + j)) j++; // Если символы строки и подстроки совпадают счетчик увеличивается
		if (j >= len) return i; // если счетчик равен длине подстроки, то мы нашли первое вхождение
	}
	throw str_exception("no such substring"); // если ничего не нашли выбрасываем сообщение об этом
}
/*
	Поиск позиции первого вхождения подстроки
*/
size_t string::find(const string& str) const
{
	return find(str._str); // вызывает предыдущий метод, передавая char*
}
/*
	Выделение подстроки из текущей строки
*/
string string::substr(size_t pos_begin, size_t length) const
{
	if (pos_begin + length > _length) throw str_exception("incorrect parameters"); // проверка правильности переданных данных
	char* str = new char[length + 1]; // выделение памяти для подстроки
	for (size_t i = 0; i < length; i++) // последовательно копируем символы в подстроку
		*(str + i) = *(_str + pos_begin + i); 
	*(str + length) = '\0';
	string s(str);
	delete[] str;
	return s;

}
/*
	Возвращение указателя на char для текущей строки 
*/
char* string::c_str() const
{
	char* str = new char[_length + 1];
	strcpy(str, _str);
	return str;
}
/*
	Вывод на экран
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

