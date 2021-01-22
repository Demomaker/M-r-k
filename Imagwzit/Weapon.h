#pragma once
#include "Enums.h"

class Weapon
{
public:	
	/// <summary>
	/// Constructeur d'arme
	/// </summary>
	/// <param name="fireRate">La cadence de tir.</param>
	/// <param name="ammo">L'ammo.</param>
	/// <param name="projectileType">Le type de projectile.</param>
	Weapon(const float & fireRate, const int & ammo, const ProjectileType & projectileType);
	
	/// <summary>
	/// Ajouter de l'ammo
	/// </summary>
	/// <param name="value">La quantité d'ammo à ajouter</param>
	void addAmmo(const int & value);
	
	/// <summary>
	/// Obtenir la quantité d'ammo d'en ce moment
	/// </summary>
	/// <returns>la quantité d'ammo</returns>
	int getCurrentAmmo() const;
	
	/// <summary>
	/// La cadence de tir
	/// </summary>
	const float FIRE_RATE;
	
	/// <summary>
	/// Le type de projectile
	/// </summary>
	const ProjectileType PROJECTILE_TYPE;
private:	
	/// <summary>
	/// La quantité d'amoo
	/// </summary>
	int ammo;
};

