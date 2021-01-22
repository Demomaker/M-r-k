#include "SceneEnd.h"
#include "Constants.h"
#include "Player.h"
#include <fstream>
#include <iostream>

/// <summary>
/// Initialise la scène
/// </summary>
/// <param name="window">Fenêtre de jeu</param>
/// <return>Succès ou non de l'initialisation</return>
bool SceneEnd::init(RenderWindow * const window)
{
	if (!SceneMenu::init(window) || !titleScreenImageT.loadFromFile("Sprites\\Field.jpg"))
	{
		return false;
	}

	previousScene = EXIT;

	titleScreenImage.setTexture(titleScreenImageT);
	putAllScoresInScoreArrayFromFile("scores.txt");
	writeScoreInFile("scores.txt", currentPlayerScore);
	gameOverLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 125), true, 0, "GAME OVER !" + std::to_string(currentPlayerScore), 50, Color::White);
	scoreLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 75), true, 0, "SCORE : " + std::to_string(currentPlayerScore), 50, Color::White);
	lastScoreLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25), true, 0, "PARTIE PRÉCÉDENTE : " + std::to_string(getLastScore()), 50, Color::White);
	restartButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 25), true, 300, "RESTART", 7);
	menuButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 75), true, 300, "MENU", 4);
	exitButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 125), true, 300, "QUIT", 4);

	return true;
}

/// <summary>
/// Gère la mise à jour de la scène
/// </summary>
void SceneEnd::update()
{
}

void SceneEnd::writeScoreInFile(std::string file, int score)
{
	//Ouvrir le fichier et ajouter les chaines de caractères de score dans le fichier. Fermer le fichier.
	std::fstream myfile;
	myfile.open(file);
	std::string str{ std::istreambuf_iterator<char>{myfile},
					  std::istreambuf_iterator<char>{} };
	myfile.close();
	myfile.open(file, std::ofstream::out | std::ofstream::trunc);
	myfile.clear();
	myfile.seekg(0);
	myfile << str;
	myfile << score << "\n";
	myfile.close();
}
void SceneEnd::putAllScoresInScoreArrayFromFile(std::string file)
{
	//Ouvrir le fichier de scores, obtenir le contenu, passer à travers tout pour obtenir les scores
	//Et assigner les scores dans le pointeur de scores
	//Augmenter la capacité du tableau du pointeur si besoin est.
	std::ifstream myfile;
	myfile.open(file, std::ios::binary);
	numScores = 0;
	if (myfile.is_open())
	{

		myfile.seekg(0, std::ios::end);
		std::streampos size = myfile.tellg();
		myfile.seekg(0, std::ios::beg);
		std::ifstream file(file);
		std::string str{ std::istreambuf_iterator<char>{file},
						  std::istreambuf_iterator<char>{} };
		int stringLength = str.length();
		std::string * strs = new std::string[stringLength];
		int iteration = 0;
		size_t pos = 0;
		int length = 0;
		while ((pos = str.find('\n')) != std::string::npos) {
			length++;
			strs[iteration] = str.substr(0, pos);
			str.erase(0, pos + 1);
			numScores++;
			iteration++;
		}
		delete[] scores;
		scores = new int[length + 1];
		for (int i = 0; i <= length; i++) {
			std::string score;
			int iteration = 0;
			if (strs[i].find(' ') == std::string::npos) {
				score = strs[i];
			}
			
			if (score != "" && score != "\n")
				scores[i] = stoi(score);
		}
		delete[] strs;
		myfile.close();
	}

}
int SceneEnd::getLastScore() 
{
	//Retourner le dernier score
	return scores[numScores - 1];
}

/// <summary>
/// Gère l'affichage de la scène
/// </summary>
void SceneEnd::draw()
{
	mainWin->clear();
	mainWin->draw(titleScreenImage);
	lastScoreLabel.draw(mainWin);
	scoreLabel.draw(mainWin);
	restartButton.draw(mainWin);
	menuButton.draw(mainWin);
	exitButton.draw(mainWin);
	mainWin->display();
}

/// <summary>
/// Gère les événements liés à l'interface graphique
/// </summary>
/// <param name="eventType">Type d'événement</param>
void SceneEnd::onUIEvent(const UIEventType & eventType)
{
	switch (eventType)
	{
	case LEFT_MOUSE_PRESSED:
		//Valider si on a appuyé ou non sur un bouton
		restartButton.pressed(Mouse::getPosition(*mainWin));
		menuButton.pressed(Mouse::getPosition(*mainWin));
		exitButton.pressed(Mouse::getPosition(*mainWin));
		break;
	case LEFT_MOUSE_RELEASED:
		if (restartButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(GAME);
			delete[] scores;
		}
		else if (menuButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(TITLE);
			delete[] scores;
		}
		else if (exitButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(EXIT);
			delete[] scores;
		}
		break;
	case BACK:
		transitionToScene(previousScene);
		break;
	}
}
