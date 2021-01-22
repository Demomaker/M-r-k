#pragma once
#include "Destructible.h"

/// <summary>
/// Repr�sente le concept logique et graphique d'un personnage en jeu
/// </summary>
/// <seealso cref="GameObject" />
class Character : public Destructible
{
public:
	/// <summary>
	/// Constructeur d'un personnage
	/// </summary>
	Character(const int & maxHealth);
	
	/// <summary>
	/// Met � jour l'orientation du personnage et l'emp�che de sortir de la zone de jeu
	/// </summary>
	void update();

protected:
	/// <summary>
	/// Vitesse du personnage
	/// </summary>
	float speed;

	/// <summary>
	/// Orientation du personnage
	/// </summary>
	float spriteAngle;
	
	/// <summary>
	/// Orientation de l'arme du personnage
	/// </summary>
	float weaponAngle;
	
	/// <summary>
	/// Le mouvement du personnage
	/// </summary>
	sf::Vector2f movement;


};

