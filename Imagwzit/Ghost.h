#pragma once
#include "Enemy.h"
#include "Constants.h"
class SceneGame;

/// <summary>
/// Repr�sente le concept logique et graphique d'un ghost dans l'espace de jeu
/// </summary>
/// <seealso cref="Character" />
class Ghost : public Enemy
{
public:	
	/// <summary>
	/// Constructeur d'un ghost
	/// </summary>
	Ghost();

	/// <summary>
	/// Initialise les composants utiles � la classe
	/// </summary>
	/// <returns>Vrai lorsque l'initialisation a fonctionn�, faux sinon</returns>
	static bool init();	

	/// <summary>
	/// Met � jour le ghost
	/// </summary>
	/// <param name="timeSpend">Le temps �coul� � la derni�re frame</param>
	void update(const float& timeSpend, SceneGame & scene) override;

	/// <summary>
	/// Animer l'ennemi
	/// </summary>
	/// <param name="layer">Le niveau d'animation.</param>
	/// <param name="animation">Le num�ro d'animation.</param>
	void animate(int layer, int animation);
	
	/// <summary>
	/// T�l�porter le fant�me � une position al�atoire
	/// </summary>
	void randomTeleport();

private:

	/// <summary>
	/// Vitesse du ghost
	/// </summary>
	const static int MOVE_SPEED = 4;

	/// <summary>
	/// Rectangles d'animation de l'ennemi
	/// </summary>
	static sf::IntRect intRects[4];

	/// <summary>
	/// Texture de l'ennemi
	/// </summary>
	static sf::Texture ghostT;
	
	/// <summary>
	/// Le nombre maximal d'animations par niveau d'animation
	/// </summary>
	static const int MAX_ANIMATIONS_PER_LAYER = 2;
	
	/// <summary>
	/// Le num�ro de l'animation en cours
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
};

