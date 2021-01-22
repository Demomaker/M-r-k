#pragma once
#include "stdafx.h"
#include <exception>

class EmptyListException :
	public std::exception
{
public:
	EmptyListException();
	~EmptyListException();
};

