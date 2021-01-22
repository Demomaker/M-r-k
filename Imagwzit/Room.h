#pragma once
#include "GameObject.h"

/// <summary>
/// Représente le concept d'une pièce en jeu
/// </summary>
class Room
{
public :
	/// <summary>
	/// Constructeur d'une pièce
	/// </summary>
	/// <param name="x">Position en X</param>
	/// <param name="y">Position en Y</param>
	/// <param name="w">Largeur</param>
	/// <param name="h">Hauteur</param>
	Room(int x, int y, int w, int h);

	
	/// <summary>
	/// Détermine si la pièce entre en collision avec une autre
	/// </summary>
	/// <return>Vrai si collision, faux sinon</return>
	bool intersects(Room room);

	/// <summary>
	/// Obtient la position centrale de la pièce
	/// </summary>
	/// <return>La position centrale de la pièce</return>
	sf::Vector2i getCenter() const;

	/// <summary>
	/// Obtient la position de la pièce
	/// </summary>
	/// <return>La position de la pièce</return>
	sf::Vector2i getPosition() const;

	/// <summary>
	/// Obtient la largeur de la pièce
	/// </summary>
	/// <return>La largeur de la pièce</return>
	const int & getWidth() const;

	/// <summary>
	/// Obtient la hauteur de la pièce
	/// </summary>
	/// <return>La hauteur de la pièce</return>
	const int & getHeight() const;

private :
	/// <summary>
	/// Position en X de l'extrémité gauche de la pièce
	/// </summary>
	int x1;

	/// <summary>
	/// Position en X de l'extrémité droite de la pièce
	/// </summary>
	int x2;

	/// <summary>
	/// Position en Y de l'extrémité gauche de la pièce
	/// </summary>
	int y1;

	/// <summary>
	/// Position en Y de l'extrémité droite de la pièce
	/// </summary>
	int y2;

	/// <summary>
	/// Position centrale de la pièce
	/// </summary>
	sf::Vector2i center;

	/// <summary>
	/// Largeur de la pièce
	/// </summary>
	const int w;

	/// <summary>
	/// Hauteur de la pièce
	/// </summary>
	const int h;

	/// <summary>
	/// Position de la pièce
	/// </summary>
	sf::Vector2i position;
};
