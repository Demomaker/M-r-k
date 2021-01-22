#pragma once
#include "Enemy.h"
#include "Constants.h"
class SceneGame;

/// <summary>
/// Représente le concept logique et graphique d'un ghost dans l'espace de jeu
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
	/// Initialise les composants utiles à la classe
	/// </summary>
	/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
	static bool init();	

	/// <summary>
	/// Met à jour le ghost
	/// </summary>
	/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
	void update(const float& timeSpend, SceneGame & scene) override;

	/// <summary>
	/// Animer l'ennemi
	/// </summary>
	/// <param name="layer">Le niveau d'animation.</param>
	/// <param name="animation">Le numéro d'animation.</param>
	void animate(int layer, int animation);
	
	/// <summary>
	/// Téléporter le fantôme à une position aléatoire
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
	/// Le numéro de l'animation en cours
	/// </summary>
	int animation = 0;	

	/// <summary>
	/// Le nombre de frames depuis le début
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

