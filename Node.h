#pragma once

template<typename T>
struct Node
{
	T data;
	Node<T>* next;

	Node<T>();
	Node<T>(const T& value);
};

template<typename T>
Node<T>::Node(const T& value)
	:data(value), next(nullptr)
{}

template<typename T>
Node<T>::Node()
{}