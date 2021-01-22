#pragma once
#pragma once
#include "CircleLinkedList.h"
#include <limits.h>
template <class T>
class Pile
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="LinkedListStack"/> class.
	/// </summary>
	Pile();
	/// <summary>
	/// Finalizes an instance of the <see cref="LinkedListStack"/> class.
	/// </summary>
	~Pile();
	/// <summary>
	/// Pushes the specified element into the pile.
	/// </summary>
	/// <param name="element">The element.</param>
	void push(T& element) ;
	/// <summary>
	/// Pops the first element of the pile
	/// </summary>
	T * pop() ;
	/// <summary>
	/// Gets the top element of the pile
	/// </summary>
	/// <returns>The top element of the pile</returns>
	T * top() const ;
	/// <summary>
	/// Determines whether this pile is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this pile is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty() const ;
	/// <summary>
	/// Gives the size of the pile
	/// </summary>
	/// <returns>The size of the pile</returns>
	int size() const ;
private:
	CircleLinkedList<T> * pile;
	int numElements = 0;
}
;

template<class T>
inline Pile<T>::Pile()
{
	pile = new CircleLinkedList<T>;
}

template<class T>
inline Pile<T>::~Pile()
{
	delete pile;
}

template<class T>
inline void Pile<T>::push(T & element)
{
	numElements++;
	pile->add_end(&element);
}

template<class T>
inline T * Pile<T>::pop()
{
	if (!isEmpty()) {
		numElements--;
		return pile->remove_end();
	}
	return nullptr;
}

template<class T>
inline T * Pile<T>::top() const
{
	if (!isEmpty())
		return pile->lastValue();
	else
		return nullptr;
	// TODO: insert return statement here
}

template<class T>
inline bool Pile<T>::isEmpty() const
{
	return pile->isNullptr();
}

template<class T>
inline int Pile<T>::size() const
{
	return numElements;
}
