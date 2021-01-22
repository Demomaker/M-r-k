#include "Star.h"

/// <summary>
/// Constructeur d'une étoile
/// </summary>
PowerUp::Star::Star()
{
	setTexture(bonusT[BonusType::StarType]);
}

/// <summary>
/// Active le bonus
/// </summary>
void PowerUp::Star::pickUp()
{
	Bonus::pickUp();
}
