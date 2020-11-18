#include "todo_string.h"

todo_string::todo_string() : // ������, ������ � ����� ���
	string()
{
	_start = 0;
	_end = 0;
}

todo_string::todo_string(const char* task) : // ����������� ������, ������ � ����� ���
	string(task)
{
	_start = 0;
	_end = 0;
}

void todo_string::start()
{
	if (!_start) _start = time(0); // ���� ������ �� ������, ��������� ������� �����
}

void todo_string::finish()
{
	if (_start && !_end) _end = time(0); // ���� ������ ������, �� �� ���������, ��������� ������� �����
}

bool todo_string::started() const
{
	return _start != 0;
}

bool todo_string::finished() const
{
	return _end != 0; 
}

time_t todo_string::when_started() const
{
	return _start;
}

time_t todo_string::when_finished() const
{
	return _end;
}

todo_string& todo_string::operator=(const todo_string& other)
{
	assign(other); //����������� ������ � ����� ������ � ����������
	_start = other._start;
	_end = other._end;
	return *this;
}

todo_string& todo_string::operator=(const char* other)
{
	assign(other); //����������� ������ � ����� ������ � ����������
	_start = 0;
	_end = 0;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const todo_string& task)
{
	if (task.started()) out << "started: " << asctime(localtime(&task._start)); // ���� ��������, �� ������� �����
	if (task.finished()) out << "finished: " << asctime(localtime(&task._end)); // ���� �����������, �� ������� �����
	out << task._str; // ������� ������
	return out;
}

std::istream& operator>>(std::istream& in, todo_string& task)
{
	char* buf = new char[128]; // ������� ����� 
	in.getline(buf, 128); // ������ ������� �� ������ � �����
	task.assign(buf); // ����������� ������� ����� ������
	task._start = 0;
	task._end = 0;
	delete[] buf; // ������� �����
	return in;
}
