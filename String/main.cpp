#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "catch.hpp"

#include "String.h"
#include "binary_string.h"
#include "todo_string.h"

// binary_string
TEST_CASE("bin_constructor", "[binary_string]") { // тесты для конструктора
	binary_string str1 = 15;
	REQUIRE(str1.get_decimal() == 15);
	REQUIRE(strcmp(str1.c_str(), "1111") == 0);
	binary_string str2;
	REQUIRE(str2.get_decimal() == 0);
	REQUIRE(strcmp(str2.c_str(), "0") == 0);
}

TEST_CASE("bin_operator=", "[binary_string]") { // тесты для присваивания
	binary_string str;
	str = 15;
	REQUIRE(str.get_decimal() == 15); // требуем совпадения десятичных значений
	REQUIRE(strcmp(str.c_str(), "1111") == 0); // требуем совпадения двоичных значений
	str = "1111";
	REQUIRE(str.get_decimal() == 15);
	REQUIRE(strcmp(str.c_str(), "1111") == 0);
	str = -15;
	REQUIRE(str.get_decimal() == -15);
	REQUIRE(strcmp(str.c_str(), "-1111") == 0);

	REQUIRE_THROWS_AS(str = "-0-221awd0", std::exception);
}

TEST_CASE("bin_operator+", "[binary_string]") {
	binary_string s1 = 12;
	binary_string s2 = 24;
	REQUIRE((s1 + s2).get_decimal() == 36); // 12 + 24 = 36
	REQUIRE(strcmp((s1 + s2).c_str(), "100100") == 0);
	s1 = 15;
	s2 = -15;
	REQUIRE((s1 + s2).get_decimal() == 0); // 15 + (-15) = 0
	REQUIRE(strcmp((s1 + s2).c_str(), "0") == 0);
	s1 = -12;
	s2 = -24;
	REQUIRE((s1 + s2).get_decimal() == -36); // -12 + (-24) = 36
	REQUIRE(strcmp((s1 + s2).c_str(), "-100100") == 0);
}

TEST_CASE("bin_operator-", "[binary_string]") {
	binary_string s1 = 12;
	binary_string s2 = 24;
	REQUIRE((s1 - s2).get_decimal() == -12); // 12 - 24 = -12
	REQUIRE(strcmp((s1 - s2).c_str(), "-1100") == 0);
	s1 = 15;
	s2 = 15;
	REQUIRE((s1 - s2).get_decimal() == 0); // 15 - 15 = 0
	REQUIRE(strcmp((s1 - s2).c_str(), "0") == 0);
	s1 = -12;
	s2 = -24;
	REQUIRE((s1 - s2).get_decimal() == 12); // -12 - (-24) = 12
	REQUIRE(strcmp((s1 - s2).c_str(), "1100") == 0);
}

TEST_CASE("bin_operator*", "[binary_string]") {
	char* s;
	binary_string s1 = 2;
	binary_string s2 = 4;
	s = (s1 * s2).c_str();
	REQUIRE((s1 * s2).get_decimal() == 8); // 2*4=8
	REQUIRE(strcmp(s, "1000") == 0);
	delete s;
	s1 = 123123;
	s2 = 0;
	s = (s1 * s2).c_str();
	REQUIRE((s1 * s2).get_decimal() == 0); // 123123 * 0 = 0
	REQUIRE(strcmp(s, "0") == 0);
	delete s;
	s1 = 2;
	s2 = -4;
	s = (s1 * s2).c_str();
	REQUIRE((s1 * s2).get_decimal() == -8); // 2 * (-4) = -8
	REQUIRE(strcmp((s1 * s2).c_str(), "-1000") == 0);
	delete s;
}


// Оператор вывода достаточно тривиальный и тестился в прошлой лабе

TEST_CASE("bin_operator>>", "[binary_string, istream]") {
	binary_string s;

	std::ofstream out("in.txt");  // Записываем данные в файл
	if (!out.is_open()) throw std::exception("file was not opened");
	out << "10001\n-10001\n12131";
	out.close();

	FILE* o = freopen("in.txt", "r", stdin); // Перенаправляем стандартный поток ввода из консоли в файл
	
	std::cin >> s; // Считываем значения
	REQUIRE(s.get_decimal() == 17); // Проверяем

	std::cin >> s;
	REQUIRE(s.get_decimal() == -17);

	REQUIRE_THROWS_AS(std::cin >> s, std::exception); // введенная строка "12131" должна при вводе кидать исключение

	fclose(stdin);
	o = freopen("CON", "r", stdin); // Перенаправляем стандартный поток ввода из файла обратно в консоль
}

// todo_string
// методы данного класса тривиальны и не требуют проверки, кроме перегрузки операторов 
TEST_CASE("todo_constructor", "[todo_string]") {
	todo_string s;
	REQUIRE(strcmp(s.c_str(), "") == 0); // Задачи нет
	REQUIRE((!s.started() && !s.finished())); // Не начата и не закончена

	todo_string s1("task");
	REQUIRE(strcmp(s1.c_str(), "task") == 0); // Задача task
	REQUIRE((!s1.started() && !s1.finished())); // Не начата и не закончена
}

TEST_CASE("todo_operator=", "[todo_string]") {
	todo_string s;
	s = "task";
	REQUIRE(strcmp(s.c_str(), "task") == 0); // Задачи task
	REQUIRE((!s.started() && !s.finished())); // Не начата и не закончена
	todo_string s1("task2");
	s1.start(); // Начали задачу
	s = s1;
	REQUIRE(strcmp(s.c_str(), "task2") == 0); // Задача task
	REQUIRE((s.started() && !s.finished())); // Начата и не закончена
}

// Оператор ввода достаточно тривиальный и тестился в прошлой лабе
TEST_CASE("todo_operator<<", "[todo_string, ostream]") {
	todo_string s = "test a lab 2";
	s.start();
	std::ofstream out("out.txt");
	out << s; // Выводим строку в поток
	out.close();

	time_t start_time = s.when_started(); // создаем эталонную строку для сравнения
	string expected = "started: ";
	expected.append(asctime(localtime(&start_time)));
	expected.append("test a lab 2");
	
	std::ifstream in("out.txt"); // считываем то, что выводили
	char buf[128];
	in.read(buf, 128);
	*(buf + expected.length()) = '\0';

	REQUIRE(strcmp(buf, expected.c_str()) == 0); // сравниваем
}