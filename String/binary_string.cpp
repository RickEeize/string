#include "binary_string.h"

binary_string::binary_string()
{
	assign("0"); // Присваиваем 0
	_decimal = 0;
	_is_negative = 0;
}

binary_string::binary_string(int decimal)
{
	_decimal = decimal;
	if (decimal < 0) { // если число отрицательное флаг отрицательности = 1
		_is_negative = 1;
		decimal *= -1; // меняем знак входного числа
	}
	else _is_negative = 0;
	const char* str = _dec_to_str(decimal); // переводим десятичное в бинарное в строку
	assign(str); // присваиваем строку
	delete str; // удаляем буфер
}

binary_string::binary_string(const binary_string& other)
{
	assign(other); // присваиваем параметры второй строки
	_is_negative = other._is_negative;
	_decimal = other._decimal;
}

binary_string binary_string::operator+(const binary_string& other)
{
	return binary_string(_decimal + other._decimal); // возвращаем сумму
}

binary_string binary_string::operator+(int decimal)
{
	return binary_string(_decimal + decimal);
}

binary_string binary_string::operator+(const char* other)
{
	if(!_is_valid(other)) throw std::exception("incorrect data"); // проверяем переданное число на корректность
	return binary_string(_decimal + _str_to_dec(other));
}

binary_string binary_string::operator-(const binary_string& other)
{
	return binary_string(_decimal - other._decimal); // возвращаем разность
}

binary_string binary_string::operator-(int decimal)
{
	return binary_string(_decimal - decimal);
}

binary_string binary_string::operator-(const char* other)
{
	if (!_is_valid(other)) throw std::exception("incorrect data");// проверяем переданное число на корректность
	return binary_string(_decimal - _str_to_dec(other));
}

binary_string binary_string::operator*(const binary_string& other)
{
	return binary_string(_decimal * other._decimal); // возвращаем произведение
}

binary_string binary_string::operator*(int decimal)
{
	return binary_string(_decimal * decimal);
}

binary_string binary_string::operator*(const char* other)
{
	if (!_is_valid(other)) throw std::exception("incorrect data");// проверяем переданное число на корректность
	return binary_string(_decimal * _str_to_dec(other));
}

binary_string binary_string::operator+() // унарный плюс, ничего не делает
{
	return *this;
}

binary_string binary_string::operator-() // унарный минус, меняет знак числа 
{
	return binary_string(_decimal * (-1));
}

int binary_string::get_decimal() const // десятичный эквивалент числа
{
	return _decimal;
}

char* binary_string::c_str() const
{
	char* str;
	if (_is_negative) {
		str = new char[_length + 2];
		*str = '-';
		strcpy(str + 1, _str);
	}
	else {
		str = new char[_length + 1];
		strcpy(str, _str);
	}
	return str;
}

binary_string& binary_string::operator=(const binary_string& other)
{
	assign(other); // присваиваем параметры второй строки
	_is_negative = other._is_negative;
	_decimal = other._decimal;
	return *this;
}

binary_string& binary_string::operator=(int decimal)
{
	/*
		тоже самое что и в конструкторе
	*/
	_decimal = decimal;
	if (decimal < 0) {
		_is_negative = 1;

		decimal *= -1;
	}
	else _is_negative = 0;
	const char* str = _dec_to_str(decimal);
	assign(str);
	delete str;
	return *this;
}

binary_string& binary_string::operator=(const char* other)
{
	if (!_is_valid(other)) throw std::exception("incorrect data"); // прверяем строку на корректность
	_decimal = _str_to_dec(other); // переводим строку в число
	if (_decimal < 0) { // проверяем на отрицательность
		_is_negative = 1;
		assign(other + 1); // присваиваем строку за исключением знака минус
	}
	else {
		_is_negative = 0;
		assign(other); // присваиваем строку
	}
	return *this;
}
/*
	Перевод десятичного числа в бинарное в строку
*/
const char* binary_string::_dec_to_str(int decimal)
{
	int copy = decimal;
	size_t res = 0;
	while (copy) { // считаем количество разрядов двоичного эквивалента
		res++;
		copy >>= 1;
	}
	char* str;
	if (res == 0) { // если число = 0
		str = new char[2];
		str[0] = '0';
		str[1] = '\0';
	}
	else { 
		str = new char[res + 1];
		for (int i = 0; i < res; i++) { // последовательно заполняем строку цифрами бинарного числа
			int digit = decimal % 2;
			str[res - 1 - i] ='0' + digit;
			decimal /= 2;
		}
		str[res] = '\0';
	}
	return str;
}
/*
	Перевод бинарного числа в строке в десятичное
*/
int binary_string::_str_to_dec(const char* str)
{
	bool neg;
	if (*str == '-') { // если в строке первый знак это минус
		neg = 1; // флаг отрицательности
		str++; // сдвиг сторки ( не повлияет на исходный указатель, так как он копируется при передаче в функцию )
	}
	else neg = 0;
	int result = 0;
	size_t len = strlen(str);
	for (int i = 0; i < len; i++) { // составление числа по бинарным цифрам
		result += (str[i] - '0') * (int)pow(2, len - 1 - i);
	}
	return result * (neg ? -1 : 1); // в зависимости от флага отрицательности возвращаем либо отрицательное либо положительное число
}
/*
	Проверка на корректность бинарного числа в строке
*/
bool binary_string::_is_valid(const char* str)
{
	if (*str == '\0') return 0; // если строка пустая - она некорректна
	if (!(*(str) == '-' || *(str) == '0' || *(str) == '1')) return 0; // первый символ может быть минус
	size_t len = strlen(str);
	for (int i = 1; i < len; i++) { // проверяем символы в строке (должны быть либо 0, либо 1)
		if (!(*(str + i) == '0' || *(str + i) == '1')) return 0;
	}
	return 1;
}
/*
	Вывод в поток
*/
std::ostream& operator<<(std::ostream& out, const binary_string& str)
{
	out << (str._is_negative ? "-" : "") << str._str; // Выводим или не выводим минус и само число
	return out;
}
/*
	Чтение числа из потока
*/
std::istream& operator>>(std::istream& in, binary_string& str)
{
	char* buf = new char[128]; // Создаем буфер 
	in.getline(buf, 128); // Читаем символы из потока в буфер
	if (!str._is_valid(buf)) throw std::exception("incorrect data"); // Проверяем на корректность
	if (buf[0] == '-') { // Если отрицательное
		if (*(buf + 1) != '0') { //если строка != -0
			str._is_negative = 1; // флаг отрицательности
			str.assign(buf + 1); // присваиваем символы нашей строке со сдвигом
			str._decimal = str._str_to_dec(buf); // переводим строку в число и присваиваем десятичному эквиваленту
		}
		else {
			str._is_negative = 0;
			str.assign("0");
			str._decimal = 0;
		}
	}
	else {
		str._is_negative = 0;
		str.assign(buf); // присваиваем символы нашей строке
		str._decimal = str._str_to_dec(buf); // переводим строку в число и присваиваем десятичному эквиваленту
	}
	delete[] buf; // удаляем буфер
	return in;
}