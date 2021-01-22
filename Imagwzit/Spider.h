#pragma once
#include "Enemy.h"
#include "Constants.h"
#include "Projectile.h"
class SceneGame;

/// <summary>
/// Repr�sente le concept logique et graphique d'un spider dans l'espace de jeu
/// </summary>
/// <seealso cref="Character" />
class Spider : public Enemy
{
public:	
	/// <summary>
	/// Constructeur d'un spider
	/// </summary>
	Spider();

	/// <summary>
	/// Initialise les composants utiles � la classe
	/// </summary>
	/// <returns>Vrai lorsque l'initialisation a fonctionn�, faux sinon</returns>
	static bool init();	

	/// <summary>
	/// Met � jour le spider
	/// </summary>
	/// <param name="timeSpend">Le temps �coul� � la derni�re frame</param>
	void update(const float& timeSpend, SceneGame & scene) override;

	/// <summary>
	/// Animer l'ennemi
	/// </summary>
	/// <param name="layer">Le niveau d'animation.</param>
	/// <param name="animation">Le num�ro d'animation.</param>
	void animate(int layer, int animation);	

private:
	/// <summary>
	/// Vitesse du spider
	/// </summary>
	const static int MOVE_SPEED = 4;

	/// <summary>
	/// Diff�rence de distance pour d�terminer si la cible est atteinte
	/// </summary>
	const static int POSITION_THRESHOLD = 2;
	
	/// <summary>
	/// Le nombre maximal d'animations par niveau d'animation
	/// </summary>
	static const int MAX_ANIMATIONS_PER_LAYER = 10;
	
	/// <summary>
	/// Le nombre maximal de niveaux d'animation
	/// </summary>
	static const int MAX_ANIMATION_LAYERS = 5;
	
	/// <summary>
	/// Rectangles d'animation de l'ennemi
	/// </summary>
	static sf::IntRect intRects[MAX_ANIMATIONS_PER_LAYER * MAX_ANIMATION_LAYERS];

	/// <summary>
	/// Textures de l'araign�e
	/// </summary>
	static sf::Texture spiderT;
	
	/// <summary>
	/// Le num�ro d'animation
	/// </summary>
	int animation = 0;
	
	/// <summary>
	/// Le nombre de frames depuis le d�but
	/// </summary>
	int frames = 0;
	
	/// <summary>
	/// Le nombre de frames avant de changer d'animation
	/// </summary>
	const int FRAMES_BEFORE_ANIMATION_CHANGE = FRAMES_PER_SECOND / 3;
	
	/// <summary>
	/// Le niveau d'animation
	/// </summary>
	int animationLayer = 0;
	
	/// <summary>
	/// Le temps depuis le dernier tir
	/// </summary>
	float timeSinceLastShoot = 0;
};

