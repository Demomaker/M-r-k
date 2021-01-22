#include "Shield.h"


/// <summary>
/// Constructeur de shield
/// </summary>
/// <param name="resistance">La r�sistance du shield.</param>
/// <param name="color">La couleur du shield.</param>
Shield::Shield(const int & resistance, const sf::Color & color) : resistance(resistance), color(color)
{
}

/// <summary>
/// Prendre des dommages
/// </summary>
/// <param name="damage">Le nombre de dommages � prendre.</param>
/// <returns>La r�sistance restante</returns>
int Shield::takeDamage(const float & damage)
{
	return resistance -= damage;
}

/// <summary>
/// Obtenir la couleur du shield
/// </summary>
/// <returns>La couleur du bouclier</returns>
const sf::Color & Shield::getColor() const
{
	return color;
}

/// <summary>
/// Obtenir la r�sistance en ce moment
/// </summary>
/// <returns>La r�sistance en ce moment</returns>
int Shield::getCurrentResistance() const
{
	return resistance;
}

/// <summary>
/// Ajouter de la r�sistance
/// </summary>
/// <param name="value">La quantit� de r�sistance � ajouter.</param>
/// <returns>La quantit� de r�sistance qui n'a pas �t� ajout�e</returns>
int Shield::addResistance(const int & value)
{
	// On ajoute la r�sistance et on retourne celle qui n'a pas �t� ajout�e
	int newResistance = resistance + value;
	resistance = std::min(MAX_RESISTANCE, newResistance);
	return std::max(0, newResistance - resistance);
}
