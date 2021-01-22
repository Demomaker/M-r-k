#pragma once
#include "CircleLinkedList.h"
#include "File.h"
#include "Pile.h"
template <class T> 
class ContainerFactory
{
public:
	static Pile<T> * getPile()
	{
		return new Pile<T>();
	}

	static File<T> * getFile()
	{
		return new File<T>();
	}

	static CircleLinkedList<T> * getCircleLinkedList()
	{
		return new CircleLinkedList<T>();
	}
};