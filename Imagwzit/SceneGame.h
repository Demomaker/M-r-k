#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bonus.h"
#include "Player.h"
#include "Scene.h"
#include "Map.h"
#include "Constants.h"
#include "Recorder.h"
#include "Spawner.h"
#include "DestructableWall.h"

using namespace sf;
class Enemy;
/// <summary>
/// Représente le déroulement logique et graphique du jeu
/// </summary>
class SceneGame : public Scene
{
public:	
	/// <summary>
	/// Constructeur de SceneGame
	/// </summary>
	SceneGame();

	/// <summary>
	/// Destructeur de SceneGame
	/// </summary>
	~SceneGame();

	/// <summary>
	///  Détermine si le cheat a été activé
	/// </summary>
	/// <return>Vrai si cheat activé</return>
	bool checkCheat();

	/// <summary>
	/// Boucle principale de la scène
	/// </summary>
	/// <return>Prochaine scène à charger</return>
	SceneType run();

	/// <summary>
	/// Initialise la scène
	/// </summary>
	/// <param name="window">Fenêtre de jeu</param>
	/// <return>Succès ou non de l'initialisation</return>
	bool init(RenderWindow * const window);

	/// <summary>
	/// Gère les entrées de l'utilisateur
	/// </summary>
	void getInputs();

	/// <summary>
	/// Gère la mise à jour de la scène
	/// </summary>
	void update();
	
	/// <summary>
	/// Mettre à jour l'Interface utilisateur.
	/// </summary>
	void updateUI();
	
	/// <summary>
	/// Mettre fin au jeu.
	/// </summary>
	void endGame();

	/// <summary>
	/// Gère l'affichage de la scène
	/// </summary>
	void draw();

	/// <summary>
	/// Génère un corridor horizontal
	/// </summary>
	/// <param name="x1">Position en X de l'extrémité gauche</param>
	/// <param name="x2">Position en Y de l'extrémité droite</param>
	/// <param name="y">Position en Y</param>
	void hCorridor(int x1, int x2, int y);

	/// <summary>
	/// Génère un corridor vertical
	/// </summary>
	/// <param name="x1">Position en Y du haut</param>
	/// <param name="x2">Position en Y du bas</param>
	/// <param name="y">Position en X</param>
	void vCorridor(int y1, int y2, int x);

	/// <summary>
	/// Génère les pièces du niveau
	/// </summary>
	void placeRooms();
	
	/// <summary>
	/// Déterminer si l'endroit est marchable
	/// </summary>
	/// <param name="movement">Le mouvement à effectuer (Modifié dans la méthode si invalide)</param>
	/// <param name="position">La position initial de l'objet.</param>
	/// <returns>0 (faux) si ce n'est pas marchable, 1 (true) si c'est marchable, 2 (true) si c'est un mur destructible, dans ce cas, faire les traitements nécessaires</returns>
	int isWalkableArea(sf::Vector2f & movement, const sf::Vector2f & position) const;
	
	/// <summary>
	/// Charger le prochain niveau
	/// </summary>
	void loadNextLevel();

private:
	/// <summary>
	/// Centre logique du monde en x
	/// </summary>
	const int WORLD_CENTER_X = WORLD_WIDTH / 2;

	/// <summary>
	/// Centre logique du monde en y
	/// </summary>
	const int WORLD_CENTER_Y = WORLD_HEIGHT / 2;

	/// <summary>
	/// Limite d'affichage minimale en x
	/// </summary>
	const int VIEW_LIMIT_MIN_X = SCREEN_WIDTH / 2;

	/// <summary>
	/// Limite d'affichage minimale en y
	/// </summary>
	const int VIEW_LIMIT_MIN_Y = SCREEN_HEIGHT / 2;

	/// <summary>
	/// Limite d'affichage maximale en x
	/// </summary>
	const int VIEW_LIMIT_MAX_X = WORLD_WIDTH - VIEW_LIMIT_MIN_X;

	/// <summary>
	/// Limite d'affichage maximale en y
	/// </summary>
	const int VIEW_LIMIT_MAX_Y = WORLD_HEIGHT - VIEW_LIMIT_MIN_Y;
	
	/// <summary>
	/// Les textures du tileset
	/// </summary>
	Texture tilesetT;
	
	/// <summary>
	/// Le tile
	/// </summary>
	Sprite tile;

	/// <summary>
	/// Background coloring
	/// </summary>
	RectangleShape background;

	/// <summary>
	/// Tableau des instances de spawner
	/// </summary>
	std::list<Spawner*> spawnerInstances;


	/// <summary>
	/// Tableau des instances de murs destructibles
	/// </summary>
	std::list<DestructableWall*> destructableWallInstances;


	/// <summary>
	/// Tableau dynamique qui contient les rectangles des différentes tuiles
	/// </summary>
	IntRect* intRectsTiles;
	
	/// <summary>
	/// Police d'écriture principale
	/// </summary>
	Font mainFont;	

	/// <summary>
	/// Musique en jeu
	/// </summary>
	Music music;

	/// <summary>
	/// Composant permettant l'affichage du type de munition
	/// </summary>
	Sprite bonusIcon;
	
	/// <summary>
	/// Le sprite de sortie
	/// </summary>
	Sprite exitSprite;

	#pragma region HUD
	
	/// <summary>
	/// Dessiner le hud.
	/// </summary>
	void drawHUD();
	
	/// <summary>
	/// L'arrière-plan des slots
	/// </summary>
	RectangleShape slotsBackground;
	
	/// <summary>
	/// L'arrière-plan des ammos
	/// </summary>
	RectangleShape ammoBackground;
	
	/// <summary>
	/// L'enregistreur de manipulations
	/// </summary>
	Recorder recorder;
	
	/// <summary>
	/// Le timer pour l'enregistrement de manipulations
	/// </summary>
	Clock timer;
	
	/// <summary>
	/// La texture des coeurs
	/// </summary>
	Texture heartT;
	
	/// <summary>
	/// Le sprite des coeurs
	/// </summary>
	Sprite heart;
	
	/// <summary>
	/// Les textures des logos
	/// </summary>
	Texture logosT[6];
	
	/// <summary>
	/// Le sprite des logos
	/// </summary>
	Sprite logo;

	/// <summary>
	/// Composant permettant l'affichage du score
	/// </summary>
	Text scoreText;

	/// <summary>
	/// Composant permettant l'affichage des munitions
	/// </summary>
	Text ammoText;

	#pragma endregion
	
	/// <summary>
	/// Le niveau
	/// </summary>
	int level = 1;
	
	/// <summary>
	/// Empêche l'écran de dépasser les limites logiques du monde
	/// </summary>
	void crossingViewLimitsAdjustment();

	/// <summary>
	/// Composant pour la gestion du temps et des rafraichissement d'écran
	/// </summary>
	Clock frameClock;
	
	/// <summary>
	/// Temps écoulé lors de la dernière boucle de jeu
	/// </summary>
	float timeSpend;
	
	/// <summary>
	/// État de pause
	/// </summary>
	bool pause;
	
	/// <summary>
	/// État de la touche pause appuyée
	/// </summary>
	bool pauseKeyPressed;

	/// <summary>
	/// État de la touche P appuyée
	/// </summary>
	bool PKeyPressed;

	/// <summary>
	/// État de la touche O appuyée
	/// </summary>
	bool OKeyPressed;

	/// <summary>
	/// État de la touche T appuyée
	/// </summary>
	bool TKeyPressed;

	/// <summary>
	/// État de la touche E appuyée
	/// </summary>
	bool EKeyPressed;

	/// <summary>
	/// Vue pour la caméra principale
	/// </summary>
	View view;

	/// <summary>
	/// Vue pour l'affichage de l'interface
	/// </summary>
	View HUD;
};