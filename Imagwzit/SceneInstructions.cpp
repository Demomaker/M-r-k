#include "SceneInstructions.h"
#include "Constants.h"

/// <summary>
/// Initialise la sc�ne
/// </summary>
/// <param name="window">Fen�tre de jeu</param>
/// <return>Succ�s ou non de l'initialisation</return>
bool SceneInstructions::init(RenderWindow * const window)
{
	if (!SceneMenu::init(window) || !titleScreenImageT.loadFromFile("Sprites\\Field.jpg"))
	{
		return false;
	}

	previousScene = TITLE;

	titleScreenImage.setTexture(titleScreenImageT);
	titleLabel.initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 125), true, 0, "M�R�K - INSTRUCTIONS", 50, Color::White);
	descriptionsLabel[0].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 75), true, 0, "Bienvenue � M�R�K! Ce jeu saura satisfaire votre urge de tuer des monstres juste pour le plaisir.", 200, Color::White);
	descriptionsLabel[1].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 25), true, 0, "Vous commencez � un endroit tranquille de la carte, mais plus que vous explorez, plus que vous aurez � affronter de monstres. MUAHAHAHAH!", 200, Color::White);
	descriptionsLabel[2].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 25), true, 0, "Le but de ce jeu est de rapporter le plus de points possibles tout en s'assurant de ne pas mourir.", 200, Color::White);
	descriptionsLabel[3].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 75), true, 0, "Vous pourrez rencontrer diff�rents monstres tels que : Des araign�es, des squelettes, des zombies, des fant�mes et... DES HOMMES � BOMBES! (Des bombermans, oui)", 200, Color::White);
	descriptionsLabel[4].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 125), true, 0, "Repoussez les � l'aide de vos balles de fusil, vos missiles, votre lance-flammes, votre lanceur de rockets, votre fusil � �parpillement et votre fusil � laser! C'est \"cool\" en?", 200, Color::White);
	descriptionsLabel[5].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 175), true, 0, "Plusieurs super-pouvoirs apparaitront � vous lorsque vous tuerez certains de ces b�tes monstrueuses. Utilisez les avec pr�caution.", 200, Color::White);
	descriptionsLabel[6].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 225), true, 0, "Les contr�les du jeu sont simples : le clavier et la souris sont les seuls outils dont vous avez besoin!", 200, Color::White);
	descriptionsLabel[7].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 275), true, 0, "Les touches W(pour se d�placer vers le haut),A(pour se d�placer vers la gauche),S(pour se d�placer vers le bas),D(pour se d�placer vers la droite) vous permettent de vous d�placer.", 200, Color::White);
	descriptionsLabel[8].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 325), true, 0, "Le clique gauche de la souris permet de tirer et la roulette permet de changer d'arme. La souris oriente aussi le fusil du joueur.", 200, Color::White);
	descriptionsLabel[9].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 375), true, 0, "Rendez-vous � l'�chelle de sortie pour pouvoir sortir du niveau pr�sent et aller dans le prochain. Tous les niveaux sont faits al�atoirement.", 200, Color::White);
	descriptionsLabel[10].initializeFloatingTextLabel(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 425), true, 0, "Fin des instructions, veuillez aller jouer au jeu maintenant. Merci! ", 200, Color::White);
	backButton.initializeStandardCustomButton(font, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 475), true, 300, "BACK", 4);

	return true;
}

/// <summary>
/// G�re la mise � jour de la sc�ne
/// </summary>
void SceneInstructions::update()
{
}

/// <summary>
/// G�re l'affichage de la sc�ne
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
/// G�re les �v�nements li�s � l'interface graphique
/// </summary>
/// <param name="eventType">Type d'�v�nement</param>
void SceneInstructions::onUIEvent(const UIEventType & eventType)
{
	switch (eventType)
	{
	case LEFT_MOUSE_PRESSED:
		//Valider si on a appuy� ou non sur un bouton
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
