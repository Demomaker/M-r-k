#pragma once
#include "SceneMenu.h"

using namespace sf;

/// <summary>
/// Représente le concept d'une scène de crédits
/// </summary>
class SceneCredits : public SceneMenu
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
	/// Label pour le titre de la scène
	/// </summary>
	Label titleLabel;

	/// <summary>
	/// Label pour introduire les créateurs
	/// </summary>
	Label creatorLabel;

	/// <summary>
	/// Labels pour afficher les noms des créateurs
	/// </summary>
	Label namesLabel[2];

	/// <summary>
	/// Label pour introduire les sources
	/// </summary>
	Label sourceLabel;

	/// <summary>
	/// Labels pour afficher les noms des créateurs
	/// </summary>
	Label sourcesLabel[11];

	/// <summary>
	/// Bouton de transition vers menu
	/// </summary>
	CustomButton backButton;
};
