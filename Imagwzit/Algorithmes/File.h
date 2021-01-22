#pragma once
#include "CircleLinkedList.h"
#include <limits.h>
template <class T>
class File
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="LinkedListStack"/> class.
	/// </summary>
	File();
	/// <summary>
	/// Finalizes an instance of the <see cref="LinkedListStack"/> class.
	/// </summary>
	~File();
	/// <summary>
	/// Pushes the specified element into the pile.
	/// </summary>
	/// <param name="element">The element.</param>
	void push(T& element);
	/// <summary>
	/// Pops the first element of the pile
	/// </summary>
	T * pop();
	/// <summary>
	/// Gets the top element of the pile
	/// </summary>
	/// <returns>The top element of the pile</returns>
	T * bottom() const;
	/// <summary>
	/// Determines whether this pile is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this pile is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty() const;
	/// <summary>
	/// Gives the size of the pile
	/// </summary>
	/// <returns>The size of the pile</returns>
	int size() const;
private:
	CircleLinkedList<T> * file;
	int numElements = 0;
}
;

template<class T>
inline File<T>::File()
{
	file = new CircleLinkedList<T>;
}

template<class T>
inline File<T>::~File()
{
	delete file;
}

template<class T>
inline void File<T>::push(T & element)
{
	numElements++;
	file->add_end(&element);
}

template<class T>
inline T * File<T>::pop()
{
	if (!isEmpty()) {
		numElements--;
		return file->remove_start();
	}
	return nullptr;
}

template<class T>
inline T * File<T>::bottom() const
{
	if (!isEmpty())
		return file->firstValue();
	else
		return nullptr;
	// TODO: insert return statement here
}

template<class T>
inline bool File<T>::isEmpty() const
{
	return file->isNullptr();
}

template<class T>
inline int File<T>::size() const
{
	return numElements;
}
