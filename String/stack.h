#pragma once

#include "String.h"
#include <iostream>

namespace my {
class stack {
public:
	stack();
	stack(const stack& other);
	~stack();
	void push(string& data);
	void pop();
	const string& top() const;
	bool empty() const;
	size_t size() const;
	void clear();
	void insert(string& data, size_t index);
	const string& remove(size_t index);
	void print() const;
	bool contains(const string& data) const;

private:
	class node {
	public:
		node(string& data);
	private:
		string& _data;
		node* _next;
		friend class stack;
	};

	node* _head;
	size_t _length;
};
}