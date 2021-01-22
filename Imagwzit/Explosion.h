#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Représente le concept logique et graphique d'une explosion dans l'espace de jeu
/// </summary>
/// <seealso cref="sf::Text" />
class Explosion : public sf::Sprite
{
public:
	/// <summary>
	/// Constructeur d'une explosion
	/// </summary>
	Explosion();

	/// <summary>
	/// Met à jour l'état de l'explosion (Actif ou inactif)
	/// </summary>
	/// <param name="active">État actif ou non de l'explosion</param>
	void setActive(const bool& active);

	/// <summary>
	/// Détermine si l'explosion est active
	/// </summary>
	/// <returns>État actif ou non de l'explosion</returns>
	bool isActive() const;

	/// <summary>
	/// Initialise toutes les instances
	/// </summary>
	static bool init();

	/// <summary>
	/// Met à jour toutes les instances de la classe qui sont actives
	/// </summary>
	/// <param name="timeSpend">Le temps écoulé</param>
	static void updateActiveInstances(const float& timeSpend);

	/// <summary>
	/// Dessine toutes les instances de la classe qui sont actives
	/// </summary>
	/// <param name="mainWin">Fenêtre de jeu principale</param>
	static void drawActiveInstances(sf::RenderWindow& mainWin);

	/// <summary>
	/// Désactive toutes les instances de la classe
	/// </summary>
	static void disableAllActiveInstances();

	/// <summary>
	/// Active une explosion
	/// </summary>
	/// <param name="position">La position 2D</param>
	static void spawnAnExplosion(const sf::Vector2f& position);

	/// <summary>
	/// Nombre d'instances de la classe
	/// </summary>
	const static int MAX_NB_EXPLOSIONS = 20;

private:
	/// <summary>
	/// État actif ou non
	/// </summary>
	bool active = false;

	/// <summary>
	/// Tableau des instances de la classe
	/// </summary>
	static Explosion instances[MAX_NB_EXPLOSIONS];

	/// <summary>
	/// Nombre de colonnes dans la sprite sheet
	/// </summary>
	const static int NB_COLS_IN_SRITESHEET = 10;

	/// <summary>
	/// Nombre de lignes dans la sprite sheet
	/// </summary>
	const static int NB_LINES_IN_SRITESHEET = 7;

	/// <summary>
	/// Nombre d'animation dans la sprite sheet
	/// </summary>
	const static int NB_ANIMS = 64;

	/// <summary>
	/// Largeur d'un frame d'animation
	/// </summary>
	const static int RECT_SIZE = 100;

	/// <summary>
	/// Chronomètre pour gérer le temps d'activation
	/// </summary>
	float chronometer;

	/// <summary>
	/// Compteur pour l'animation de l'explosion
	/// </summary>
	int animator;

	/// <summary>
	/// Rect qui contient la position des frames de l'animation
	/// </summary>
	static sf::IntRect anims[NB_ANIMS];

	/// <summary>
	/// Texture qui contient l'animation de l'explosion
	/// </summary>
	static sf::Texture explosionT;
};

