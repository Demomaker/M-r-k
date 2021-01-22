#pragma once
#include "Scene.h"
#include "Textbox.h"
#include "CustomButton.h"

	/// <summary>
	/// Représente le concept d'un scène de menu
	/// </summary>
	class SceneMenu : public Scene
	{
	public:
		/// <summary>
		/// Boucle principale de la scène
		/// </summary>
		/// <return>Prochaine scène à charger</return>
		SceneType run();

		/// <summary>
		/// Initialise la scène
		/// </summary>
		/// <param name="window">Fenêtre de jeu</param>
		/// <return>Succès ou non de l'initialisation</return>
		virtual bool init(RenderWindow * const window);

		/// <summary>
		/// Gère les entrées de l'utilisateur
		/// </summary>
		void getInputs();

		/// <summary>
		/// Gère la mise à jour de la scène
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// Gère l'affichage de la scène
		/// </summary>
		virtual void draw() = 0;


	protected:
		/// <summary>
		/// Met à jour le Textbox sélectionné
		/// </summary>
		/// <param name="textbox">Nouveau Textbox sélectionné</param>
		void selectTextbox(Textbox& textbox);

		/// <summary>
	/// Gère les événements liés à l'interface graphique
	/// </summary>
	/// <param name="eventType">Type d'événement</param>
		virtual void onUIEvent(const UIEventType& eventType) = 0;


		/// <summary>
		/// Scène qui était chargé avant celle-ci
		/// </summary>
		SceneType previousScene;

		/// <summary>
		/// Détermine si un caractère non valide a été tapé dans un Textbox
		/// </summary>
		bool unwritableKeyPressed = false;

		/// <summary>
		/// Composant permettant l'affichage des messages d'erreur
		/// </summary>
		Label labelError;

		/// <summary>
		/// Textbox sélectionné
		/// </summary>
		Textbox* activeTextbox = nullptr;
	};

