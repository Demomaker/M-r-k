#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionCircle.h"
#include <list>

/// <summary>
/// Représente le concept d'un objet dans l'espace de jeu
/// </summary>
/// <seealso cref="sf::Sprite" />
class GameObject : public sf::Sprite
{
public:	
	/// <summary>
	/// Constructeur d'un GameObject
	/// </summary>
	GameObject();

	/// <summary>
	/// Déconstructeur d'un GameObject
	/// </summary>
	~GameObject();

	/// <summary>
	/// Met à jour l'état du GameObject (Actif ou inactif)
	/// </summary>
	/// <param name="active">État actif ou non du GameObject</param>
	void setActive(const bool& active);

	/// <summary>
	/// Détermine si le GameObject est actif
	/// </summary>
	/// <returns>État actif ou non du GameObject</returns>
	bool isActive() const;

	/// <summary>
	/// Obtient le cercle de collision du GameObject
	/// </summary>
	/// <returns>Cercle de collision du GameObject</returns>
	CollisionCircle getCollisionCircle() const;

	/// <summary>
	/// Dessiner toute les instances de la classe qui sont actives
	/// </summary>
	/// <param name="mainWin">Fenêtre de jeu principale</param>
	static void drawActiveInstances(sf::RenderWindow& mainWin);
	
	/// <summary>
	/// Détecter la collision avec d'autres.
	/// </summary>
	/// <param name="gameObject">L'objet pour détecter.</param>
	/// <returns>true si vrai, false sinon</returns>
	static bool detectCollisionWithOthers(GameObject * gameObject);
	
	/// <summary>
	/// Désactiver tous les objets de jeu actifs
	/// </summary>
	static void disableAllActiveGameObjects();

private:	
	/// <summary>
	/// État actif ou non
	/// </summary>
	bool active;

	/// <summary>
	/// Liste des instances de la classe
	/// </summary>
	static std::list<GameObject*> instances;
};

