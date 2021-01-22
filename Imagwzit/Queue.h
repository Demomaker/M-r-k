#pragma once
#include "CircularDoubleLinkedList.h"

template <class T>
class Queue
{
public:
	void push(T * value);
	T * pop();
	T * top();
	int getSize() const;
	T * operator[] (int);
private:
	CircularDoubleLinkedList<T> list;
};

template <class T>
inline T * Queue<T>::operator[] (int index)
{
	if (index < 0 || index > list.getSize() - 1)
	{
		throw std::out_of_range("Index invalide");
	}
	auto current = std::begin(list);
	for (; index > 0; index--)
	{
		current++;
	}
	return &(*current);
}

template <class T>
void Queue<T>::push(T* value)
{
	list.add_end(value);
}

template <class T>
inline T * Queue<T>::pop()
{
	return list.remove_start();
}

template<class T>
inline T * Queue<T>::top()
{
	return list.getStart();
}

template<class T>
inline int Queue<T>::getSize() const
{
	return list.getSize();
}
