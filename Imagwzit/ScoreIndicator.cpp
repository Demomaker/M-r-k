#include "ScoreIndicator.h"
#include "SceneGame.h"

/// <summary>
/// Tableau des instances de la classe
/// </summary>
ScoreIndicator ScoreIndicator::instances[ScoreIndicator::MAX_NB_SCORE_INDICATORS];

/// <summary>
/// Constructeur d'un indicateur de score
/// </summary>
ScoreIndicator::ScoreIndicator()
{
	chronometer = 0;
}

/// <summary>
/// Met à jour l'état de l'indicateur (Actif ou inactif)
/// </summary>
/// <param name="active">État actif ou non de l'indicateur</param>
void ScoreIndicator::setActive(const bool& active)
{
	this->active = active;
}

/// <summary>
/// Détermine si l'indicateur est actif
/// </summary>
/// <returns>État actif ou non de l'indicateur</returns>
bool ScoreIndicator::isActive() const
{
	return active;
}

/// <summary>
/// Initialise toutes les instances
/// </summary>
/// <param name="mainFont">Police d'écriture principale</param>
void ScoreIndicator::initAllInstances(const sf::Font& mainFont)
{
	// Initialiser toutes les instances de la classe
	for (int i = 0; i < MAX_NB_SCORE_INDICATORS; i++) 
	{
		instances[i].setString("");
		instances[i].setFont(mainFont);
		instances[i].setCharacterSize(12);
		instances[i].setFillColor(sf::Color::White);
	}
}

/// <summary>
/// Met à jour toutes les instances de la classe qui sont actives
/// </summary>
/// <param name="timeSpend">Le temps écoulé</param>
void ScoreIndicator::updateActiveInstances(const float& timeSpend)
{
	for (int i = 0; i < MAX_NB_SCORE_INDICATORS; i++)
	{
		if (instances[i].isActive()) 
		{
			// On met à jour l'instance si elle est active
			instances[i].chronometer += timeSpend / FRAMES_PER_SECOND;
			instances[i].setPosition(instances[i].getPosition().x, instances[i].getPosition().y - 20 * timeSpend / 60);
			instances[i].setColor(sf::Color(255, 255, 255, 255 * (1 - instances[i].chronometer / DISPLAY_TIME)));
			if (instances[i].chronometer >= DISPLAY_TIME) 
			{
				// On désactive l'instance si sa durée de vie atteint zéro
				instances[i].setActive(false);
				instances[i].setColor(sf::Color(255, 255, 255, 255));
				instances[i].chronometer = 0;
			}
		}
	}
}

/// <summary>
/// Dessine toutes les instances de la classe qui sont actives
/// </summary>
/// <param name="mainWin">Fenêtre de jeu principale</param>
void ScoreIndicator::drawActiveInstances(sf::RenderWindow & mainWin)
{
	for (int i = 0; i < MAX_NB_SCORE_INDICATORS; i++)
	{
		if (instances[i].isActive())
		{
			// Dessiner l'instance à l'écran si elle est active
			mainWin.draw(instances[i]);
		}
	}
}

/// <summary>
/// Active un indicateur de score
/// </summary>
/// <param name="position">La position 2D</param>
/// <param name="value">La valeur à afficher</param>
void ScoreIndicator::spawnAScoreIndicator(const sf::Vector2f & position, const int & value)
{
	for (int i = 0; i < MAX_NB_SCORE_INDICATORS; i++)
	{
		if (!instances[i].isActive())
		{
			// Initialiser le premier indicateur de score inactif
			instances[i].setPosition(position.x, position.y - 40);
			instances[i].setString(std::to_string(value));
			instances[i].setOrigin(instances[i].getGlobalBounds().width / 2, instances[i].getGlobalBounds().height / 2);
			instances[i].setActive(true);
			break;
		}
	}
}
