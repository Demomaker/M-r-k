#pragma once
#include "Enemy.h"
#include "Constants.h"
class SceneGame;

/// <summary>
/// Repr�sente le concept logique et graphique d'un zombie dans l'espace de jeu
/// </summary>
/// <seealso cref="Character" />
class Zombie : public Enemy
{
public:	
	/// <summary>
	/// Constructeur d'un zombie
	/// </summary>
	Zombie();

	/// <summary>
	/// Initialise les composants utiles � la classe
	/// </summary>
	/// <returns>Vrai lorsque l'initialisation a fonctionn�, faux sinon</returns>
	static bool init();	

	/// <summary>
	/// Met � jour le zombie
	/// </summary>
	/// <param name="playerPosition">La position du joueur</param>
	/// <param name="playerIsActive">Le joueur est en vie ou non</param>
	/// <param name="timeSpend">Le temps �coul� � la derni�re frame</param>
	void update(const float& timeSpend, SceneGame & scene) override;

private:

	/// <summary>
	/// Vitesse du zombie
	/// </summary>
	const static int MOVE_SPEED = 1;

	/// <summary>
	/// Tableau des textures de zombie disponibles en jeu
	/// </summary>
	static sf::Texture zombieT[3];
};

