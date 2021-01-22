#include "Destructible.h"


/// <summary>
/// Constructeur d'un élément destructible
/// </summary>
/// <param name="maxHealth"> La vie maximale</param>
Destructible::Destructible(const int & maxHealth) : MAX_HEALTH(maxHealth), health(maxHealth)
{
}

/// <summary>
/// Ajouter de la vie à l'élément
/// </summary>
/// <param name="value">quantité de vie</param>
void Destructible::addHealth(const float & value)
{
	health = std::max(0.0f, std::min(health + value, (float)MAX_HEALTH));
}

/// <summary>
/// Obtenir la vie.
/// </summary>
/// <returns>La vie de l'élément</returns>
int Destructible::getHealth()
{
	return health;
}
