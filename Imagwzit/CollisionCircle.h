#pragma once

/// <summary>
/// Représente le concept logique d'un cercle de collision en jeu
/// </summary>
class CollisionCircle
{
public:		
	/// <summary>
	/// Constructeur par défaut d'un cercle de collision
	/// </summary>
	CollisionCircle();

	/// <summary>
	/// Constructeur d'un cercle de collision avec des valeurs spécifiées
	/// </summary>
	/// <param name="radius">Rayon du cercle</param>
	/// <param name="posX">Position du cercle en x</param>
	/// <param name="posY">Position du cercle en y</param>
	CollisionCircle(const float radius, const float posX, const float posY);

	/// <summary>
	/// Vérifie si le cercle entre en collision avec celui entré en paramètre
	/// </summary>
	/// <param name="otherCircle">Cercle de collision à vérifier</param>
	/// <returns>Vrai s'il y a collision, faux sinon</returns>
	bool checkCollision(const CollisionCircle &otherCircle) const;
	
	/// <summary>
	/// Obtient le rayon du cercle
	/// </summary>
	/// <returns>Rayon du cercle</returns>
	float getRadius() const;

	/// <summary>
	/// Obtient la position du cercle en x
	/// </summary>
	/// <returns>Position du cercle en x</returns>
	float getPosX() const;

	/// <summary>
	/// Obtient la position du cercle en y
	/// </summary>
	/// <returns>Position du cercle en y</returns>
	float getPosY() const;

private:	
	/// <summary>
	/// Rayon du cercle
	/// </summary>
	float radius;	

	/// <summary>
	///  Position du cercle en x
	/// </summary>
	float posX;	

	/// <summary>
	/// Position du cercle en y
	/// </summary>
	float posY;
};


