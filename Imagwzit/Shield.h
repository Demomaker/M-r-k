#pragma once
#include<SFML/Graphics.hpp>

class Shield
{
public:	
	/// <summary>
	/// Constructeur de shield
	/// </summary>
	/// <param name="resistance">La r�sistance du shield.</param>
	/// <param name="color">La couleur du shield.</param>
	Shield(const int & resistance, const sf::Color & color);
	
	/// <summary>
	/// Prendre des dommages
	/// </summary>
	/// <param name="damage">Le nombre de dommages � prendre.</param>
	/// <returns>La r�sistance restante</returns>
	int takeDamage(const float & damage);
	
	/// <summary>
	/// Obtenir la couleur du shield
	/// </summary>
	/// <returns>La couleur du bouclier</returns>
	const sf::Color & getColor() const;
	
	/// <summary>
	/// Obtenir la r�sistance en ce moment
	/// </summary>
	/// <returns>La r�sistance en ce moment</returns>
	int getCurrentResistance() const;
	
	/// <summary>
	/// La r�sistance maximale
	/// </summary>
	const int MAX_RESISTANCE = 3;
	
	/// <summary>
	/// Ajouter de la r�sistance.
	/// </summary>
	/// <param name="value">La quantit� de r�sistance � ajouter.</param>
	/// <returns>La quantit� de r�sistance</returns>
	int addResistance(const int& value);
private:	
	/// <summary>
	/// Le r�sistance du shield
	/// </summary>
	int resistance;
	
	/// <summary>
	/// La couleur du shield
	/// </summary>
	const sf::Color color;
};

