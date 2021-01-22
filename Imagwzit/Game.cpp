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
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner
	mainWin.create(VideoMode(1920, 1080, 32), "MÉRÉK", sf::Style::Fullscreen);

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

/// <summary>
/// Boucle principale des scènes de jeu
/// </summary>
/// <returns>Code de retour (0-> Succès, 1->Erreur)</returns>
int Game::run()
{
	//deux enums et un pointeur de scene pour faire la manipulation de scène
	SceneType selecteurDeScene = TITLE;
	SceneType sceneEnRetour = SceneType::GAME;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle scène

	while (true)
	{
		//Seule condition de EXIT de toute l'app
		if (selecteurDeScene == EXIT)
		{
			return EXIT_SUCCESS;
		}
		else
		{
			// Chargement de la scène sélectionnée
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


			// Lancement de la scène si initialisable
			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
			}
			else
			{
				// Cleap-up à faire pour s'assurer  de ne pas avoir de leak
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