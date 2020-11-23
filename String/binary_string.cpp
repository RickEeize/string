#include "binary_string.h"

binary_string::binary_string()
{
	assign("0"); // ����������� 0
	_decimal = 0;
	_is_negative = 0;
}

binary_string::binary_string(int decimal)
{
	_decimal = decimal;
	if (decimal < 0) { // ���� ����� ������������� ���� ��������������� = 1
		_is_negative = 1;
		decimal *= -1; // ������ ���� �������� �����
	}
	else _is_negative = 0;
	const char* str = _dec_to_str(decimal); // ��������� ���������� � �������� � ������
	assign(str); // ����������� ������
	delete str; // ������� �����
}

binary_string::binary_string(const binary_string& other)
{
	assign(other); // ����������� ��������� ������ ������
	_is_negative = other._is_negative;
	_decimal = other._decimal;
}

binary_string binary_string::operator+(const binary_string& other)
{
	return binary_string(_decimal + other._decimal); // ���������� �����
}

binary_string binary_string::operator+(int decimal)
{
	return binary_string(_decimal + decimal);
}

binary_string binary_string::operator+(const char* other)
{
	if(!_is_valid(other)) throw std::exception("incorrect data"); // ��������� ���������� ����� �� ������������
	return binary_string(_decimal + _str_to_dec(other));
}

binary_string binary_string::operator-(const binary_string& other)
{
	return binary_string(_decimal - other._decimal); // ���������� ��������
}

binary_string binary_string::operator-(int decimal)
{
	return binary_string(_decimal - decimal);
}

binary_string binary_string::operator-(const char* other)
{
	if (!_is_valid(other)) throw std::exception("incorrect data");// ��������� ���������� ����� �� ������������
	return binary_string(_decimal - _str_to_dec(other));
}

binary_string binary_string::operator*(const binary_string& other)
{
	return binary_string(_decimal * other._decimal); // ���������� ������������
}

binary_string binary_string::operator*(int decimal)
{
	return binary_string(_decimal * decimal);
}

binary_string binary_string::operator*(const char* other)
{
	if (!_is_valid(other)) throw std::exception("incorrect data");// ��������� ���������� ����� �� ������������
	return binary_string(_decimal * _str_to_dec(other));
}

binary_string binary_string::operator+() // ������� ����, ������ �� ������
{
	return *this;
}

binary_string binary_string::operator-() // ������� �����, ������ ���� ����� 
{
	return binary_string(_decimal * (-1));
}

int binary_string::get_decimal() const // ���������� ���������� �����
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
	assign(other); // ����������� ��������� ������ ������
	_is_negative = other._is_negative;
	_decimal = other._decimal;
	return *this;
}

binary_string& binary_string::operator=(int decimal)
{
	/*
		���� ����� ��� � � ������������
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
	if (!_is_valid(other)) throw std::exception("incorrect data"); // �������� ������ �� ������������
	_decimal = _str_to_dec(other); // ��������� ������ � �����
	if (_decimal < 0) { // ��������� �� ���������������
		_is_negative = 1;
		assign(other + 1); // ����������� ������ �� ����������� ����� �����
	}
	else {
		_is_negative = 0;
		assign(other); // ����������� ������
	}
	return *this;
}
/*
	������� ����������� ����� � �������� � ������
*/
const char* binary_string::_dec_to_str(int decimal)
{
	int copy = decimal;
	size_t res = 0;
	while (copy) { // ������� ���������� �������� ��������� �����������
		res++;
		copy >>= 1;
	}
	char* str;
	if (res == 0) { // ���� ����� = 0
		str = new char[2];
		str[0] = '0';
		str[1] = '\0';
	}
	else { 
		str = new char[res + 1];
		for (int i = 0; i < res; i++) { // ��������������� ��������� ������ ������� ��������� �����
			int digit = decimal % 2;
			str[res - 1 - i] ='0' + digit;
			decimal /= 2;
		}
		str[res] = '\0';
	}
	return str;
}
/*
	������� ��������� ����� � ������ � ����������
*/
int binary_string::_str_to_dec(const char* str)
{
	bool neg;
	if (*str == '-') { // ���� � ������ ������ ���� ��� �����
		neg = 1; // ���� ���������������
		str++; // ����� ������ ( �� �������� �� �������� ���������, ��� ��� �� ���������� ��� �������� � ������� )
	}
	else neg = 0;
	int result = 0;
	size_t len = strlen(str);
	for (int i = 0; i < len; i++) { // ����������� ����� �� �������� ������
		result += (str[i] - '0') * (int)pow(2, len - 1 - i);
	}
	return result * (neg ? -1 : 1); // � ����������� �� ����� ��������������� ���������� ���� ������������� ���� ������������� �����
}
/*
	�������� �� ������������ ��������� ����� � ������
*/
bool binary_string::_is_valid(const char* str)
{
	if (*str == '\0') return 0; // ���� ������ ������ - ��� �����������
	if (!(*(str) == '-' || *(str) == '0' || *(str) == '1')) return 0; // ������ ������ ����� ���� �����
	size_t len = strlen(str);
	for (int i = 1; i < len; i++) { // ��������� ������� � ������ (������ ���� ���� 0, ���� 1)
		if (!(*(str + i) == '0' || *(str + i) == '1')) return 0;
	}
	return 1;
}
/*
	����� � �����
*/
std::ostream& operator<<(std::ostream& out, const binary_string& str)
{
	out << (str._is_negative ? "-" : "") << str._str; // ������� ��� �� ������� ����� � ���� �����
	return out;
}
/*
	������ ����� �� ������
*/
std::istream& operator>>(std::istream& in, binary_string& str)
{
	char* buf = new char[128]; // ������� ����� 
	in.getline(buf, 128); // ������ ������� �� ������ � �����
	if (!str._is_valid(buf)) throw std::exception("incorrect data"); // ��������� �� ������������
	if (buf[0] == '-') { // ���� �������������
		if (*(buf + 1) != '0') { //���� ������ != -0
			str._is_negative = 1; // ���� ���������������
			str.assign(buf + 1); // ����������� ������� ����� ������ �� �������
			str._decimal = str._str_to_dec(buf); // ��������� ������ � ����� � ����������� ����������� �����������
		}
		else {
			str._is_negative = 0;
			str.assign("0");
			str._decimal = 0;
		}
	}
	else {
		str._is_negative = 0;
		str.assign(buf); // ����������� ������� ����� ������
		str._decimal = str._str_to_dec(buf); // ��������� ������ � ����� � ����������� ����������� �����������
	}
	delete[] buf; // ������� �����
	return in;
}