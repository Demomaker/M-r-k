#pragma once
#include "Enums.h"
#include "Destructible.h"
#include "IObserver.h"

/// <summary>
/// Repr�sente le concept logique et graphique d'un spawner en jeu
/// </summary>
class Spawner : public Destructible, IObserver
{
public:	
	/// <summary>
	/// Constructeur de spawner
	/// </summary>
	Spawner();	

	/// <summary>
	/// �tre notifi� selon un certain sujet.
	/// </summary>
	/// <param name="subject">Le sujet.</param>
	void notify(Subject * subject) override;
	
	/// <summary>
	/// Charger la texture
	/// </summary>
	/// <returns>true si tout est correct, false sinon</returns>
	static bool loadTexture();
	
	/// <summary>
	/// Faire appara�tre un ennemi.
	/// </summary>
	/// <param name="enemy">The enemy.</param>
	void spawnEnemy(EnemyType enemy);
	
	/// <summary>
	/// Destructeur de spawner
	/// </summary>
	~Spawner();
private:
	/// <summary>
	/// Texture du spawner
	/// </summary>
	static sf::Texture texture;

	/// <summary>
	/// Composant pour g�rer le temps d'apparition des ennemis
	/// </summary>
	sf::Clock timeSinceLastSpawn;
};

