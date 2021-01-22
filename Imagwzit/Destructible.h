#pragma once
#include "GameObject.h"

class Destructible : public GameObject
{
public:	
	/// <summary>
	/// Constructeur d'un élément destructible
	/// </summary>
	/// <param name="maxHealth"> La vie maximale</param>
	Destructible(const int & maxHealth);	
	
	/// <summary>
	/// Ajouter de la vie à l'élément
	/// </summary>
	/// <param name="value">quantité de vie</param>
	void addHealth(const float & value);
	
	/// <summary>
	/// Obtenir la vie.
	/// </summary>
	/// <returns>La vie de l'élément</returns>
	int getHealth();

protected:	
	/// <summary>
	/// La vie
	/// </summary>
	int health;
	
	/// <summary>
	/// La vie maximale
	/// </summary>
	const int MAX_HEALTH;
};

