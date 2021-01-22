#include "Game.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneCredits.h"
#include "SceneEnd.h"
#include "SceneInstructions.h"
#include "Constants.h"


/// <summary>
/// Constructeur de Game
/// </summary>
Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner
	mainWin.create(VideoMode(1920, 1080, 32), "M�R�K", sf::Style::Fullscreen);

	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

/// <summary>
/// Boucle principale des sc�nes de jeu
/// </summary>
/// <returns>Code de retour (0-> Succ�s, 1->Erreur)</returns>
int Game::run()
{
	//deux enums et un pointeur de scene pour faire la manipulation de sc�ne
	SceneType selecteurDeScene = TITLE;
	SceneType sceneEnRetour = SceneType::GAME;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle sc�ne

	while (true)
	{
		//Seule condition de EXIT de toute l'app
		if (selecteurDeScene == EXIT)
		{
			return EXIT_SUCCESS;
		}
		else
		{
			// Chargement de la sc�ne s�lectionn�e
			switch (selecteurDeScene)
			{
			case TITLE:
				sceneActive = new SceneTitle();
				break;
			case GAME:
				sceneActive = new SceneGame();
				break;
			case CREDITS:
				sceneActive = new SceneCredits();
				break;
			case INSTRUCTIONS:
				sceneActive = new SceneInstructions();
				break;
			case END:
				sceneActive = new SceneEnd();
				break;

			}


			// Lancement de la sc�ne si initialisable
			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
			}
			else
			{
				// Cleap-up � faire pour s'assurer  de ne pas avoir de leak
				selecteurDeScene = sceneEnRetour;
				delete sceneActive;
				sceneActive = nullptr;
				return EXIT_FAILURE;
			}
		}

		// Clean-up
		selecteurDeScene = sceneEnRetour;
		delete sceneActive;
		sceneActive = nullptr;
	}
}