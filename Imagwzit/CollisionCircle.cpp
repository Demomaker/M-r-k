#include "CollisionCircle.h"

/// <summary>
/// Constructeur par défaut d'un cercle de collision
/// </summary>
CollisionCircle::CollisionCircle()
{
	this->radius = 1;
	this->posX = 0;
	this->posY = 0;
}

/// <summary>
/// Constructeur d'un cercle de collision avec des valeurs spécifiées
/// </summary>
/// <param name="radius">Rayon du cercle</param>
/// <param name="posX">Position du cercle en x</param>
/// <param name="posY">Position du cercle en y</param>
CollisionCircle::CollisionCircle(const float radius, const float posX, const float posY)
{
	this->radius = radius;
	this->posX = posX;
	this->posY = posY;
}

/// <summary>
/// Vérifie si le cercle entre en collision avec celui entré en paramètre
/// </summary>
/// <param name="otherCircle">Cercle de collision à vérifier</param>
/// <returns>Vrai s'il y a collision, faux sinon</returns>
bool CollisionCircle::checkCollision(const CollisionCircle &otherCircle) const
{
	float lineX = this->posX - otherCircle.posX;
	float lineY = this->posY - otherCircle.posY;

	float distance = lineX * lineX + lineY * lineY;
	float totalRadius = this->radius + otherCircle.radius;
	
	//À la place de faire la racine carré de la distance, on met la somme des rayons au carré; plus économe.
	totalRadius *= totalRadius;
	
	//Deux cercles qui se touchent sont considérées en collision
	if (distance <= totalRadius)
	{
		return true;
	}

	return false;
}

/// <summary>
/// Obtient le rayon du cercle
/// </summary>
/// <returns>Rayon du cercle</returns>
float CollisionCircle::getRadius() const
{ 
	return radius; 
}

/// <summary>
/// Obtient la position du cercle en x
/// </summary>
/// <returns>Position du cercle en x</returns>
float CollisionCircle::getPosX() const
{
	return posX; 
}

/// <summary>
/// Obtient la position du cercle en y
/// </summary>
/// <returns>Position du cercle en y</returns>
float CollisionCircle::getPosY() const
{ 
	return posY; 
}
