#include "DestructableWall.h"
#include "Bomb.h"
#include "Map.h"

/// <summary>
/// Texture du mur
/// </summary>
sf::Texture DestructableWall::texture;

/// <summary>
/// IntRect
/// </summary>
sf::IntRect DestructableWall::intRect;

/// <summary>
/// Constructeur de mur destructible
/// </summary>
DestructableWall::DestructableWall() : Destructible(100)
{
	setTexture(texture);
	setTextureRect(intRect);
	Subject::addObserver(this);
}

/// <summary>
/// Se fait notifier avec un certain sujet
/// </summary>
/// <param name="subject">Le sujet qui a notifié.</param>
void DestructableWall::notify(Subject * subject)
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
			// On détruit le mur si les dommages sont suffisants
			IntMap::getInstance()->setElement(positionOnMap.x,
				positionOnMap.y, 0);
			setActive(false);
		}
	}
}

/// <summary>
/// Charger la texture.
/// </summary>
/// <returns>true si c'est correct, faux sinon</returns>
bool DestructableWall::loadTexture()
{
	if(!texture.loadFromFile("Sprites\\FreeArt\\Tiles.png"))
		return false;
	intRect.top = 0;
	intRect.left = 9 * 64;
	intRect.width = 64;
	intRect.height = 64;
	return true;
}

/// <summary>
/// Mettre la position du mur selon la carte
/// </summary>
/// <param name="position">La position.</param>
void DestructableWall::setPositionDependingOnMap(sf::Vector2f position)
{
	positionOnMap = position;
}

/// <summary>
/// Obtenir la position du mur selon la carte
/// </summary>
/// <returns>La position</returns>
sf::Vector2f DestructableWall::getPositionDependingOnMap()
{
	return positionOnMap;
}

/// <summary>
/// Le destructeur d'un mur destructible
/// </summary>
DestructableWall::~DestructableWall()
{
	Subject::removeObserver(this);
}
