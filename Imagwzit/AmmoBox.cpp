#include "AmmoBox.h"

/// <summary>
/// Constructeur d'une bo�te de munitions
/// </summary>
/// <param name="ammoType">Type de bo�te de munitions</param>
PowerUp::AmmoBox::AmmoBox(BonusType ammoType)
{
	setTexture(bonusT[ammoType]);
	this->ammoType = ammoType;
}

/// <summary>
/// Active le bonus
/// </summary>
void PowerUp::AmmoBox::pickUp()
{
	Bonus::pickUp();
}

/// <summary>
/// Obtient le type de la bo�te de munitions
/// </summary>
/// <return>Le type de la bo�te de munitions</return>
BonusType PowerUp::AmmoBox::getAmmoBoxType() const
{
	return ammoType;
}
