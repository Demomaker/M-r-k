#include "SceneInstructions.h"
#include "Constants.h"

/// <summary>
/// Initialise la scène
/// </summary>
/// <param name="window">Fenêtre de jeu</param>
/// <return>Succès ou non de l'initialisation</return>
bool SceneInstructions::init(RenderWindow * const window)
{
	if (!SceneMenu::init(window) || !titleScreenImageT.loadFromFile("Sprites\\Field.jpg"))
	{
		return false;
	}

	previousScene = TITLE;

	titleScreenImage.setTexture(titleScreenImageT);
	titleLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 125), true, 0, "MÉRÉK - INSTRUCTIONS", 50, Color::White);
	descriptionsLabel[0].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 75), true, 0, "Bienvenue à MÉRÉK! Ce jeu saura satisfaire votre urge de tuer des monstres juste pour le plaisir.", 200, Color::White);
	descriptionsLabel[1].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 25), true, 0, "Vous commencez à un endroit tranquille de la carte, mais plus que vous explorez, plus que vous aurez à affronter de monstres. MUAHAHAHAH!", 200, Color::White);
	descriptionsLabel[2].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 25), true, 0, "Le but de ce jeu est de rapporter le plus de points possibles tout en s'assurant de ne pas mourir.", 200, Color::White);
	descriptionsLabel[3].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 75), true, 0, "Vous pourrez rencontrer différents monstres tels que : Des araignées, des squelettes, des zombies, des fantômes et... DES HOMMES À BOMBES! (Des bombermans, oui)", 200, Color::White);
	descriptionsLabel[4].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 125), true, 0, "Repoussez les à l'aide de vos balles de fusil, vos missiles, votre lance-flammes, votre lanceur de rockets, votre fusil à éparpillement et votre fusil à laser! C'est \"cool\" en?", 200, Color::White);
	descriptionsLabel[5].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 175), true, 0, "Plusieurs super-pouvoirs apparaitront à vous lorsque vous tuerez certains de ces bêtes monstrueuses. Utilisez les avec précaution.", 200, Color::White);
	descriptionsLabel[6].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 225), true, 0, "Les contrôles du jeu sont simples : le clavier et la souris sont les seuls outils dont vous avez besoin!", 200, Color::White);
	descriptionsLabel[7].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 275), true, 0, "Les touches W(pour se déplacer vers le haut),A(pour se déplacer vers la gauche),S(pour se déplacer vers le bas),D(pour se déplacer vers la droite) vous permettent de vous déplacer.", 200, Color::White);
	descriptionsLabel[8].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 325), true, 0, "Le clique gauche de la souris permet de tirer et la roulette permet de changer d'arme. La souris oriente aussi le fusil du joueur.", 200, Color::White);
	descriptionsLabel[9].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 375), true, 0, "Rendez-vous à l'échelle de sortie pour pouvoir sortir du niveau présent et aller dans le prochain. Tous les niveaux sont faits aléatoirement.", 200, Color::White);
	descriptionsLabel[10].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 425), true, 0, "Fin des instructions, veuillez aller jouer au jeu maintenant. Merci! ", 200, Color::White);
	backButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 475), true, 300, "BACK", 4);

	return true;
}

/// <summary>
/// Gère la mise à jour de la scène
/// </summary>
void SceneInstructions::update()
{
}

/// <summary>
/// Gère l'affichage de la scène
/// </summary>
void SceneInstructions::draw()
{
	mainWin->clear();
	mainWin->draw(titleScreenImage);
	titleLabel.draw(mainWin);
	for (int i = 0; i < 20; i++) {
		descriptionsLabel[i].draw(mainWin);
	}
	backButton.draw(mainWin);
	mainWin->display();
}

/// <summary>
/// Gère les événements liés à l'interface graphique
/// </summary>
/// <param name="eventType">Type d'événement</param>
void SceneInstructions::onUIEvent(const UIEventType & eventType)
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
