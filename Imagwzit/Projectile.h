#pragma once
#include "GameObject.h"
#include "Enums.h"
#include "Player.h"
#include "Enemy.h"
class SceneGame;
/// <summary>
/// Représente le concept logique et graphique d'un projectile dans l'espace de jeu
/// </summary>
/// <seealso cref="GameObject" />
class Projectile : public GameObject
{
public:	
	/// <summary>
	/// Constructeur d'un projectile
	/// </summary>
	Projectile();

	/// <summary>
	/// Fait apparaître un projectile dans l'espace de jeu
	/// </summary>
	/// <param name="_angle">Angle du projectile</param>
	/// <param name="_player">Le joueur</param>
	void spawn(const float& _angle, const Character& character, bool shotByPlayer);

	/// <summary>
	/// Met à jour le projectile
	/// </summary>
	/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
	/// <param name="sceneGame">Référence à la partie en cours</param>
	void update(const float& timeSpend, SceneGame & sceneGame);
	
	/// <summary>
	/// Détermine si le projectile a été tiré par le joueur
	/// </summary>
	/// <returns>Vrai si tiré par le joueur, faux sinon</returns>
	bool isShotByPlayer() const;

	/// <summary>
	/// Obtient le type de projectile
	/// </summary>
	/// <returns>Type de projectile</returns>
	ProjectileType getType() const;

	/// <summary>
	/// Mettre à jour le type de projectile
	/// </summary>
	/// <param name="type">Type de projectile</param>
	void setType(const ProjectileType& type);

	/// <summary>
	/// Initialise les composants de la classe
	/// </summary>
	/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
	static bool init();

	/// <summary>
	/// Met à jour toutes les instances de la classe qui sont actives
	/// </summary>
	/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
	/// <param name="sceneGame">Référence à la partie en cours</param>
	static void updateActiveInstances(const float& timeSpend, SceneGame & sceneGame);

	/// <summary>
	/// Active un projectile
	/// </summary>
	/// <param name="player">Le joueur</param>
	/// <param name="angle">L'orientation du projectile</param>
	/// <param name="shotByPlayer">Vrai si tiré par le joueur</param>
	static void spawnAProjectile(const float& angle, const Character & character, bool shotByPlayer);
	
	/// <summary>
	/// Détermine si le bonus est en collision avec l'object de jeu spécifié
	/// </summary>
	/// <param name="other">GameObject avec lequel on teste la collision</param>
	/// <returns>Vrai s'il y a une collision, faux sinon</returns>
	static Projectile * checkCollisionWith(const GameObject& other);
private:
	/// <summary>
	/// Nombre de projectiles maximum en jeu pour ce qui n'est pas un ennemi
	/// </summary>
	const static int MAX_NB_PROJECTILES = 30;
	
	/// <summary>
	/// Nombre de projectiles maximum pour les ennemis
	/// </summary>
	const static int MAX_NB_PROJECTILES_ENNEMIS = 30;

	/// <summary>
	/// Durée de vie des munitions de type "Flame"
	/// </summary>
	const static float FLAME_LIFE_TIME;
	
	/// <summary>
	/// Durée de vie des munitions de type "Laser"
	/// </summary>
	const static float LASER_LIFE_TIME;

	/// <summary>
	/// Vitesse des projectiles de base
	/// </summary>
	const static int BASE_SPEED = 30;	

	/// <summary>
	/// Vitesse des missiles
	/// </summary>
	const static int MISSILE_SPEED = 20;
	
	/// <summary>
	/// Vitesse des lasers
	/// </summary>
	const static int LASER_SPEED = 0;

	/// <summary>
	/// Vitesse des projectiles de feu
	/// </summary>
	const static int FLAME_SPEED = 10;	

	/// <summary>
	/// Vitesse des projectiles à dispersion
	/// </summary>
	const static int SCATTER_SPEED = 25;

	/// <summary>
	/// Vitesse des toiles d'araignées
	/// </summary>
	const static int SPIDERWEB_SPEED = 5;

	/// <summary>
	/// Vitesse des bombes
	/// </summary>
	const static int BOMB_SPEED = 10;

	/// <summary>
	/// Tableau qui contient les textures des projectiles disponibles en jeu
	/// </summary>
	static sf::Texture projectileT[6];

	/// <summary>
	/// Tableau qui contient les instances de la classe
	/// </summary>
	static Projectile instances[MAX_NB_PROJECTILES + MAX_NB_PROJECTILES_ENNEMIS];

	/// <summary>
	/// Orientation du projectile
	/// </summary>
	float angle;

	/// <summary>
	/// Vitesse du projectile
	/// </summary>
	int speed;	

	/// <summary>
	/// Composant permettant la gestion du temps
	/// </summary>
	float chronometer;	

	/// <summary>
	/// Type du projectile
	/// </summary>
	ProjectileType type;
	
	/// <summary>
	/// Détermine si le projectile a été tiré par le joueur ou non
	/// </summary>
	bool shotByPlayer;

};

