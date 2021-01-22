#pragma once
#include "stdafx.h"
#include "CircularDoubleLinkedList.h"

template <class T>
class Stack
{
public:
	void push(T * value);
	T * pop();
	T * top();
	int getSize() const;
private:
	CircularDoubleLinkedList<T> list;
};

template <class T>
void Stack<T>::push(T* value)
{
	list.add_end(value);
}

template <class T>
inline T * Stack<T>::pop()
{
	return list.remove_end();
}

template<class T>
inline T * Stack<T>::top()
{
	return list.getEnd();
}

template<class T>
inline int Stack<T>::getSize() const
{
	return list.getSize();
}