#include "Weapon.h"
#include <algorithm>
#include "Constants.h"

/// <summary>
/// Constructeur d'arme
/// </summary>
/// <param name="fireRate">La cadence de tir.</param>
/// <param name="ammo">L'ammo.</param>
/// <param name="projectileType">Le type de projectile.</param>
Weapon::Weapon(const float & fireRate, const int & ammo, const ProjectileType & projectileType) : FIRE_RATE(fireRate), ammo(ammo), PROJECTILE_TYPE(projectileType)
{
}

/// <summary>
/// Ajouter de l'ammo
/// </summary>
/// <param name="value">La quantité d'ammo à ajouter</param>
void Weapon::addAmmo(const int & value)
{
	ammo = std::min(value + ammo, MAX_NB_AMMO_WEAPON);
}

/// <summary>
/// Obtenir la quantité d'ammo d'en ce moment
/// </summary>
/// <returns>la quantité d'ammo</returns>
int Weapon::getCurrentAmmo() const
{
	return ammo;
}
