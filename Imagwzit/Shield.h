#pragma once
#include<SFML/Graphics.hpp>

class Shield
{
public:	
	/// <summary>
	/// Constructeur de shield
	/// </summary>
	/// <param name="resistance">La résistance du shield.</param>
	/// <param name="color">La couleur du shield.</param>
	Shield(const int & resistance, const sf::Color & color);
	
	/// <summary>
	/// Prendre des dommages
	/// </summary>
	/// <param name="damage">Le nombre de dommages à prendre.</param>
	/// <returns>La résistance restante</returns>
	int takeDamage(const float & damage);
	
	/// <summary>
	/// Obtenir la couleur du shield
	/// </summary>
	/// <returns>La couleur du bouclier</returns>
	const sf::Color & getColor() const;
	
	/// <summary>
	/// Obtenir la résistance en ce moment
	/// </summary>
	/// <returns>La résistance en ce moment</returns>
	int getCurrentResistance() const;
	
	/// <summary>
	/// La résistance maximale
	/// </summary>
	const int MAX_RESISTANCE = 3;
	
	/// <summary>
	/// Ajouter de la résistance.
	/// </summary>
	/// <param name="value">La quantité de résistance à ajouter.</param>
	/// <returns>La quantité de résistance</returns>
	int addResistance(const int& value);
private:	
	/// <summary>
	/// Le résistance du shield
	/// </summary>
	int resistance;
	
	/// <summary>
	/// La couleur du shield
	/// </summary>
	const sf::Color color;
};

