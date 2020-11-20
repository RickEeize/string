#include "stack.h"

using namespace my;

stack::stack()
{
	_head = nullptr;
	_length = 0;
}

/*
	Конструктор копирования
*/
stack::stack(const stack& other) 
{
	clear(); // Очищаем стек
	if (other._length == 0) return;
	_head = new node(other._head->_data); // Создаем голову
	node* n = _head;
	node* tmp = other._head->_next;
	while (tmp != nullptr) {
		n->_next = new node(tmp->_data); // добавляем элементы стека other
		n = n->_next;
		tmp = tmp->_next;
	}
	_length = other._length;
}

stack::~stack()
{
	node* tmp;
	while (_head) { // Последовательно удаляем вершины
		tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
}

void stack::push(string& data)
{
	node* tmp = new node(data); // Создаем новую вершину на месте головы
	tmp->_next = _head;
	_head = tmp;
	_length++;
}

void stack::pop()
{
	if (_length == 0) throw std::exception("no elements");
	node* tmp = _head; // Удаляем вершину с головы
	_head = _head->_next;
	delete tmp;
	_length--;
}

const string& stack::top() const
{
	if (_length == 0) throw std::exception("no elements");
	return _head->_data;
}

bool stack::empty() const
{
	return _length == 0;
}

size_t stack::size() const
{
	return _length;
}

void stack::clear()
{
	node* tmp;
	while (_head) { // То же, что и в деструкторе 
		tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
	_head = nullptr; // Обнуляем переменные
	_length = 0;
}

void stack::insert(string& data, size_t index)
{
	if (index < 0 || index >= _length) throw std::out_of_range("index out of range");
	if (index == 0) { // Если индекс == 0, то же самое что и push
		push(data);
		return;
	}
	node* tmp = _head;
	for (int i = 1; i < index; i++) { // Доходим до нужного места
		tmp = tmp->_next;
	}
	node* new_node = new node(data); // Вставляем туда вершину
	new_node->_next = tmp->_next;
	tmp->_next = new_node;
	_length++;
}

const string& stack::remove(size_t index)
{

	if (index < 0 || index >= _length) throw std::out_of_range("index out of range");
	if (index == 0) { // Если индекс == 0, то же самое что и pop
		string s = top();
		pop();
		return s;
	}
	node* tmp = _head;
	for (int i = 1; i < index; i++) { // Доходим до нужного места 
		tmp = tmp->_next;
	}
	node* del = tmp->_next; // удаляем вершину, сохраняя и возвращая ее значение
	tmp->_next = del->_next;
	del->_next = nullptr;
	string& s = del->_data;
	delete del;
	_length--;
	return s;
}

void stack::print() const
{
	node* tmp = _head;
	for (size_t i = 0; i < _length; i++, tmp = tmp->_next) std::cout << tmp->_data << " "; // выводим данные
	std::cout << std::endl;
}
/*
	Последовательно проверяем на наличие значения, сравнивая по данным, а не по адресам
*/
bool stack::contains(const string& data) const
{
	node* tmp = _head;
	for (size_t i = 0; i < _length; i++, tmp = tmp->_next) if (strcmp(tmp->_data.c_str(), data.c_str()) == 0) return 1;
	return 0;
}

stack::node::node(string& data) :
	_data(data),
	_next(nullptr)
{
}
