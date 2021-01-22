#include "SceneCredits.h"
#include "Constants.h"

/// <summary>
/// Initialise la scène
/// </summary>
/// <param name="window">Fenêtre de jeu</param>
/// <return>Succès ou non de l'initialisation</return>
bool SceneCredits::init(RenderWindow * const window)
{
	if (!SceneMenu::init(window) || !titleScreenImageT.loadFromFile("Sprites\\Field.jpg"))
	{
		return false;
	}

	previousScene = TITLE;

	titleScreenImage.setTexture(titleScreenImageT);
	titleLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 100), true, 0, "CRÉDITS", 50, Color::White);
	sourceLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 50), true, 0, "SOURCES", 50, Color::White);
	sourcesLabel[0].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + -25), true, 0, "Sprite Squelette : https://opengameart.org/content/zombie-and-skeleton-32x48", 200, Color::White);
	sourcesLabel[1].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 25), true, 0, "Sprite Araignée : https://opengameart.org/content/lpc-spider ", 200, Color::White);
	sourcesLabel[2].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 75), true, 0, "Sprite Zombies https://opengameart.org/content/freeart-topdown-zombies", 200, Color::White); //, Bullet, Flame, Missile, Scatter:
	sourcesLabel[3].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 125), true, 0, "Sprite Bomberman (Sans tête de bombe) : https://opengameart.org/content/player-1", 200, Color::White);
	sourcesLabel[4].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 175), true, 0, "Sprite Bombes : https://opengameart.org/content/bombs", 200, Color::White);
	sourcesLabel[5].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 225), true, 0, "Sprite Rocket Launcher : https://steemitimages.com/DQmeN5WBQy5ZrFJzMYizBC3LsVP9sgNMteP2hmKnanFBY7S/bomb.png", 200, Color::White);
	sourcesLabel[6].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 275), true, 0, "Sprite Fantômes, Toile d'araignée, Spawner, Musique de fond : Demomaker / Mike Bédard", 100, Color::White);
	sourcesLabel[7].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 325), true, 0, "Sprite Coeur : https://art.pixilart.com/df6746562c2e7a9.png", 100, Color::White);
	sourcesLabel[8].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 375), true, 0, "Sprite Joueur, Murs, Planchers : https://0x72.itch.io/dungeontileset-ii", 200, Color::White);
	sourcesLabel[9].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 425), true, 0, "Sprite explosion : https://untiedgames.itch.io/five-free-pixel-explosions", 200, Color::White);
	sourcesLabel[10].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 475), true, 0, "Sprite Bullet, Flame, Missile, Scatter, Logo Missile, Logo Scatter, Logo Flame : (Professeur) François Paradis", 200, Color::White);
	creatorLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 525), true, 0, "DEVS", 50, Color::White);
	namesLabel[0].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 575), true, 0, "Jérémie Bertrand", 50, Color::White);
	namesLabel[1].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 625), true, 0, "Mike Bédard", 50, Color::White);
	backButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 675), true, 300, "BACK", 4);

	return true;
}

/// <summary>
/// Gère la mise à jour de la scène
/// </summary>
void SceneCredits::update()
{
}

/// <summary>
/// Gère l'affichage de la scène
/// </summary>
void SceneCredits::draw()
{
	mainWin->clear();
	mainWin->draw(titleScreenImage);
	titleLabel.draw(mainWin);
	sourceLabel.draw(mainWin);
	sourcesLabel[0].draw(mainWin);
	for (int i = 0; i < 11; i++) 
	{
		sourcesLabel[i].draw(mainWin);
	}
	creatorLabel.draw(mainWin);
	namesLabel[0].draw(mainWin);
	namesLabel[1].draw(mainWin);
	backButton.draw(mainWin);
	mainWin->display();
}

/// <summary>
/// Gère les événements liés à l'interface graphique
/// </summary>
/// <param name="eventType">Type d'événement</param>
void SceneCredits::onUIEvent(const UIEventType & eventType)
{
	switch (eventType)
	{
	case LEFT_MOUSE_PRESSED:
		//Valider si on a appuyé ou non sur un bouton
		backButton.pressed(Mouse::getPosition(*mainWin));
		break;
	case LEFT_MOUSE_RELEASED:
		if (backButton.released(Mouse::getPosition(*mainWin)))
		{
			transitionToScene(TITLE);
		}
		break;
	case BACK:
		transitionToScene(previousScene);
		break;
	}
}
