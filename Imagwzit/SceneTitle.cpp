#include "SceneTitle.h"
#include "Constants.h"

/// <summary>
/// Initialise la scène
/// </summary>
/// <param name="window">Fenêtre de jeu</param>
/// <return>Succès ou non de l'initialisation</return>
bool SceneTitle::init(RenderWindow * const window)
{
	if (!SceneMenu::init(window) || !titleScreenImageT.loadFromFile("Sprites\\Field.jpg"))
	{
		return false;
	}

	previousScene = EXIT;
	merekLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 125), true, 0, "MÉRÉK", 50, Color::White);
	titleScreenImage.setTexture(titleScreenImageT);
	playButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 75), true, 300, "PLAY", 4);
	instructionsButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25), true, 300, "INSTRUCTIONS", 12);
	creditsButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 25), true, 300, "CREDITS", 7);
	exitButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 75), true, 300, "QUIT", 4);

	return true;
}

/// <summary>
/// Gère la mise à jour de la scène
/// </summary>
void SceneTitle::update()
{
}

/// <summary>
/// Gère l'affichage de la scène
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
/// Gère les événements liés à l'interface graphique
/// </summary>
/// <param name="eventType">Type d'événement</param>
void SceneTitle::onUIEvent(const UIEventType & eventType)
{
	switch (eventType)
	{
	case LEFT_MOUSE_PRESSED:
		//Valider si on a appuyé ou non sur un bouton
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
