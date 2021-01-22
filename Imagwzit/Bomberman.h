#pragma once
#include "Enums.h"
#include "Enemy.h"
#include "Constants.h"
#include "Projectile.h"
class SceneGame;

/// <summary>
/// Repr�sente le concept logique et graphique d'un bomberman dans l'espace de jeu
/// </summary>
/// <seealso cref="Character" />
class Bomberman : public Enemy
{
public:
	/// <summary>
	/// Constructeur d'un bomberman
	/// </summary>
	Bomberman();

	/// <summary>
	/// Initialise les composants utiles � la classe
	/// </summary>
	/// <returns>Vrai lorsque l'initialisation a fonctionn�, faux sinon</returns>
	static bool init();

	/// <summary>
	/// Met � jour le bomberman
	/// </summary>
	/// <param name="playerPosition">La position du joueur</param>
	/// <param name="playerIsActive">Le joueur est en vie ou non</param>
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
	/// Vitesse du bomberman
	/// </summary>
	const static int MOVE_SPEED = 1;

	/// <summary>
	/// Texture de l'ennemi
	/// </summary>
	static sf::Texture bombermanT;

	/// <summary>
	/// Diff�rence de distance pour d�terminer si la cible est atteinte
	/// </summary>
	const static int POSITION_THRESHOLD = 2;
	
	/// <summary>
	/// Le nombre maximal d'animations par niveau d'animation
	/// </summary>
	static const int MAX_ANIMATIONS_PER_LAYER = 4;	

	/// <summary>
	/// Le nombre maximal de niveaux d'animation
	/// </summary>
	static const int MAX_ANIMATION_LAYERS = 4;
	
	/// <summary>
	/// Rectangles d'animation de l'ennemi
	/// </summary>
	static sf::IntRect intRects[MAX_ANIMATIONS_PER_LAYER * MAX_ANIMATION_LAYERS];
	
	/// <summary>
	/// Le num�ro de l'animation en cours
	/// </summary>
	int animation = 0;	

	/// <summary>
	/// Le nombre de frames depuis le d�but
	/// </summary>
	int frames = 0;	

	/// <summary>
	/// Le nombre de frames avant que l'animation change
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

