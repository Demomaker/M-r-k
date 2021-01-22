#pragma once
#include <SFML/Graphics.hpp>

struct Manip
{	
	/// <summary>
	/// Constructeur de Manip
	/// </summary>
	/// <param name="move">Ce qui est � faire.</param>
	/// <param name="time">Temps lorsque c'est arriv�.</param>
	Manip(int move, sf::Time time)
	{
		this->move = move;
		whenHappened = time;
	}
	
	/// <summary>
	/// Ce qui est � faire
	/// </summary>
	int move;
	
	/// <summary>
	/// Temps lorsque c'est arriv�
	/// </summary>
	sf::Time whenHappened;
};