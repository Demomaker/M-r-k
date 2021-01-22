#pragma once
#include <iterator>
#include "EmptyListException.h"

template <class T>
class CircularDoubleLinkedList
{
public:
	CircularDoubleLinkedList();
	~CircularDoubleLinkedList();
	void add_end(T * value);
	void add_start(T * value);
	T * remove_end();
	T * remove_start();
	int getSize() const;
	T * getEnd() const;
	T * getStart() const;
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

	int size = 0;
	Cell * first;

public:
	class iterator
		: public std::iterator<std::input_iterator_tag, T>
	{
	public:
		iterator(const CircularDoubleLinkedList<T> * list);
		iterator(const iterator& list_iter);

		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
		T& operator*();

	private:
		Cell * current;
		Cell * first;
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
CircularDoubleLinkedList<T>::CircularDoubleLinkedList()
{
	first = nullptr;
}

template <class T>
CircularDoubleLinkedList<T>::~CircularDoubleLinkedList()
{
	while (first != nullptr && first->next != nullptr && first != first->next)
	{
		Cell *temp = first;
		first->prev->next = nullptr;
		first = first->next;
		delete temp;
	}
	if (first != nullptr && first == first->next)
	{
		delete first;
	}
}

template <class T>
int CircularDoubleLinkedList<T>::getSize() const
{
	return size;
}

template <class T>
T * CircularDoubleLinkedList<T>::getStart() const
{
	return first != nullptr ? first->value : nullptr;
}

template <class T>
T * CircularDoubleLinkedList<T>::getEnd() const
{
	return first != nullptr ? first->prev->value : nullptr;
}

template <class T>
void CircularDoubleLinkedList<T>::add_end(T* value)
{
	if (first == nullptr)
	{
		first = new Cell(nullptr, value, nullptr);
		first->prev = first;
		first->next = first;
	}
	else
	{
		first->prev = new Cell(first->prev, value, first); // Circulaire
		first->prev->next->prev = first->prev;
		first->prev->prev->next = first->prev;
	}
	size++;
}

template <class T>
void CircularDoubleLinkedList<T>::add_start(T* value)
{
	if (first == nullptr)
	{
		first = new Cell(nullptr, value, nullptr);
		first->prev = first;
		first->next = first;
	}
	else
	{
		first = new Cell(first->prev, value, first); // Circulaire 
		first->next->prev = first;
		first->prev->next = first;
	}
	size++;
}

template <class T>
T * CircularDoubleLinkedList<T>::remove_end()
{
	if (first == nullptr || first->prev == nullptr)
	{
		throw EmptyListException();
	}

	T * temp = first->prev->value;
	if (first->prev == first)
	{
		delete first;
		first = nullptr;
	}
	else
	{
		first->prev = first->prev->prev;
		delete first->prev->next;
		first->prev->next = first;
	}
	size--;
	return temp;
}

template <class T>
T * CircularDoubleLinkedList<T>::remove_start()
{
	if (first == nullptr)
	{
		throw EmptyListException();
	}

	T * temp = first->value;
	if (first == first->prev)
	{
		delete first;
		first = nullptr;
	}
	else
	{
		first = first->next;
		first->prev = first->prev->prev;
		delete first->prev->next;
		first->prev->next = first;
	}
	size--;
	return temp;
}

template <class T>
CircularDoubleLinkedList<T>::iterator::iterator(const CircularDoubleLinkedList<T>* list)
{
	if (list == nullptr)
	{
		current = nullptr;
	}
	else
	{
		current = list->first;
		first = current;
	}
}

template <class T>
CircularDoubleLinkedList<T>::iterator::iterator(const iterator& list_iter)
	: current(list_iter.current)
{
}

template <class T>
typename CircularDoubleLinkedList<T>::iterator& CircularDoubleLinkedList<T>::iterator::operator++()
{
	if (current->next == first)
	{
		current = nullptr;
	}
	else
	{
		current = current->next;
	}
	return *this;
}

template <class T>
typename CircularDoubleLinkedList<T>::iterator CircularDoubleLinkedList<T>::iterator::operator++(int)
{
	iterator tmp(*this);
	operator++();
	return tmp;
}

template <class T>
bool CircularDoubleLinkedList<T>::iterator::operator==(const iterator& rhs) const
{
	return current == rhs.current;
}

template <class T>
bool CircularDoubleLinkedList<T>::iterator::operator!=(const iterator& rhs) const
{
	return current != rhs.current;
}

template <class T>
T & CircularDoubleLinkedList<T>::iterator::operator*()
{
	return *current->value;
}