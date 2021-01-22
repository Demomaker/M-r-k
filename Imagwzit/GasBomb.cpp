#include "GasBomb.h"

/// <summary>
/// Constructeur d'une bombe de gaz
/// </summary>
PowerUp::GasBomb::GasBomb()
{
	setTexture(bonusT[BonusType::GasBombType]);
}

/// <summary>
/// Active le bonus par le joueur
/// </summary>
void PowerUp::GasBomb::pickUp()
{
	pickedByPlayer = true;
	Bonus::pickUp();
}

/// <summary>
/// Active le bonus par un ennemi
/// </summary>
void PowerUp::GasBomb::enemyPickUp() 
{
	pickedByPlayer = false;
	Bonus::pickUp();
}

/// <summary>
///  D�termine si la bombe a �t� prise par le joueur ou non
/// </summary>
/// <return>Bombe r�cup�r�e par le joueur</return>
bool PowerUp::GasBomb::isPickedByPlayer() const
{
	return pickedByPlayer;
}
