#pragma once
#include <iostream>
#include <fstream>

class string {

public:
	string();
	string(const char*);
	string(const string&);
	~string();
	void append(const char*);
	void append(const string&);
	size_t length() const;
	size_t max_length() const;
	void clear();
	bool empty() const;
	void assign(const char*);
	void assign(const string&);
	void insert(size_t, const char*);
	void insert(size_t, const string&);
	size_t find(const char*) const;
	size_t find(const string&) const;
	string substr(size_t, size_t) const;
	virtual char* c_str() const;
	void print() const;
	static size_t get_string_count();
	
	string operator+(const char*);
	string operator+(const string&);
	string operator-(const char*);
	string operator-(const string&);
	char& operator[](const size_t);
	string& operator=(const char*);
	string& operator=(const string&);

	void write_binary(std::ofstream&);
	void read_binary(std::ifstream&);

	/*
		Класс ofstream - поток записи данных в файл наследуется от ostream,
		так что нет смысла переопределять операцию << для ofstream, потому что
		действия были бы те же
	*/
	friend std::ostream& operator<<(std::ostream&, const string&);
	/*
		Аналогично
	*/
	friend std::istream& operator>>(std::istream&, string&);

private:
	static size_t _string_count;
	const size_t initial_max_length = 16;
protected:	
	char* _str;
	size_t _max_length;
	size_t _length;

	void allocate_and_cpy(size_t);
};