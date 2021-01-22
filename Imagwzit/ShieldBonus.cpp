#include "ShieldBonus.h"

/// <summary>
/// Constructeur d'un bonus de bouclier
/// </summary>
/// <param name="shieldType">Type de bouclier</param>
PowerUp::Shield::Shield(BonusType shieldType)
{
	setTexture(bonusT[shieldType]);
	this->shieldType = shieldType;
}

/// <summary>
/// Active le bonus
/// </summary>
void PowerUp::Shield::pickUp()
{
	Bonus::pickUp();
}

/// <summary>
/// Obtient le type de bouclier
/// </summary>
/// <return>Le type de bouclier</return>
BonusType PowerUp::Shield::getShieldType() const
{
	return shieldType;
}
