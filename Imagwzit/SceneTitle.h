#pragma once
#include "SceneMenu.h"

using namespace sf;

/// <summary>
/// Représente le concept d'une scène de titre
/// </summary>
class SceneTitle : public SceneMenu
{
public:
	/// <summary>
	/// Initialise la scène
	/// </summary>
	/// <param name="window">Fenêtre de jeu</param>
	/// <return>Succès ou non de l'initialisation</return>
	bool init(RenderWindow * const window) override;

	/// <summary>
	/// Gère la mise à jour de la scène
	/// </summary>
	void update() override;

	/// <summary>
	/// Gère l'affichage de la scène
	/// </summary>
	void draw() override;

	/// <summary>
	/// Gère les événements liés à l'interface graphique
	/// </summary>
	/// <param name="eventType">Type d'événement</param>
	void onUIEvent(const UIEventType& eventType) override;

private:
	/// <summary>
	/// Texture de l'image titre
	/// </summary>
	Texture titleScreenImageT;

	/// <summary>
	/// Sprite de l'image titre
	/// </summary>
	Sprite titleScreenImage;

	/// <summary>
	/// Bouton de transition vers jouer
	/// </summary>
	CustomButton playButton;

	/// <summary>
	/// Bouton de transition vers les instructions
	/// </summary>
	CustomButton instructionsButton;

	/// <summary>
	/// Bouton de transition vers les crédits
	/// </summary>
	CustomButton creditsButton;

	/// <summary>
	/// Bouton de transition vers quitter
	/// </summary>
	CustomButton exitButton;


	/// <summary>
	/// Label pour le titre de la scène
	/// </summary>
	Label merekLabel;
};
