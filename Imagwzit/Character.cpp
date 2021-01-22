#include "Character.h"
#include "SceneGame.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Constants.h"

/// <summary>
/// Constructeur d'un personnage
/// </summary>
Character::Character(const int & maxHealth) : Destructible(maxHealth)
{
	speed = 0;
	spriteAngle = 0;
	weaponAngle = 0;
}

/// <summary>
/// Met à jour l'orientation du personnage et l'empêche de sortir de la zone de jeu
/// </summary>
void Character::update()
{
	move(movement);

	// Mettre à jour l'oorientation du personnage
	setRotation(spriteAngle * 180 / M_PI);

	// Empêcher le personnage de sortir de la zone de jeu
	if (getPosition().x < getGlobalBounds().width / 2)
	{
		setPosition(getGlobalBounds().width / 2, getPosition().y);
	}
	else if (getPosition().x > WORLD_WIDTH - getGlobalBounds().width / 2)
	{
		setPosition(WORLD_WIDTH - getGlobalBounds().width / 2, getPosition().y);
	}

	if (getPosition().y < getGlobalBounds().height / 2)
	{
		setPosition(getPosition().x, getGlobalBounds().height / 2);
	}
	else if (getPosition().y > WORLD_HEIGHT - getGlobalBounds().height / 2)
	{
		setPosition(getPosition().x, WORLD_HEIGHT - getGlobalBounds().height / 2);
	}
}
