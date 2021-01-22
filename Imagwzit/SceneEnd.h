#pragma once
#include "SceneMenu.h"

using namespace sf;

/// <summary>
/// Représente le concept d'une scène de fin
/// </summary>
class SceneEnd : public SceneMenu
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
	/// Écrire un score dans un certain fichier
	/// </summary>
	/// <param name="file">Le fichier.</param>
	/// <param name="score">Le score.</param>
	void writeScoreInFile(std::string file, int score);
	
	/// <summary>
	/// Mettre tous les scores dans le tableau de scores du fichier spécifié
	/// </summary>
	/// <param name="file">The file.</param>
	void putAllScoresInScoreArrayFromFile(std::string file);
	
	/// <summary>
	/// Obtenir le dernier score.
	/// </summary>
	/// <returns>Le dernier score</returns>
	int getLastScore();

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
	/// Label pour l'affichage de "gameOver"
	/// </summary>
	Label gameOverLabel;

	/// <summary>
	/// Label pour le score du joueur
	/// </summary>
	Label scoreLabel;

	/// <summary>
	/// Label pour le dernier score
	/// </summary>
	Label lastScoreLabel;
	
	/// <summary>
	/// Le nombre de scores
	/// </summary>
	int numScores = 0;
	
	/// <summary>
	/// Le pointeur de scores
	/// </summary>
	int * scores;

	/// <summary>
	/// Bouton de transition vers jouer
	/// </summary>
	CustomButton restartButton;

	/// <summary>
	/// Bouton de transition vers les crédits
	/// </summary>
	CustomButton menuButton;

	/// <summary>
	/// Bouton de transition vers quitter
	/// </summary>
	CustomButton exitButton;
};
