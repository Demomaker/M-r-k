#pragma once
#include "Character.h"
#include "IObserver.h"
#include "Enums.h"

class SceneGame;
class Subject;

/// <summary>
/// Repr�sente le concept logique et graphique d'un zombie dans l'espace de jeu
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
	/// <param name="subject">le sujet qui a notifi�.</param>
	void notify(Subject * subject) override;
	
	/// <summary>
	/// Lib�re les ressources
	/// </summary>
	static void release();
	
	/// <summary>
	/// Faire appara�tre l'ennemi � une certaine position
	/// </summary>
	/// <param name="pos">La position.</param>
	void spawn(const sf::Vector2f& pos);

	/// <summary>
	/// V�rifie s'il y a une collision entre les ennemis et le cercle de collision sp�cifi�
	/// </summary>
	/// <param name="otherCollisionCircle">Cercle de collision � tester</param>
	/// <returns>Vrai si un zombie entre en collision avec le cercle, faux sinon</returns>
	static bool checkCollisionWith(const CollisionCircle& otherCollisionCircle);
	
	/// <summary>
	/// Faire appara�tre un zombie.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnAZombie(const sf::Vector2f& pos);

	/// <summary>
	/// Faire appara�tre un fant�me.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnAGhost(const sf::Vector2f& pos);

	/// <summary>
	/// Faire appara�tre une araign�e.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnASpider(const sf::Vector2f& pos);

	/// <summary>
	/// Faire appara�tre un squelette.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnASkeleton(const sf::Vector2f& pos);

	/// <summary>
	/// Faire appara�tre un bomberman.
	/// </summary>
	/// <param name="pos">La position.</param>
	static void spawnABomberman(const sf::Vector2f & pos);

	/// <summary>
	/// Met � jour l'ennemi
	/// </summary>
	virtual void update(const float& timeSpend, SceneGame & scene);

	/// <summary>
	/// Met � jour les instances de la classe qui sont actives
	/// </summary>
	/// <param name="timeSpend">Le temps �coul� � la derni�re frame</param>
	/// <param name="game">Instance de la partie</param>
	static void updateActiveInstances(const float & timeSpend, SceneGame & game);
	
	/// <summary>
	/// Initialiser la classe
	/// </summary>
	/// <returns>Vrai si succ�s, faux sinon</returns>
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
	/// Bool�en repr�sentant si l'ennemi est en r�duction de vitesse
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
	/// Le temps qui reste � l'ennemi pour �tre en r�duction de vitesse
	/// </summary>
	float remainingSlowedTime = 0;
};

