#pragma once
#include <SFML/Graphics.hpp>

struct Manip
{	
	/// <summary>
	/// Constructeur de Manip
	/// </summary>
	/// <param name="move">Ce qui est à faire.</param>
	/// <param name="time">Temps lorsque c'est arrivé.</param>
	Manip(int move, sf::Time time)
	{
		this->move = move;
		whenHappened = time;
	}
	
	/// <summary>
	/// Ce qui est à faire
	/// </summary>
	int move;
	
	/// <summary>
	/// Temps lorsque c'est arrivé
	/// </summary>
	sf::Time whenHappened;
};