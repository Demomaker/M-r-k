#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Repr�sente le concept logique et graphique d'un indicateur de score dans l'espace de jeu
/// </summary>
/// <seealso cref="sf::Text" />
class ScoreIndicator : public sf::Text
{
public:	
	/// <summary>
	/// Constructeur d'un indicateur de score
	/// </summary>
	ScoreIndicator();

	/// <summary>
	/// Met � jour l'�tat de l'indicateur (Actif ou inactif)
	/// </summary>
	/// <param name="active">�tat actif ou non de l'indicateur</param>
	void setActive(const bool& active);

	/// <summary>
	/// D�termine si l'indicateur est actif
	/// </summary>
	/// <returns>�tat actif ou non de l'indicateur</returns>
	bool isActive() const;

	/// <summary>
	/// Initialise toutes les instances
	/// </summary>
	/// <param name="mainFont">Police d'�criture principale</param>
	static void initAllInstances(const sf::Font& mainFont);

	/// <summary>
	/// Met � jour toutes les instances de la classe qui sont actives
	/// </summary>
	/// <param name="timeSpend">Le temps �coul�</param>
	static void updateActiveInstances(const float& timeSpend);

	/// <summary>
	/// Dessine toutes les instances de la classe qui sont actives
	/// </summary>
	/// <param name="mainWin">Fen�tre de jeu principale</param>
	static void drawActiveInstances(sf::RenderWindow& mainWin);

	/// <summary>
	/// Active un indicateur de score
	/// </summary>
	/// <param name="position">La position 2D</param>
	/// <param name="value">La valeur � afficher</param>
	static void spawnAScoreIndicator(const sf::Vector2f& position, const int& value);

	/// <summary>
	/// Nombre d'instances de la classe
	/// </summary>
	const static int MAX_NB_SCORE_INDICATORS = 30;
	/// <summary>
	/// Dur�e d'afichage
	/// </summary>
	const static int DISPLAY_TIME = 2;
private:
	/// <summary>
	/// �tat actif ou non
	/// </summary>
	bool active = false;
	/// <summary>
	/// Tableau des instances de la classe
	/// </summary>
	static ScoreIndicator instances[MAX_NB_SCORE_INDICATORS];
	/// <summary>
	/// Chronom�tre pour g�rer le temps d'activation
	/// </summary>
	float chronometer;
};

