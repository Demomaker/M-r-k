#include "Shield.h"


/// <summary>
/// Constructeur de shield
/// </summary>
/// <param name="resistance">La résistance du shield.</param>
/// <param name="color">La couleur du shield.</param>
Shield::Shield(const int & resistance, const sf::Color & color) : resistance(resistance), color(color)
{
}

/// <summary>
/// Prendre des dommages
/// </summary>
/// <param name="damage">Le nombre de dommages à prendre.</param>
/// <returns>La résistance restante</returns>
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
/// Obtenir la résistance en ce moment
/// </summary>
/// <returns>La résistance en ce moment</returns>
int Shield::getCurrentResistance() const
{
	return resistance;
}

/// <summary>
/// Ajouter de la résistance
/// </summary>
/// <param name="value">La quantité de résistance à ajouter.</param>
/// <returns>La quantité de résistance qui n'a pas été ajoutée</returns>
int Shield::addResistance(const int & value)
{
	// On ajoute la résistance et on retourne celle qui n'a pas été ajoutée
	int newResistance = resistance + value;
	resistance = std::min(MAX_RESISTANCE, newResistance);
	return std::max(0, newResistance - resistance);
}
