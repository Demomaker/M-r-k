#pragma once
#include <iterator>
#include "EmptyListException.h"

template <class T>
class CircleLinkedList
{
public:
	CircleLinkedList();
	~CircleLinkedList();
	void add_end(T * value);
	void add_start(T * value);
	T * firstValue();
	T * lastValue();
	T * remove_end();
	T * remove_start();
	bool isNullptr();

private:
	class Cell
	{
	public:
		Cell(Cell * prev, T * value, Cell * next)
			: prev(prev), value(value), next(next) {}
		Cell * prev;
		T * value;
		Cell * next;


	};
	Cell * last;

public:
	class iterator
		: public std::iterator<std::input_iterator_tag, T>
	{
	public:
		iterator(const CircleLinkedList<T> * list);
		iterator(const iterator& list_iter);

		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
		T& operator*();

	private:
		Cell * current;
		Cell * last;
	};

	iterator begin()
	{
		return iterator(this);
	}

	iterator end()
	{
		return iterator(nullptr);
	}


};


template <class T>
CircleLinkedList<T>::CircleLinkedList()
{
	last = nullptr;
}


template <class T>
CircleLinkedList<T>::~CircleLinkedList()
{
	while (last != nullptr)
	{
		Cell *temp = last;
		last = last->next;
		delete temp;
	}
}

template <class T>
void CircleLinkedList<T>::add_end(T* value)
{
	Cell * temp = last;
	if (temp == nullptr) {
		last = new Cell(last , value, last);
		last->next = last;
		last->prev = last;
	}
	else {
		last = new Cell(last, value, last->next);
		last->prev->next = last;
		last->next->prev = last;
	}
	temp = nullptr;
}

template <class T>
void CircleLinkedList<T>::add_start(T* value)
{
	Cell * temp = last;
	if (temp == nullptr) {
		last = new Cell(last, value, last);
		last->next = last;
		last->prev = last;
	}
	else {
		last->next = new Cell(last, value, last->next);
		last->next->next->prev = last->next;
	}
	temp = nullptr;
}

template<class T>
inline T * CircleLinkedList<T>::firstValue()
{
	return last->next->value;
}

template<class T>
inline T * CircleLinkedList<T>::lastValue()
{
	return last->value;
}

template <class T>
T * CircleLinkedList<T>::remove_end()
{
	if (last == nullptr)
	{
		throw EmptyListException();
	}
	T * temp = last->value;
	if (last == last->prev)
	{
		delete last;
		last = nullptr;
	}
	else {
		Cell * temp2 = last->next;
		last = last->prev;
		delete last->next;
		last->next = temp2;
		last->next->prev = last;
	}
	return temp;
}

template <class T>
T * CircleLinkedList<T>::remove_start()
{
	if (last == nullptr) {
		throw EmptyListException();
	}

	T * temp = last->next->value;
	if (last->prev == last) {
		delete last;
		last = nullptr;
	}
	else {
		Cell * temp2 = last->next->next;
		delete last->next;
		last->next = temp2;
		last->next->prev = last;
	}
	return temp;
}

template<class T>
bool CircleLinkedList<T>::isNullptr()
{
	return (last == nullptr);
}

template <class T>
CircleLinkedList<T>::iterator::iterator(const CircleLinkedList<T>* list)
{
	if (list == nullptr || list->last == nullptr) {
		current = nullptr;
	}
	else
	{
		if(last != current)
		current = list->last->next;
	}
}

template <class T>
CircleLinkedList<T>::iterator::iterator(const iterator& list_iter)
	: current(list_iter.current)
{
}

template <class T>
typename CircleLinkedList<T>::iterator& CircleLinkedList<T>::iterator::operator++()
{
	if (last != current) {
		current = current->next;
	}
	return *this;
}

template <class T>
typename CircleLinkedList<T>::iterator CircleLinkedList<T>::iterator::operator++(int)
{
	iterator tmp(*this);
	operator++();
	return tmp;
}

template <class T>
bool CircleLinkedList<T>::iterator::operator==(const iterator& rhs) const
{
	return current == rhs.current;
}

template <class T>
bool CircleLinkedList<T>::iterator::operator!=(const iterator& rhs) const
{
	return current != rhs.current;
}

template <class T>
T & CircleLinkedList<T>::iterator::operator*()
{
	return *current->value;
}