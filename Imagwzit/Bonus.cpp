#include "Bonus.h"
#include "Constants.h"
#include "AmmoBox.h"
#include "Star.h"
#include "ScoreMultiplier.h"
#include "ShieldBonus.h"
#include "Bomb.h"
#include "GasBomb.h"
#include "ContainerFactory.h"
#include "Player.h"
#include "Enemy.h"

/// <summary>
/// Tableau qui contient les textures des bonus disponibles en jeu
/// </summary>
sf::Texture PowerUp::Bonus::bonusT[14];

/// <summary>
/// Liste des instances de la classe
/// </summary>
CircularDoubleLinkedList<PowerUp::Bonus> * PowerUp::Bonus::instances;

/// <summary>
/// Constructeur d'un bonus
/// </summary>
PowerUp::Bonus::Bonus() 
{
	setOrigin(POWER_UP_SIZE / 2, POWER_UP_SIZE / 2);
}

/// <summary>
/// Initialise les diff�rents composants de la classe
/// </summary>
/// <returns>Succ�s de l'initialisation</returns>
bool PowerUp::Bonus::init()
{
	if (!bonusT[0].loadFromFile("Sprites\\Logos\\StarLogo.png"))
	{
		return false;
	}

	if (!bonusT[1].loadFromFile("Sprites\\Logos\\ScoreMultiplierLogo.png"))
	{
		return false;
	}

	if (!bonusT[2].loadFromFile("Sprites\\Logos\\FlameLogo.png"))
	{
		return false;
	}

	if (!bonusT[3].loadFromFile("Sprites\\Logos\\MissileLogo.png"))
	{
		return false;
	}

	if (!bonusT[4].loadFromFile("Sprites\\Logos\\ScatterLogo.png"))
	{
		return false;
	}

	if (!bonusT[5].loadFromFile("Sprites\\Logos\\RocketLauncherLogo.png"))
	{
		return false;
	}

	if (!bonusT[6].loadFromFile("Sprites\\Logos\\LaserLogo.png"))
	{
		return false;
	}
	if (!bonusT[7].loadFromFile("Sprites\\Logos\\GreenShieldLogo.png"))
	{
		return false;
	}

	if (!bonusT[8].loadFromFile("Sprites\\Logos\\BlueShieldLogo.png"))
	{
		return false;
	}

	if (!bonusT[9].loadFromFile("Sprites\\Logos\\RedShieldLogo.png"))
	{
		return false;
	}

	if (!bonusT[10].loadFromFile("Sprites\\Logos\\GreenBombLogo.png"))
	{
		return false;
	}

	if (!bonusT[11].loadFromFile("Sprites\\Logos\\BlueBombLogo.png"))
	{
		return false;
	}

	if (!bonusT[12].loadFromFile("Sprites\\Logos\\RedBombLogo.png"))
	{
		return false;
	}

	if (!bonusT[13].loadFromFile("Sprites\\Logos\\GasBombLogo.png"))
	{
		return false;
	}

	instances = ContainerFactory<Bonus>::getCircularDoubleLinkedList();

	// On charge tous les bonus en m�moire
	for (int i = 0; i < MAX_NB_OF_EACH_BONUS; i++)
	{
		instances->add_start(new AmmoBox(FlameAmmoBoxType));
		instances->add_start(new AmmoBox(ScatterAmmoBoxType));
		instances->add_start(new AmmoBox(MissileAmmoBoxType));
		instances->add_start(new AmmoBox(RocketLauncherAmmoBoxType));
		instances->add_start(new AmmoBox(LaserAmmoBoxType));
		instances->add_start(new Star());
		instances->add_start(new ScoreMultiplier());
		instances->add_start(new Shield(BlueShieldType));
		instances->add_start(new Shield(GreenShieldType));
		instances->add_start(new Shield(RedShieldType));
		instances->add_start(new Bomb(GreenBombType));
		instances->add_start(new Bomb(RedBombType));
		instances->add_start(new Bomb(BlueBombType));
		instances->add_start(new GasBomb());
	}

	return true;
}

/// <summary>
/// Lib�re les ressources utilis�es par la classe
/// </summary>
void PowerUp::Bonus::release()
{
	int nbBonus = instances->getSize();
	for (int i = 0; i < nbBonus; i++)
	{
		delete instances->remove_end();
	}
	delete instances;
}


/// <summary>
/// D�termine si le bonus est en collision avec le cercle de collision sp�cifi�
/// </summary>
/// <param name="otherCollisionCircle">Cercle de collision � tester</param>
/// <returns>Vrai s'il y a une collision, faux sinon</returns>
bool PowerUp::Bonus::checkCollisionWith(const CollisionCircle & otherCollisionCircle) const
{
	return getCollisionCircle().checkCollision(otherCollisionCircle);
}

/// <summary>
/// Met � jour les instances de la classe
/// </summary>
void PowerUp::Bonus::updateInstances()
{
	for (auto it = instances->begin(); it != instances->end(); ++it) 
	{
		// Pour toutes les instances actives en jeu
		if ((*it).isActive()) 
		{
			if (typeid(*it) == typeid(Bomb) && GameObject::detectCollisionWithOthers(&(*it)))
			{
				// La bombe explose d�s qu'il y a une collision
				(*it).pickUp();
			}
			else if ((*it).checkCollisionWith(Player::getInstance()->getCollisionCircle()))
			{
				// On teste si le bonus est ramass� par le joueur
				(*it).pickUp();
			}
			else if (typeid(*it) == typeid(GasBomb) && Enemy::checkCollisionWith((*it).getCollisionCircle()))
			{
				// On teste si la bombe de gas est ramass�e par un ennemi
				GasBomb * gasBomb = static_cast<GasBomb*>(&(*it));
				gasBomb->enemyPickUp();
			}
		}
	}
}

/// <summary>
/// Fait appara�tre un bonus en jeu
/// </summary>
/// <param name="zombiePosition">Position � laquelle on fait appara�tre le bonus</param>
void PowerUp::Bonus::spawnABonus(const sf::Vector2f& pos)
{
	auto it = instances->begin();
	for (int i = rand() % instances->getSize(); i > 0; i--)
	{
		it++;
	}
	// On d�bute � une position al�atoire dans la liste des bonus
	auto startPosition = it;
	for (int i = 0; i < instances->getSize(); i++) 
	{
		it++;
		if ((it) == nullptr)
		{
			it = instances->begin();
		}
		if (!(*it).isActive()) 
		{
			// On fait appara�tre le bonus s'il n'est pas d�j� actif
			(*it).spawn(pos);
			break;
		}
	}
}

/// <summary>
/// Active le bonus
/// </summary>
void PowerUp::Bonus::pickUp()
{
	Subject::notifyAllObservers();
	setActive(false);
}

/// <summary>
/// Fait appara�tre un bonus en jeu
/// </summary>
/// <param name="position">Position � laquelle on fait appara�tre le bonus</param>
void PowerUp::Bonus::spawn(const sf::Vector2f& pos)
{
	setPosition(pos);
	setActive(true);
}
