#pragma once
#include "Enums.h"
#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Repr�sente le concept d'un sc�ne
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Destructeur de Scene
	/// </summary>
	virtual ~Scene() {}  //Pour que le destructeur de l'objet en m�moire soit apell�

	/// <summary>
	/// Boucle principale de la sc�ne
	/// </summary>
	/// <return>Prochaine sc�ne � charger</return>
	virtual SceneType run() = 0;

	/// <summary>
	/// Initialise la sc�ne
	/// </summary>
	/// <param name="window">Fen�tre de jeu</param>
	/// <return>Succ�s ou non de l'initialisation</return>
	virtual bool init(RenderWindow * const window) = 0;

	/// <summary>
	/// G�re les entr�es de l'utilisateur
	/// </summary>
	virtual void getInputs() = 0;

	/// <summary>
	/// G�re la mise � jour de la sc�ne
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// G�re l'affichage de la sc�ne
	/// </summary>
	virtual void draw() = 0;

	/// <summary>
	/// Effectue une transition vers une autre sc�ne
	/// </summary>
	/// <param name="to">Sc�ne vers laquelle on veut faire une transition</param>
	void transitionToScene(SceneType to);


protected:

	/// <summary>
	/// Pointeur vers la fen�tre principale du jeu
	/// </summary>
	RenderWindow *mainWin;

	/// <summary>
	/// Gestionnaire des �v�nements
	/// </summary>
	Event event;

	/// <summary>
	/// � la fin de chaque sc�ne, on indique � Game quelle sra la nouvelle sc�ne qu'elle doit charger
	/// </summary>
	SceneType nextScene;

	/// <summary>
	/// Police d'�criture principale
	/// </summary>
	Font font;

	/// <summary>
	/// �tat de l'ex�cution de la sc�ne
	/// </summary>
	bool isRunning;
	
	/// <summary>
	/// Le score du joueur
	/// </summary>
	static int currentPlayerScore;
};