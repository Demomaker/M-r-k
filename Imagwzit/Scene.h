#pragma once
#include "Enums.h"
#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Représente le concept d'un scène
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Destructeur de Scene
	/// </summary>
	virtual ~Scene() {}  //Pour que le destructeur de l'objet en mémoire soit apellé

	/// <summary>
	/// Boucle principale de la scène
	/// </summary>
	/// <return>Prochaine scène à charger</return>
	virtual SceneType run() = 0;

	/// <summary>
	/// Initialise la scène
	/// </summary>
	/// <param name="window">Fenêtre de jeu</param>
	/// <return>Succès ou non de l'initialisation</return>
	virtual bool init(RenderWindow * const window) = 0;

	/// <summary>
	/// Gère les entrées de l'utilisateur
	/// </summary>
	virtual void getInputs() = 0;

	/// <summary>
	/// Gère la mise à jour de la scène
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// Gère l'affichage de la scène
	/// </summary>
	virtual void draw() = 0;

	/// <summary>
	/// Effectue une transition vers une autre scène
	/// </summary>
	/// <param name="to">Scène vers laquelle on veut faire une transition</param>
	void transitionToScene(SceneType to);


protected:

	/// <summary>
	/// Pointeur vers la fenêtre principale du jeu
	/// </summary>
	RenderWindow *mainWin;

	/// <summary>
	/// Gestionnaire des événements
	/// </summary>
	Event event;

	/// <summary>
	/// À la fin de chaque scène, on indique à Game quelle sra la nouvelle scène qu'elle doit charger
	/// </summary>
	SceneType nextScene;

	/// <summary>
	/// Police d'écriture principale
	/// </summary>
	Font font;

	/// <summary>
	/// État de l'exécution de la scène
	/// </summary>
	bool isRunning;
	
	/// <summary>
	/// Le score du joueur
	/// </summary>
	static int currentPlayerScore;
};