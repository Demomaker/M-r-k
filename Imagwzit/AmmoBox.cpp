#include "AmmoBox.h"

/// <summary>
/// Constructeur d'une boîte de munitions
/// </summary>
/// <param name="ammoType">Type de boîte de munitions</param>
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
/// Obtient le type de la boîte de munitions
/// </summary>
/// <return>Le type de la boîte de munitions</return>
BonusType PowerUp::AmmoBox::getAmmoBoxType() const
{
	return ammoType;
}
