#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "String.h"

class binary_string : public string {
	/*
		Деление у целых чисел не определено
	*/
public:
	binary_string();
	binary_string(int decimal);
	binary_string(const binary_string& other);
	int get_decimal() const;
	virtual char* c_str() const;
	binary_string& operator=(const binary_string& other);
	binary_string& operator=(int decimal);
	binary_string& operator=(const char* other);
	binary_string operator+(const binary_string& other);
	binary_string operator+(int decimal);
	binary_string operator+(const char* other);
	binary_string operator-(const binary_string& other);
	binary_string operator-(int decimal);
	binary_string operator-(const char* other);
	binary_string operator*(const binary_string& other);
	binary_string operator*(int decimal);
	binary_string operator*(const char* other);
	binary_string operator+();
	binary_string operator-();
	
	friend std::ostream& operator<<(std::ostream& os, const binary_string& str);
	friend std::istream& operator>>(std::istream& is, binary_string& str);

private:
	int _decimal;
	bool _is_negative;
	
	static const char* _dec_to_str(int decimal);
	static int _str_to_dec(const char* str);
	static bool _is_valid(const char* str);
};