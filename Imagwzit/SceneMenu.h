#pragma once
#include "Scene.h"
#include "Textbox.h"
#include "CustomButton.h"

	/// <summary>
	/// Repr�sente le concept d'un sc�ne de menu
	/// </summary>
	class SceneMenu : public Scene
	{
	public:
		/// <summary>
		/// Boucle principale de la sc�ne
		/// </summary>
		/// <return>Prochaine sc�ne � charger</return>
		SceneType run();

		/// <summary>
		/// Initialise la sc�ne
		/// </summary>
		/// <param name="window">Fen�tre de jeu</param>
		/// <return>Succ�s ou non de l'initialisation</return>
		virtual bool init(RenderWindow * const window);

		/// <summary>
		/// G�re les entr�es de l'utilisateur
		/// </summary>
		void getInputs();

		/// <summary>
		/// G�re la mise � jour de la sc�ne
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// G�re l'affichage de la sc�ne
		/// </summary>
		virtual void draw() = 0;


	protected:
		/// <summary>
		/// Met � jour le Textbox s�lectionn�
		/// </summary>
		/// <param name="textbox">Nouveau Textbox s�lectionn�</param>
		void selectTextbox(Textbox& textbox);

		/// <summary>
	/// G�re les �v�nements li�s � l'interface graphique
	/// </summary>
	/// <param name="eventType">Type d'�v�nement</param>
		virtual void onUIEvent(const UIEventType& eventType) = 0;


		/// <summary>
		/// Sc�ne qui �tait charg� avant celle-ci
		/// </summary>
		SceneType previousScene;

		/// <summary>
		/// D�termine si un caract�re non valide a �t� tap� dans un Textbox
		/// </summary>
		bool unwritableKeyPressed = false;

		/// <summary>
		/// Composant permettant l'affichage des messages d'erreur
		/// </summary>
		Label labelError;

		/// <summary>
		/// Textbox s�lectionn�
		/// </summary>
		Textbox* activeTextbox = nullptr;
	};

