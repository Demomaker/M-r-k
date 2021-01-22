#include "SceneMenu.h"
#include "Textbox.h"
#include "CustomButton.h"

/// <summary>
/// Boucle principale de la sc�ne
/// </summary>
/// <return>Prochaine sc�ne � charger</return>
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
/// Initialise la sc�ne
/// </summary>
/// <param name="window">Fen�tre de jeu</param>
/// <return>Succ�s ou non de l'initialisation</return>
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
/// G�re les entr�es de l'utilisateur
/// </summary>
void SceneMenu::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin corrctement � l'application
			transitionToScene(EXIT);
		}

		//-------------------SELECTION DE TEXTBOX ACTIVE------------------------------------//
		//Si on a un �v�nement de click de souris
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

		//-----------UN �V�NEMENT DE TOUCHE DE CLAVIER AVEC UN TEXTBOX ACTIF---//
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				onUIEvent(UIEventType::BACK);
			}
			else if (activeTextbox != nullptr)
			{
				//ON PEUT SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
				//LES TEXTBOX D'UNE SC�NE
				if (event.key.code == Keyboard::Return)
				{
					unwritableKeyPressed = true; //Pour s'assurer que enter n'est pas saisie comme caract�re
					onUIEvent(UIEventType::CONTINUE);
					activeTextbox = nullptr;

				}
				else if (event.key.code == Keyboard::BackSpace)
				{
					activeTextbox->removeCharacter();
					unwritableKeyPressed = true;  //Pour s'assurer que backspace n'est pas saisie comme caract�re
				}
				else if (event.key.code == Keyboard::Space || event.key.code == Keyboard::Tab)
				{
					unwritableKeyPressed = true;  //Pour s'assurer que space et tab ne soient pas saisis comme caract�re
				}
			}
		}

		//Attention : TextEntered est diff�rent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.5/window-events-fr.php
		if (!unwritableKeyPressed && activeTextbox != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre � vous d'aller plus loin si vous voulez)
				activeTextbox->addCharacter((char)event.text.unicode);
			}
		}
	}

	//Dans tous les cas on netoie ces conditions apr�s chaque boucle.
	unwritableKeyPressed = false;
}

/// <summary>
/// Met � jour le Textbox s�lectionn�
/// </summary>
/// <param name="textbox">Nouveau Textbox s�lectionn�</param>
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
	activeTextbox->select();  //on l'affiche comme �tant s�lectionn�
}
