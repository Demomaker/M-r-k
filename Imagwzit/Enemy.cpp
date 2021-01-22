#include "Enemy.h"
#include "Subject.h"
#include "Skeleton.h"
#include "Zombie.h"
#include "Spider.h"
#include "Ghost.h"
#include "SceneGame.h"
#include "ScoreIndicator.h"
#include "GasBomb.h"
#include "Bomb.h"
#include "Bomberman.h"

/// <summary>
/// Liste des instances de la classe
/// </summary>
std::list<Enemy*> Enemy::instances;

/// <summary>
/// Constructeur d'un zombie
/// </summary>
/// <param name="maxHealth">Les points de vu max de l'ennemi</param>
Enemy::Enemy(const int & maxHealth) : Character(maxHealth)
{
	// Déterminer aléatoirement sa couleur
	int randColor = rand() % 3;
	if (randColor == 0)
	{
		color = sf::Color::Red;
	}
	if (randColor == 1)
	{
		color = sf::Color::Blue;
	}
	if (randColor == 2)
	{
		color = sf::Color::Green;
	}
	this->setColor(color);
	Subject::addObserver(this);
}

/// <summary>
/// Destructeur d'un ennemi
/// </summary>
Enemy::~Enemy()
{
	Subject::removeObserver(this);
}

/// <summary>
/// Obtenir le type de projectile.
/// </summary>
/// <returns>Le type de projectile</returns>
ProjectileType Enemy::getProjectileType() const
{
	return projectileType;
}

/// <summary>
/// Notifier selon un certain sujet
/// </summary>
/// <param name="subject">le sujet qui a notifié.</param>
void Enemy::notify(Subject * subject)
{
	if (typeid(*subject) == typeid(PowerUp::GasBomb))
	{
		PowerUp::GasBomb * gasBomb = static_cast<PowerUp::GasBomb*>(subject);
		if (gasBomb->isPickedByPlayer())
		{
			// Bombe ramassée par le joueur. Ralentit les ennemis pendant quelques secondes. Si des acteurs peuvent tirer, ils ne tirent plus pendant la même période.
			remainingSlowedTime = GAS_BOMB_DURATION;
			isSlowed = true;
			speed /= 2;
		}
	}
	else if (typeid(*subject) == typeid(PowerUp::Bomb))
	{
		//Casting de notre sujet dans son bon type... vive le polymorphisme
		PowerUp::Bomb * bomb = static_cast<PowerUp::Bomb*>(subject);
		if (color == sf::Color::Red && bomb->getBombType() == BonusType::RedBombType
			|| color == sf::Color::Blue && bomb->getBombType() == BonusType::BlueBombType
			|| color == sf::Color::Green && bomb->getBombType() == BonusType::GreenBombType) {
			int diffY = bomb->getPosition().y - getPosition().y;
			int diffX = bomb->getPosition().x - getPosition().x;
			int distance = sqrt((diffY * diffY) + (diffX * diffX));
			if (distance <= 300)
			{
				// L'ennemi meurt si trop près de la bombe
				setActive(false);
			}
		}
	}
}

/// <summary>
/// Libère les ressources
/// </summary>
void Enemy::release()
{
	for (auto instance : instances) 
	{
		delete instance;
	}
	instances.clear();
}

/// <summary>
/// Faire apparaître l'ennemi à une certaine position
/// </summary>
/// <param name="pos">La position.</param>
void Enemy::spawn(const sf::Vector2f & pos)
{
	setPosition(pos);
	// On le met actif s'il ne spawn pas sur un acteur
	setActive(!GameObject::detectCollisionWithOthers(this));
}

/// <summary>
/// Vérifie s'il y a une collision entre les enemis et le cercle de collision spécifié
/// </summary>
/// <param name="otherCollisionCircle">Cercle de collision à tester</param>
/// <returns>Vrai si un zombie entre en collision avec le cercle, faux sinon</returns>
bool Enemy::checkCollisionWith(const CollisionCircle& otherCollisionCircle)
{
	for (auto instance : instances)
	{
		if (instance->isActive() && otherCollisionCircle.checkCollision(instance->getCollisionCircle()))
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// Faire apparaître un zombie.
/// </summary>
/// <param name="pos">La position.</param>
void Enemy::spawnAZombie(const sf::Vector2f& pos)
{
	for (auto instance : instances) 
	{
		if (!instance->isActive() && typeid(*instance) == typeid(Zombie)) 
		{
			instance->spawn(pos);
			return;
		}
	}
}

/// <summary>
/// Faire apparaître un fantôme.
/// </summary>
/// <param name="pos">La position.</param>
void Enemy::spawnAGhost(const sf::Vector2f& pos)
{
	for (auto instance : instances)
	{
		if (!instance->isActive() && typeid(*instance) == typeid(Ghost))
		{
			instance->spawn(pos);
			return;
		}
	}
}

/// <summary>
/// Faire apparaître une araignée.
/// </summary>
/// <param name="pos">La position.</param>
void Enemy::spawnASpider(const sf::Vector2f& pos)
{
	for (auto instance : instances)
	{
		if (!instance->isActive() && typeid(*instance) == typeid(Spider))
		{
			instance->spawn(pos);
			return;
		}
	}
}

/// <summary>
/// Faire apparaître un squelette.
/// </summary>
/// <param name="pos">La position.</param>
void Enemy::spawnASkeleton(const sf::Vector2f& pos)
{
	for (auto instance : instances)
	{
		if (!instance->isActive() && typeid(*instance) == typeid(Skeleton))
		{
			instance->spawn(pos);
			return;
		}
	}
}

/// <summary>
/// Faire apparaître un bomberman.
/// </summary>
/// <param name="pos">La position.</param>
void Enemy::spawnABomberman(const sf::Vector2f& pos)
{
	for (auto instance : instances)
	{
		if (!instance->isActive() && typeid(*instance) == typeid(Bomberman))
		{
			instance->spawn(pos);
			return;
		}
	}
}

/// <summary>
/// Met à jour les instances de la classe qui sont actives
/// </summary>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
/// <param name="game">Instance de la partie</param>
void Enemy::updateActiveInstances(const float & timeSpend, SceneGame & game)
{
	// Mettre a jour toutes les instances de la classe
	for (auto instance: instances)
	{
		instance->update(timeSpend, game);
	}
}

/// <summary>
/// Initialiser la classe
/// </summary>
/// <returns>Vrai si succès, faux sinon</returns>
bool Enemy::init()
{
	if (!Skeleton::init()) {
		return false;
	}
	if (!Spider::init()) {
		return false;
	}
	if (!Ghost::init()) {
		return false;
	}
	if (!Zombie::init())
	{
		return false;
	}
	if (!Bomberman::init()) {
		return false;
	}

	//Initialiser les différents ennemis
	for (int i = 0; i < MAX_NB_ZOMBIES; i++) 
	{
		instances.push_back(new Zombie());
	}

	for (int i = 0; i < MAX_NB_GHOSTS; i++)
	{
		instances.push_back(new Ghost());
	}

	for (int i = 0; i < MAX_NB_SKELETONS; i++)
	{
		instances.push_back(new Skeleton());
	}

	for (int i = 0; i < MAX_NB_SPIDERS; i++)
	{
		instances.push_back(new Spider());
	}

	for (int i = 0; i < MAX_NB_BOMBERMANS; i++)
	{
		instances.push_back(new Bomberman());
	}

	return true;
}

/// <summary>
/// Obtenir la couleur de l'ennemi.
/// </summary>
/// <returns>La couleur de l'ennemi</returns>
sf::Color Enemy::getColor()
{
	return color;
}

/// <summary>
/// Met à jour l'ennemi
/// </summary>
void Enemy::update(const float& timeSpend, SceneGame & scene)
{
	if (isSlowed) 
	{
		// Si l'ennemi est ralenti
		remainingSlowedTime -= timeSpend / FRAMES_PER_SECOND;
		if (remainingSlowedTime <= 0) 
		{
			// Mettre fin au ralentissement
			isSlowed = false;
			speed *= 2;
		}
	}

	if (typeid(*this) != typeid(Ghost) && GameObject::detectCollisionWithOthers(this))
	{
		// Empêcher de traverser les autres acteurs sauf pour le fantôme
		move(-movement);
	}

	Projectile * proj = Projectile::checkCollisionWith(*this);
	//Si l'ennemi entre en collision avec un projectile
	if (proj != nullptr)
	{
		if (proj->isShotByPlayer())
		{
			setActive(false);
			if (proj->getType() != ProjectileType::Missile && proj->getType() != ProjectileType::Flame && proj->getType() != ProjectileType::Laser)
				proj->setActive(false);
			// On fait apparaître le score gagné par le joueur à la position du zombie
			ScoreIndicator::spawnAScoreIndicator(getPosition(), Player::getInstance()->addAKill());
			if (rand() % 100 / BONUS_PROBABILITY_ON_100 == 0)
			{
				// On fait apparaître un bonus à l'emplacement du zombie
				PowerUp::Bonus::spawnABonus(getPosition());
			}
			scene.updateUI();
		}
	}

	Character::update();
}
