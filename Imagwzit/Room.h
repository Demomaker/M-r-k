#pragma once
#include "GameObject.h"

/// <summary>
/// Repr�sente le concept d'une pi�ce en jeu
/// </summary>
class Room
{
public :
	/// <summary>
	/// Constructeur d'une pi�ce
	/// </summary>
	/// <param name="x">Position en X</param>
	/// <param name="y">Position en Y</param>
	/// <param name="w">Largeur</param>
	/// <param name="h">Hauteur</param>
	Room(int x, int y, int w, int h);

	
	/// <summary>
	/// D�termine si la pi�ce entre en collision avec une autre
	/// </summary>
	/// <return>Vrai si collision, faux sinon</return>
	bool intersects(Room room);

	/// <summary>
	/// Obtient la position centrale de la pi�ce
	/// </summary>
	/// <return>La position centrale de la pi�ce</return>
	sf::Vector2i getCenter() const;

	/// <summary>
	/// Obtient la position de la pi�ce
	/// </summary>
	/// <return>La position de la pi�ce</return>
	sf::Vector2i getPosition() const;

	/// <summary>
	/// Obtient la largeur de la pi�ce
	/// </summary>
	/// <return>La largeur de la pi�ce</return>
	const int & getWidth() const;

	/// <summary>
	/// Obtient la hauteur de la pi�ce
	/// </summary>
	/// <return>La hauteur de la pi�ce</return>
	const int & getHeight() const;

private :
	/// <summary>
	/// Position en X de l'extr�mit� gauche de la pi�ce
	/// </summary>
	int x1;

	/// <summary>
	/// Position en X de l'extr�mit� droite de la pi�ce
	/// </summary>
	int x2;

	/// <summary>
	/// Position en Y de l'extr�mit� gauche de la pi�ce
	/// </summary>
	int y1;

	/// <summary>
	/// Position en Y de l'extr�mit� droite de la pi�ce
	/// </summary>
	int y2;

	/// <summary>
	/// Position centrale de la pi�ce
	/// </summary>
	sf::Vector2i center;

	/// <summary>
	/// Largeur de la pi�ce
	/// </summary>
	const int w;

	/// <summary>
	/// Hauteur de la pi�ce
	/// </summary>
	const int h;

	/// <summary>
	/// Position de la pi�ce
	/// </summary>
	sf::Vector2i position;
};
