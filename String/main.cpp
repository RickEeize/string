#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "catch.hpp"

#include "String.h"
#include "binary_string.h"
#include "todo_string.h"
#include "stack.h"

using namespace my;

TEST_CASE("constructor", "[stack, string]") { // тесты для конструктора
	stack s; // конструктор по умолчанию
	REQUIRE(s.size() == 0);
	REQUIRE(s.empty());
	REQUIRE_THROWS_AS(s.top(), std::exception);
	REQUIRE_THROWS_AS(s.pop(), std::exception);
	string strings[5];
	strings[0] = "string0";
	strings[1] = "string1";
	strings[2] = "string2";
	strings[3] = "string3";
	strings[4] = "string4";
	for (int i = 0; i < 5; i++) s.push(strings[i]);
	stack s1(s); // конструктор копирования
	REQUIRE(s1.size() == 5);
	REQUIRE(strcmp(s1.remove(2).c_str(), "string2") == 0);
}

TEST_CASE("push, pop, print", "[stack, string]") {
	stack s;
	string strings[5];
	strings[0] = "string0";
	strings[1] = "string1";
	strings[2] = "string2";
	strings[3] = "string3";
	strings[4] = "string4";
	for (int i = 0; i < 5; i++) s.push(strings[i]); // добавляем в стек данные
	FILE * o = freopen("file5lab.txt", "w", stdout); // перенаправляем поток вывода
	s.print(); // выводим стек
	
	std::ifstream ist("file5lab.txt");
	string st;
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "string4 string3 string2 string1 string0")); 
	ist.close();

	s.pop(); // удаляем данные из стека
	s.pop();

	s.print(); // выводим стек

	ist.open("file5lab.txt");
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "string2 string1 string0"));
	ist.close();

	fclose(stdout);
	o = freopen("CON", "w", stdout);
}

TEST_CASE("polymorphism, top", "[stack, string, binary_string, todo_string]") {
	stack s;
	string str = "this is string"; // создаем 3 объекта разных классов
	binary_string bin_str = 19;
	todo_string todo_str = "do a test";
	s.push(todo_str); // добавляем их в стек
	s.push(bin_str);
	s.push(str);
	REQUIRE(strcmp(s.top().c_str(), "this is string") == 0); // c_str() является функцией класса string и наследуется
	s.pop();
	REQUIRE(strcmp(s.top().c_str(), "10011") == 0); // классами binary_string и
	s.pop();
	REQUIRE(strcmp(s.top().c_str(), "do a test") == 0); // todo_string
}

TEST_CASE("insert, delete", "[stack, string]") {
	stack s;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";
	s.push(str1);
	s.push(str2);
	s.insert(str3, 1);
	REQUIRE_THROWS_AS(s.insert(str1, -1), std::out_of_range);
	REQUIRE_THROWS_AS(s.insert(str1, 100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(-1), std::out_of_range);
	REQUIRE(strcmp(s.top().c_str(), str2.c_str()) == 0);
	REQUIRE(&s.top() == &str2); // совпадают адреса, так как храним ссылки
	REQUIRE(s.size() == 3);
	REQUIRE(strcmp(s.remove(1).c_str(), str3.c_str()) == 0);
}

TEST_CASE("contains", "[stack, string]") {
	stack s;
	string s1 = "string1";
	string s2 = "string2";
	string s3 = "string1";
	s.push(s1);
	s.push(s2);
	REQUIRE(s.contains(s1));
	REQUIRE(s.contains(s3)); // Проверяем, что совпадения ищутся по значению, а не по адресу
}