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
/// Repr�sente le d�roulement logique et graphique du jeu
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
	///  D�termine si le cheat a �t� activ�
	/// </summary>
	/// <return>Vrai si cheat activ�</return>
	bool checkCheat();

	/// <summary>
	/// Boucle principale de la sc�ne
	/// </summary>
	/// <return>Prochaine sc�ne � charger</return>
	SceneType run();

	/// <summary>
	/// Initialise la sc�ne
	/// </summary>
	/// <param name="window">Fen�tre de jeu</param>
	/// <return>Succ�s ou non de l'initialisation</return>
	bool init(RenderWindow * const window);

	/// <summary>
	/// G�re les entr�es de l'utilisateur
	/// </summary>
	void getInputs();

	/// <summary>
	/// G�re la mise � jour de la sc�ne
	/// </summary>
	void update();
	
	/// <summary>
	/// Mettre � jour l'Interface utilisateur.
	/// </summary>
	void updateUI();
	
	/// <summary>
	/// Mettre fin au jeu.
	/// </summary>
	void endGame();

	/// <summary>
	/// G�re l'affichage de la sc�ne
	/// </summary>
	void draw();

	/// <summary>
	/// G�n�re un corridor horizontal
	/// </summary>
	/// <param name="x1">Position en X de l'extr�mit� gauche</param>
	/// <param name="x2">Position en Y de l'extr�mit� droite</param>
	/// <param name="y">Position en Y</param>
	void hCorridor(int x1, int x2, int y);

	/// <summary>
	/// G�n�re un corridor vertical
	/// </summary>
	/// <param name="x1">Position en Y du haut</param>
	/// <param name="x2">Position en Y du bas</param>
	/// <param name="y">Position en X</param>
	void vCorridor(int y1, int y2, int x);

	/// <summary>
	/// G�n�re les pi�ces du niveau
	/// </summary>
	void placeRooms();
	
	/// <summary>
	/// D�terminer si l'endroit est marchable
	/// </summary>
	/// <param name="movement">Le mouvement � effectuer (Modifi� dans la m�thode si invalide)</param>
	/// <param name="position">La position initial de l'objet.</param>
	/// <returns>0 (faux) si ce n'est pas marchable, 1 (true) si c'est marchable, 2 (true) si c'est un mur destructible, dans ce cas, faire les traitements n�cessaires</returns>
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
	/// Tableau dynamique qui contient les rectangles des diff�rentes tuiles
	/// </summary>
	IntRect* intRectsTiles;
	
	/// <summary>
	/// Police d'�criture principale
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
	/// L'arri�re-plan des slots
	/// </summary>
	RectangleShape slotsBackground;
	
	/// <summary>
	/// L'arri�re-plan des ammos
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
	/// Emp�che l'�cran de d�passer les limites logiques du monde
	/// </summary>
	void crossingViewLimitsAdjustment();

	/// <summary>
	/// Composant pour la gestion du temps et des rafraichissement d'�cran
	/// </summary>
	Clock frameClock;
	
	/// <summary>
	/// Temps �coul� lors de la derni�re boucle de jeu
	/// </summary>
	float timeSpend;
	
	/// <summary>
	/// �tat de pause
	/// </summary>
	bool pause;
	
	/// <summary>
	/// �tat de la touche pause appuy�e
	/// </summary>
	bool pauseKeyPressed;

	/// <summary>
	/// �tat de la touche P appuy�e
	/// </summary>
	bool PKeyPressed;

	/// <summary>
	/// �tat de la touche O appuy�e
	/// </summary>
	bool OKeyPressed;

	/// <summary>
	/// �tat de la touche T appuy�e
	/// </summary>
	bool TKeyPressed;

	/// <summary>
	/// �tat de la touche E appuy�e
	/// </summary>
	bool EKeyPressed;

	/// <summary>
	/// Vue pour la cam�ra principale
	/// </summary>
	View view;

	/// <summary>
	/// Vue pour l'affichage de l'interface
	/// </summary>
	View HUD;
};