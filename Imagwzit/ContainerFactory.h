#pragma once
#include "CircularDoubleLinkedList.h"
#include "Queue.h"
#include "Stack.h"

template <class T>
class ContainerFactory
{
public:
	static Stack<T> * getStack() 
	{
		return new Stack<T>();
	}
	static Queue<T> * getQueue()
	{
		return new Queue<T>();
	}
	static CircularDoubleLinkedList<T> * getCircularDoubleLinkedList()
	{
		return new CircularDoubleLinkedList<T>();
	}
};

