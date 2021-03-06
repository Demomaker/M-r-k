#pragma once
#include "SceneMenu.h"

using namespace sf;

/// <summary>
/// Repr�sente le concept d'une sc�ne de cr�dits
/// </summary>
class SceneCredits : public SceneMenu
{
public:
	/// <summary>
	/// Initialise la sc�ne
	/// </summary>
	/// <param name="window">Fen�tre de jeu</param>
	/// <return>Succ�s ou non de l'initialisation</return>
	bool init(RenderWindow * const window) override;

	/// <summary>
	/// G�re la mise � jour de la sc�ne
	/// </summary>
	void update() override;

	/// <summary>
	/// G�re l'affichage de la sc�ne
	/// </summary>
	void draw() override;

	/// <summary>
	/// G�re les �v�nements li�s � l'interface graphique
	/// </summary>
	/// <param name="eventType">Type d'�v�nement</param>
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
	/// Label pour le titre de la sc�ne
	/// </summary>
	Label titleLabel;

	/// <summary>
	/// Label pour introduire les cr�ateurs
	/// </summary>
	Label creatorLabel;

	/// <summary>
	/// Labels pour afficher les noms des cr�ateurs
	/// </summary>
	Label namesLabel[2];

	/// <summary>
	/// Label pour introduire les sources
	/// </summary>
	Label sourceLabel;

	/// <summary>
	/// Labels pour afficher les noms des cr�ateurs
	/// </summary>
	Label sourcesLabel[11];

	/// <summary>
	/// Bouton de transition vers menu
	/// </summary>
	CustomButton backButton;
};
