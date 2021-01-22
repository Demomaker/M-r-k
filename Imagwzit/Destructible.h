#pragma once
#include "GameObject.h"

class Destructible : public GameObject
{
public:	
	/// <summary>
	/// Constructeur d'un �l�ment destructible
	/// </summary>
	/// <param name="maxHealth"> La vie maximale</param>
	Destructible(const int & maxHealth);	
	
	/// <summary>
	/// Ajouter de la vie � l'�l�ment
	/// </summary>
	/// <param name="value">quantit� de vie</param>
	void addHealth(const float & value);
	
	/// <summary>
	/// Obtenir la vie.
	/// </summary>
	/// <returns>La vie de l'�l�ment</returns>
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

