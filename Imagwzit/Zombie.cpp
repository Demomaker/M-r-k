#include "Zombie.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneGame.h"

/// <summary>
/// Tableau des textures de zombie disponibles en jeu
/// </summary>
sf::Texture Zombie::zombieT[3];

/// <summary>
/// Constructeur d'un zombie
/// </summary>
Zombie::Zombie() : Enemy(1)
{
	speed = MOVE_SPEED;
	int random = rand() % 3;
	setTexture(zombieT[random]);
	setOrigin(zombieT[random].getSize().x / 2, zombieT[random].getSize().y / 2);
}

/// <summary>
/// Met à jour le zombie
/// </summary>
/// <param name="playerPosition">La position du joueur</param>
/// <param name="playerIsActive">Le joueur est en vie ou non</param>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
void Zombie::update(const float& timeSpend, SceneGame & scene)
{
	if (!isActive())
		return;

	Vector2f playerPosition = Player::getInstance()->getPosition();
	spriteAngle = atan2(playerPosition.y - getPosition().y, playerPosition.x - getPosition().x);

	// Le zombie change de direction si le joueur est inactif
	if (!Player::getInstance()->isActive())
		spriteAngle -= M_PI;

	// Si le zombie est presque sur le joueur
	else if (Player::getInstance()->isActive() && abs(playerPosition.y - getPosition().y) < POSITION_THRESHOLD && abs(playerPosition.x - getPosition().x) < POSITION_THRESHOLD)
	{
		setPosition(playerPosition);
		movement = Vector2f(0, 0);
	}
	else
	{
		movement = Vector2f(cos(spriteAngle) * speed, sin(spriteAngle) * speed);
		// Déplacer le zombie
		scene.isWalkableArea(movement, getPosition());
	}

	if (getCollisionCircle().checkCollision(Player::getInstance()->getCollisionCircle()))
	{
		// Inflige des dégâts au joueur s'il entre en collision avec ce dernier
		Player::getInstance()->takeDamage(1, getColor());
	}

	Enemy::update(timeSpend, scene);
}

/// <summary>
/// Initialise les composants utiles à la classe
/// </summary>
/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
bool Zombie::init()
{
	if (!zombieT[0].loadFromFile("Sprites\\FreeArt\\Zombie1.png"))
	{
		return false;
	}

	if (!zombieT[1].loadFromFile("Sprites\\FreeArt\\Zombie2.png"))
	{
		return false;
	}

	if (!zombieT[2].loadFromFile("Sprites\\FreeArt\\Zombie3.png"))
	{
		return false;
	}

	return true;
}