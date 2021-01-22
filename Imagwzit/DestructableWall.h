#pragma once
#include "Destructible.h"
#include "IObserver.h"
class DestructableWall : public Destructible, IObserver
{
public:	
	/// <summary>
	/// Constructeur de mur destructible
	/// </summary>
	DestructableWall();	
	/// <summary>
	/// Se fait notifier avec un certain sujet
	/// </summary>
	/// <param name="subject">Le sujet qui a notifié.</param>
	void notify(Subject * subject) override;
	
	/// <summary>
	/// Charger la texture.
	/// </summary>
	/// <returns>true si c'est correct, faux sinon</returns>
	static bool loadTexture();
	
	/// <summary>
	/// Mettre la position du mur selon la carte
	/// </summary>
	/// <param name="position">La position.</param>
	void setPositionDependingOnMap(sf::Vector2f position);
	
	/// <summary>
	/// Obtenir la position du mur selon la carte
	/// </summary>
	/// <returns>La position</returns>
	sf::Vector2f getPositionDependingOnMap();
	
	/// <summary>
	/// Le destructeur d'un mur destructible
	/// </summary>
	~DestructableWall();
private:	
	/// <summary>
	/// Texture du mur
	/// </summary>
	static sf::Texture texture;	

	/// <summary>
	/// IntRect du mur
	/// </summary>
	static sf::IntRect intRect;
	
	/// <summary>
	/// Position du mur destructible sur la carte
	/// </summary>
	sf::Vector2f positionOnMap;
};

