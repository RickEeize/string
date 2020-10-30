#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "String.h"
#include "Tests.h"

#include "catch.hpp"

TEST_CASE("operation+") {
	REQUIRE(strcmp((string("abcde")+"fghij").c_str(), "abcdefghij") == 0);
	REQUIRE(strcmp((string("abcde") + string("fghij")).c_str(), "abcdefghij") == 0);
	REQUIRE(strcmp((string("qwe rty") + "fgh ijk").c_str(), "qwe rtyfgh ijk") == 0);
	REQUIRE(strcmp((string("qwerty") + "").c_str(), "qwerty") == 0);
	REQUIRE(strcmp((string("") + string("")).c_str(), "") == 0);
	REQUIRE(string("abcde").find("abcde") == 0);
}

TEST_CASE("operation-") {
	REQUIRE(strcmp((string("abcde") - "bcd").c_str(), "ae") == 0);
	REQUIRE(strcmp((string("abcde") - string("bcd")).c_str(), "ae") == 0);
	REQUIRE(strcmp((string("abcde") - "abcde").c_str(), "") == 0);
	REQUIRE(strcmp((string("abcde") - "").c_str(), "abcde") == 0);
	REQUIRE(strcmp((string("abcde") - "qwerty").c_str(), "abcde") == 0);
	REQUIRE(strcmp((string("") - "qwerty").c_str(), "") == 0);
	REQUIRE(strcmp((string("") - "").c_str(), "") == 0);
}

TEST_CASE("operation[]") {
	string s = "abcdefghi";
	
	REQUIRE((s[0] == 'a' && s[0] == *(s.c_str())));
	REQUIRE((s[2] == 'c' && s[2] == *(s.c_str() + 2)));
	REQUIRE((s[3] == 'd' && s[3] == *(s.c_str() + 3)));
	REQUIRE((s[6] == 'g' && s[6] == *(s.c_str() + 6)));
	s[0] = 'R';
	REQUIRE(*(s.c_str()) == 'R');
}

TEST_CASE("operation=") {
	string s = "abcde";

	REQUIRE(strcmp((s = "qwerty").c_str(), "qwerty") == 0);
	REQUIRE(strcmp(s.c_str(), "qwerty") == 0);
	REQUIRE(strcmp((s = "").c_str(), "") == 0);
	REQUIRE(strcmp(s.c_str(), "") == 0);
	REQUIRE(strcmp((s = string("qwerty")).c_str(), "qwerty") == 0);
	REQUIRE(strcmp(s.c_str(), "qwerty") == 0);
	REQUIRE(strcmp((s = string("")).c_str(), "") == 0);
	REQUIRE(strcmp(s.c_str(), "") == 0);
}

TEST_CASE("operation<<") {
	// вывод через объект ostream (cout)
	string s = "abcde";
	FILE * F = freopen("stdout_file.txt", "w", stdout); // Перенаправляем стандартный поток вывода stdout из консоли в файл.
														//Если тест будет пройден, то и при выводе в консоль, все будет работать
	std::cout << s;
	fclose(stdout);
	F = freopen("CON", "w", stdout); // перенаправляем обратно в консоль

	std::ifstream ist("stdout_file.txt"); // Проверим, те ли символы были записаны
	char* str = new char[128];
	ist.getline(str, 128);
	ist.close();

	REQUIRE(strcmp(s.c_str(), str) == 0);
	delete[] str;

	// вывод через объект ofstream (в файл)
	std::ofstream ost("file.txt");
	ost << s;
	ost.close();

	ist.open("file.txt"); // Проверим, те ли символы были записаны
	str = new char[128];
	ist.getline(str, 128);
	ist.close();
	REQUIRE(strcmp(s.c_str(), str) == 0);
	delete[] str;
}

TEST_CASE("operation>>") {
	string s;

	// Ввод через объект istream (cin)
	std::ofstream ost("stdin_file.txt"); // запишем символы в файл
	ost << "abcde";
	ost.close();

	FILE* F = freopen("stdin_file.txt", "r", stdin); // Перенаправляем стандартный поток ввода stdin из консоли в файл 
													//Если тест будет пройден, то и при вводе из консоли, все будет работать
	std::cin >> s;
	fclose(stdin);
	F = freopen("CON", "r", stdin); // Перенаправляем обратно в консоль
	REQUIRE(strcmp(s.c_str(), "abcde") == 0);

	//Ввод через объект ifstream (из файла)
	ost.open("file.txt"); // запишем символы в файл
	ost << "abcde";
	ost.close();

	std::ifstream ist("file.txt");
	ist >> s;
	ist.close();
	REQUIRE(strcmp(s.c_str(), "abcde") == 0);
}

TEST_CASE("writing to binary file") {
	string s = "abcde";
	std::ofstream ost("file_bin.bin", std::ios::binary);
	s.write_binary(ost);
	ost.close();
	
	std::ifstream ist("file_bin.bin", std::ios::binary);
	size_t ml;
	size_t l;
	char c[6];
	ist.read((char*)&ml, sizeof(size_t));
	ist.read((char*)&l, sizeof(size_t));
	for (int i = 0; i < 6; i++) {
		ist.read((char*)&c[i], sizeof(char));
	}
	ist.close();
	REQUIRE((ml == s.max_length() && l == s.length() && strcmp(c, s.c_str()) == 0));
}

TEST_CASE("reading from binary file") {
	std::ofstream ost("file_bin.bin", std::ios::binary); // Запишем в файл данные для считывания
	size_t ml = 16;
	size_t l = 5;
	const char* s = "abcde";
	ost.write((char*)&ml, sizeof(size_t));
	ost.write((char*)&l, sizeof(size_t));
	ost.write(s, 6);
	ost.close();
	string str;
	std::ifstream ist("file_bin.bin", std::ios::binary);
	str.read_binary(ist);
	ist.close();
	REQUIRE(strcmp(str.c_str(), "abcde") == 0);

}