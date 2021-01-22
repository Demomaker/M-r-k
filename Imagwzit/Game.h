#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Nouvelle version de la classe game.  � pr�sent elle sera surtout charg�e de charger les diff�rentes sc�nes
/// </summary>
class Game
{
public:
	/// <summary>
	/// Constructeur de Game
	/// </summary>
	Game();

	/// <summary>
	/// Boucle principale des sc�nes de jeu
	/// </summary>
	/// <returns>Code de retour (0-> Succ�s, 1->Erreur)</returns>
	int run();

private:
	/// <summary>
	/// Fen�tre de jeu principale
	/// </summary>
	RenderWindow mainWin;

	/// <summary>
	/// Gestionnaire d'�v�nements
	/// </summary>
	Event event;
};