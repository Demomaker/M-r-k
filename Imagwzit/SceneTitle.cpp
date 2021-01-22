#include "SceneTitle.h"
#include "Constants.h"

/// <summary>
/// Initialise la sc�ne
/// </summary>
/// <param name="window">Fen�tre de jeu</param>
/// <return>Succ�s ou non de l'initialisation</return>
bool SceneTitle::init(RenderWindow * const window)
{
	if (!SceneMenu::init(window) || !titleScreenImageT.loadFromFile("Sprites\\Field.jpg"))
	{
		return false;
	}

	previousScene = EXIT;
	merekLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 125), true, 0, "M�R�K", 50, Color::White);
	titleScreenImage.setTexture(titleScreenImageT);
	playButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 75), true, 300, "PLAY", 4);
	instructionsButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25), true, 300, "INSTRUCTIONS", 12);
	creditsButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 25), true, 300, "CREDITS", 7);
	exitButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 75), true, 300, "QUIT", 4);

	return true;
}

/// <summary>
/// G�re la mise � jour de la sc�ne
/// </summary>
void SceneTitle::update()
{
}

/// <summary>
/// G�re l'affichage de la sc�ne
/// </summary>
void SceneTitle::draw()
{
	mainWin->clear();
	mainWin->draw(titleScreenImage);
	playButton.draw(mainWin);
	instructionsButton.draw(mainWin);
	creditsButton.draw(mainWin);
	exitButton.draw(mainWin);
	merekLabel.draw(mainWin);
	mainWin->display();
}

/// <summary>
/// G�re les �v�nements li�s � l'interface graphique
/// </summary>
/// <param name="eventType">Type d'�v�nement</param>
void SceneTitle::onUIEvent(const UIEventType & eventType)
{
	switch (eventType)
	{
	case LEFT_MOUSE_PRESSED:
		//Valider si on a appuy� ou non sur un bouton
		playButton.pressed(Mouse::getPosition(*mainWin));
		instructionsButton.pressed(Mouse::getPosition(*mainWin));
		creditsButton.pressed(Mouse::getPosition(*mainWin));
		exitButton.pressed(Mouse::getPosition(*mainWin));
		break;
	case LEFT_MOUSE_RELEASED:
		if (playButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(GAME);
		}
		else if (instructionsButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(INSTRUCTIONS);
		}
		else if (creditsButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(CREDITS);
		}
		else if (exitButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(EXIT);
		}
		break;
	case BACK:
		transitionToScene(previousScene);
		break;
	}
}
