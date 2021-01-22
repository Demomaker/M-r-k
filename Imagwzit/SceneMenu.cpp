#include "SceneMenu.h"
#include "Textbox.h"
#include "CustomButton.h"

/// <summary>
/// Boucle principale de la scène
/// </summary>
/// <return>Prochaine scène à charger</return>
SceneType SceneMenu::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return nextScene;
}

/// <summary>
/// Initialise la scène
/// </summary>
/// <param name="window">Fenêtre de jeu</param>
/// <return>Succès ou non de l'initialisation</return>
bool SceneMenu::init(RenderWindow * const window)
{
	if (!font.loadFromFile("Fonts\\segoepr.ttf"))
	{
		return false;
	}

	this->mainWin = window;
	isRunning = true;

	return true;
}


/// <summary>
/// Gère les entrées de l'utilisateur
/// </summary>
void SceneMenu::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin corrctement à l'application
			transitionToScene(EXIT);
		}

		//-------------------SELECTION DE TEXTBOX ACTIVE------------------------------------//
		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				onUIEvent(UIEventType::LEFT_MOUSE_PRESSED);
			}
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				onUIEvent(UIEventType::LEFT_MOUSE_RELEASED);
			}
		}

		//-----------UN ÉVÉNEMENT DE TOUCHE DE CLAVIER AVEC UN TEXTBOX ACTIF---//
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				onUIEvent(UIEventType::BACK);
			}
			else if (activeTextbox != nullptr)
			{
				//ON PEUT SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
				//LES TEXTBOX D'UNE SCÈNE
				if (event.key.code == Keyboard::Return)
				{
					unwritableKeyPressed = true; //Pour s'assurer que enter n'est pas saisie comme caractère
					onUIEvent(UIEventType::CONTINUE);
					activeTextbox = nullptr;

				}
				else if (event.key.code == Keyboard::BackSpace)
				{
					activeTextbox->removeCharacter();
					unwritableKeyPressed = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
				}
				else if (event.key.code == Keyboard::Space || event.key.code == Keyboard::Tab)
				{
					unwritableKeyPressed = true;  //Pour s'assurer que space et tab ne soient pas saisis comme caractère
				}
			}
		}

		//Attention : TextEntered est différent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.5/window-events-fr.php
		if (!unwritableKeyPressed && activeTextbox != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre à vous d'aller plus loin si vous voulez)
				activeTextbox->addCharacter((char)event.text.unicode);
			}
		}
	}

	//Dans tous les cas on netoie ces conditions après chaque boucle.
	unwritableKeyPressed = false;
}

/// <summary>
/// Met à jour le Textbox sélectionné
/// </summary>
/// <param name="textbox">Nouveau Textbox sélectionné</param>
void SceneMenu::selectTextbox(Textbox & textbox)
{
	if (activeTextbox != nullptr)
	{
		activeTextbox->unSelect();
	}
	activeTextbox = &textbox; //Ce textbox devient actif
	if (activeTextbox->getOutlineColor() == Color::Red)
	{
		labelError.setText(""); //on efface le message d'erreur
	}
	activeTextbox->select();  //on l'affiche comme étant sélectionné
}
