#pragma once
#include "Character.h"
#include "IObserver.h"
#include "Enums.h"

class SceneGame;
class Subject;

/// <summary>
/// Représente le concept logique et graphique d'un zombie dans l'espace de jeu
/// </summary>
/// <seealso cref="Character" />
class Enemy : public Character, public IObserver
{
public:
	/// <summary>
	/// Constructeur d'un zombie
	/// </summary>
	/// <param name="maxHealth">Les points de vu max de l'ennemi</param>
	Enemy(const int & maxHealth);

	/// <summary>
	/// Destructeur d'un ennemi
	/// </summary>
	~Enemy();
	
	/// <summary>
	/// Obtenir le type de projectile.
	/// </summary>
	/// <returns>Le type de projectile</returns>
	ProjectileType getProjectileType() const;
	
	/// <summary>
	/// Notifier selon un certain sujet
	/// </summary>
	/// <param name="subject">le sujet qui a notifié.</param>
	void notify(Subject * subject) override;
	
	/// <summary>
	/// Libère les ressources
	/// </summary>
	static void release();
	
	/// <summary>
	/// Faire apparaître l'ennemi à une certaine position
	/// </summary>
	/// <param name="pos">La position.</param>
	void spawn(const sf::Vector2f& pos);

	/// <summary>
	/// Vérifie s'il y a une collision entre les ennemis et le cercle de collision spécifié
	/// </summary>
	/// <param name="otherCollisionCircle">Cercle de collision à tester</param>
	/// <returns>Vrai si un zombie entre en collision avec le cercle, faux sinon</returns>
	static bool checkCollisionWith(const CollisionCircle& otherCollisionCircle);
	
	/// <summary>
	/// Faire apparaître un zombie.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnAZombie(const sf::Vector2f& pos);

	/// <summary>
	/// Faire apparaître un fantôme.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnAGhost(const sf::Vector2f& pos);

	/// <summary>
	/// Faire apparaître une araignée.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnASpider(const sf::Vector2f& pos);

	/// <summary>
	/// Faire apparaître un squelette.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnASkeleton(const sf::Vector2f& pos);

	/// <summary>
	/// Faire apparaître un bomberman.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnABomberman(const sf::Vector2f & pos);

	/// <summary>
	/// Met à jour l'ennemi
	/// </summary>
	virtual void update(const float& timeSpend, SceneGame & scene);

	/// <summary>
	/// Met à jour les instances de la classe qui sont actives
	/// </summary>
	/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
	/// <param name="game">Instance de la partie</param>
	static void updateActiveInstances(const float & timeSpend, SceneGame & game);
	
	/// <summary>
	/// Initialiser la classe
	/// </summary>
	/// <returns>Vrai si succès, faux sinon</returns>
	static bool init();
	
	/// <summary>
	/// Obtenir la couleur de l'ennemi.
	/// </summary>
	/// <returns>La couleur de l'ennemi</returns>
	sf::Color getColor();

protected:	
	/// <summary>
	/// Le type de projectile
	/// </summary>
	ProjectileType projectileType;
	
	/// <summary>
	/// Booléen représentant si l'ennemi est en réduction de vitesse
	/// </summary>
	bool isSlowed = false;
	
	/// <summary>
	/// La couleur de l'ennemi
	/// </summary>
	sf::Color color;
private:
	/// <summary>
	/// Tableau des instances de la classe
	/// </summary>
	static std::list<Enemy*> instances;
	
	/// <summary>
	/// Le temps qui reste à l'ennemi pour être en réduction de vitesse
	/// </summary>
	float remainingSlowedTime = 0;
};

