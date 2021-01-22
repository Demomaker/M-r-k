#include "Bomb.h"
#include "Explosion.h"

/// <summary>
/// Constructeur d'une bombe
/// </summary>
/// <param name="bombType">Type de bombe</param>
PowerUp::Bomb::Bomb(BonusType bombType) : bombType(bombType)
{
	setTexture(bonusT[bombType]);
}

/// <summary>
/// Active le bonus
/// </summary>
void PowerUp::Bomb::pickUp()
{
	// On fait apparaître une explosion à l'endroit de l'explosion
	Explosion::spawnAnExplosion(getPosition());
	Bonus::pickUp();
}

/// <summary>
/// Permet de notifier l'observateur
/// </summary>
/// <param name="subject">Sujet qui notifie</param>
void PowerUp::Bomb::notify(Subject * subject)
{
	if (subject == this)
	{
		// On met fin si l'observateur est le sujet
		return;
	}

	//Si le sujet est une bombe;
	if (typeid(*subject) == typeid(Bomb))
	{
		//Casting de notre sujet dans son bon type... vive le polymorphisme
		Bomb *bomb = static_cast<Bomb*>(subject);
		int diffY = bomb->getPosition().y - getPosition().y;
		int diffX = bomb->getPosition().x - getPosition().x;
		int distance = sqrt((diffY * diffY) + (diffX * diffX));
		if ((300 - distance) / 2 >= 100)
		{
			// La bombe s'active si les dégâts reçus sont supérieur ou égal à 100
			pickUp();
		}
	}
}

/// <summary>
/// Obtient le type de la bombe
/// </summary>
/// <return>Le type de la bombe</return>
BonusType PowerUp::Bomb::getBombType() const
{
	return bombType;
}
