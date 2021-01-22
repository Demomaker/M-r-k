#include "Destructible.h"


/// <summary>
/// Constructeur d'un �l�ment destructible
/// </summary>
/// <param name="maxHealth"> La vie maximale</param>
Destructible::Destructible(const int & maxHealth) : MAX_HEALTH(maxHealth), health(maxHealth)
{
}

/// <summary>
/// Ajouter de la vie � l'�l�ment
/// </summary>
/// <param name="value">quantit� de vie</param>
void Destructible::addHealth(const float & value)
{
	health = std::max(0.0f, std::min(health + value, (float)MAX_HEALTH));
}

/// <summary>
/// Obtenir la vie.
/// </summary>
/// <returns>La vie de l'�l�ment</returns>
int Destructible::getHealth()
{
	return health;
}
