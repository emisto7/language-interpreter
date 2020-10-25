#pragma once
#include "Node.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class List
{
public:
	List<T>();

	bool isEmpty() const;
	size_t size() const;

	const T& front() const;
	const T& end() const;
	const T& at(size_t position) const;

	void pushFront(const T& value);
	void pushEnd(const T& value);
	void pushAtPos(size_t position, const T& value);

	void popFront();
	void popEnd();
	void popAtPos(size_t position);

	int findPos(const T& value);

	void print() const;
private:
	Node<T>* head;
	size_t sz;
};

template<typename T>
const T& List<T>::at(size_t position) const
{
	if (isEmpty() || position >= sz || position == -1)
	{
		cout << "variable not found" << endl;
		throw std::invalid_argument("index out of bounds\n");
		
	}

	const Node<T>* iter = head;
	for (size_t i = 0; i < position; i++)
	{
		iter = iter->next;
	}
	return iter->data;
}

template<typename T>
const T& List<T>::front() const
{
	return at(0);
}

template<typename T>
const T& List<T>::end() const
{
	return at(sz - 1);
}

template<typename T>
size_t List<T>::size() const
{
	return sz;
}

template<typename T>
void List<T>::pushAtPos(size_t position, const T& value)
{
	if (position > sz) 
	{
		throw std::invalid_argument("Index out of bounds\n");
		cout << "index out of bounds" << endl;
	}

	if (position == 0) 
	{
		Node<T>* temp = head;
		head = new Node<T>(value);
		head->next = temp;
	}

	else 
	{
		Node<T>* iter = head;
		for (size_t i = 0; i < position - 1; i++)
		{
			iter = iter->next;
		}
		Node<T>* temp = iter->next;
		Node<T>* newNode = new Node<T>(value);
		iter->next = newNode;
		newNode->next = temp;
	}
	++sz;
}

template<typename T>
void List<T>::pushFront(const T& value)
{
	pushAtPos(0, value);
}

template<typename T>
void List<T>::pushEnd(const T& value)
{
	pushAtPos(sz, value);
}

template<typename T>
void List<T>::popAtPos(size_t position)
{
	if (isEmpty() || position > sz - 1 || position < 0) 
	{
		cout << "variable not found" << endl;
		throw std::invalid_argument("Index out of bounds\n");
	}

	Node<T>* detach = head;

	if (position == 0) 
	{
		head = head->next;
	}
	else 
	{
		Node<T>* iter = head;
		for (size_t i = 0; i < position - 1; i++)
		{
			iter = iter->next;
		}	
		detach = iter->next;
		iter->next = detach->next;
	}
	--sz;
	delete detach;
}

template<typename T>
void List<T>::popFront()
{
	popAtPos(0);
}

template<typename T>
void List<T>::popEnd()
{
	popAtPos(sz - 1);
}

template<typename T>
bool List<T>::isEmpty() const
{
	return sz == 0;
}

template<typename T>
int List<T>::findPos(const T& value)
{
	Node<T>* iter = head;
	for (size_t i = 0; i < sz; i++)
	{
		if (iter->data == value)
		{
			return i;
		}
		iter = iter->next;
	}
	return -1;
}

template<typename T>
void List<T>::print() const
{
	Node<T>* iter = head;
	for (size_t i = 0; i < sz; i++)
	{
		cout << iter->data;
		iter = iter->next;
	}
}

template<typename T>
List<T>::List() 
	:sz(0), head(nullptr)
{}