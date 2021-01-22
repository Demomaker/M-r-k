#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Nouvelle version de la classe game.  À présent elle sera surtout chargée de charger les différentes scènes
/// </summary>
class Game
{
public:
	/// <summary>
	/// Constructeur de Game
	/// </summary>
	Game();

	/// <summary>
	/// Boucle principale des scènes de jeu
	/// </summary>
	/// <returns>Code de retour (0-> Succès, 1->Erreur)</returns>
	int run();

private:
	/// <summary>
	/// Fenêtre de jeu principale
	/// </summary>
	RenderWindow mainWin;

	/// <summary>
	/// Gestionnaire d'événements
	/// </summary>
	Event event;
};