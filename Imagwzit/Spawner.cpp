#include "Spawner.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Constants.h"

/// <summary>
/// Texture du spawner
/// </summary>
sf::Texture Spawner::texture;

/// <summary>
/// Constructeur de spawner
/// </summary>
Spawner::Spawner() : Destructible(100)
{
	setTexture(texture);
	timeSinceLastSpawn.restart();
	Subject::addObserver(this);
}

/// <summary>
/// Être notifié selon un certain sujet.
/// </summary>
/// <param name="subject">Le sujet.</param>
void Spawner::notify(Subject * subject)
{
	if (typeid(*subject) == typeid(PowerUp::Bomb))
	{
		//Casting de notre sujet dans son bon type... vive le polymorphisme
		PowerUp::Bomb * bomb = static_cast<PowerUp::Bomb*>(subject);
		int diffY = bomb->getPosition().y - getPosition().y;
		int diffX = bomb->getPosition().x - getPosition().x;
		int distance = sqrt((diffY * diffY) + (diffX * diffX));
		addHealth(-std::max((400 - distance) / 2, 0));
		if (getHealth() <= 0)
		{
			// Détruire le spawner si près de la bombe
			setActive(false);
		}
	}
}

/// <summary>
/// Charger la texture
/// </summary>
/// <returns>true si tout est correct, false sinon</returns>
bool Spawner::loadTexture()
{
	if (!texture.loadFromFile("Sprites\\FreeArt\\spawner.png"))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Faire apparaître un ennemi.
/// </summary>
/// <param name="enemy">The enemy.</param>
void Spawner::spawnEnemy(EnemyType enemy)
{
	if (timeSinceLastSpawn.getElapsedTime().asSeconds() > 3) {

		if (enemy == EnemyType::ZOMBIE) 
		{
			Enemy::spawnAZombie(getPosition() + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		}
		if (enemy == EnemyType::GHOST) {
			Enemy::spawnAGhost(getPosition() + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		}
		if (enemy == EnemyType::SPIDER) {
			Enemy::spawnASpider(getPosition() + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		}
		if (enemy == EnemyType::SKELETON) {
			Enemy::spawnASkeleton(getPosition() + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		}
		if (enemy == EnemyType::BOMBERMAN) {
			Enemy::spawnABomberman(getPosition() + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		}
		timeSinceLastSpawn.restart();
	}
}

/// <summary>
/// Destructeur de spawner
/// </summary>
Spawner::~Spawner()
{
	Subject::removeObserver(this);
}
