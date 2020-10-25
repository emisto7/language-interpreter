#pragma once
#include <iostream>
#include "Node.h"
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class Stack
{
	Node<T>* top;

public:
	Stack()
	{
		top = NULL;
	}

	bool isEmpty() const;
	void push(const T& value);
	void pop();
	const T& getTop() const;

};

template<typename T>
bool Stack<T>::isEmpty() const
{
	if (top == NULL)
		return true;
	else
		return false;
}

template<typename T>
void Stack<T>::push(const T& value)
{
	Node<T>* ptr = new Node<T>();
	ptr->data = value;
	ptr->next = top;
	top = ptr;
}

template<typename T>
void Stack<T>::pop()
{
	if (isEmpty())
	{
		cout << "Stack is empty" << endl;
	}
	else
	{
		Node<T>* ptr = top;
		top = top->next;
		delete(ptr);
	}
}

template<typename T>
const T& Stack<T>::getTop() const
{
	return top->data;
}