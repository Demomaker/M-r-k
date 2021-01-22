#include "Room.h"
#include "Constants.h"

/// <summary>
/// Constructeur d'une pièce
/// </summary>
/// <param name="x">Position en X</param>
/// <param name="y">Position en Y</param>
/// <param name="w">Largeur</param>
/// <param name="h">Hauteur</param>
Room::Room(int x, int y, int w, int h) : position(x, y), w(w), h(h)
{
	x1 = x;
	x2 = x + w;
	y1 = y;
	y2 = y + h;
	// Déterminer la position centrale
	center = sf::Vector2i(floor((x1 + x2) / 2), floor((y1 + y2) / 2));
}

/// <summary>
/// Détermine si la pièce entre en collision avec une autre
/// </summary>
/// <return>Vrai si collision, faux sinon</return>
bool Room::intersects(Room room)
{
	// Teste des rectangles de collision
	return (x1 <= room.x2 && x2 >= room.x1 && y1 <= room.y2 && room.y2 >= room.y1);
}

/// <summary>
/// Obtient la position centrale de la pièce
/// </summary>
/// <return>La position centrale de la pièce</return>
sf::Vector2i Room::getCenter() const
{
	return center;
}

/// <summary>
/// Obtient la position de la pièce
/// </summary>
/// <return>La position de la pièce</return>
sf::Vector2i Room::getPosition() const
{
	return position;
}

/// <summary>
/// Obtient la largeur de la pièce
/// </summary>
/// <return>La largeur de la pièce</return>
const int & Room::getWidth() const
{
	return w;
}

/// <summary>
/// Obtient la hauteur de la pièce
/// </summary>
/// <return>La hauteur de la pièce</return>
const int & Room::getHeight() const
{
	return h;
}
