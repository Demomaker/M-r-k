#include "Explosion.h"
#include "SceneGame.h"

/// <summary>
/// Tableau des instances de la classe
/// </summary>
Explosion Explosion::instances[Explosion::MAX_NB_EXPLOSIONS];

/// <summary>
/// Rect qui contient la position des frames de l'animation
/// </summary>
sf::IntRect Explosion::anims[Explosion::NB_ANIMS];

/// <summary>
/// Texture qui contient l'animation de l'explosion
/// </summary>
sf::Texture Explosion::explosionT;

/// <summary>
/// Constructeur d'une explosion
/// </summary>
Explosion::Explosion()
{
	animator = chronometer = 0;
}

/// <summary>
/// Met � jour l'�tat de l'explosion (Actif ou inactif)
/// </summary>
/// <param name="active">�tat actif ou non de l'explosion</param>
void Explosion::setActive(const bool& active)
{
	this->active = active;
}

/// <summary>
/// D�termine si l'explosion est active
/// </summary>
/// <returns>�tat actif ou non de l'explosion</returns>
bool Explosion::isActive() const
{
	return active;
}

/// <summary>
/// Initialise toutes les instances
/// </summary>
bool Explosion::init()
{
	if (!explosionT.loadFromFile("Sprites\\FreeArt\\Explosion.png"))
	{
		return false;
	}

	// Initiliser les rects d'animations
	for (int i = 0; i < NB_ANIMS; i++)
	{
		anims[i].top = RECT_SIZE * (i / NB_LINES_IN_SRITESHEET);
		anims[i].left = RECT_SIZE * (i % NB_COLS_IN_SRITESHEET);
		anims[i].width = RECT_SIZE;
		anims[i].height = RECT_SIZE;
	}

	// Initialiser toutes les instances de la classe
	for (int i = 0; i < MAX_NB_EXPLOSIONS; i++)
	{
		instances[i].setTexture(explosionT, true);
		instances[i].setScale(2, 2);
		instances[i].setOrigin(RECT_SIZE / 2, RECT_SIZE / 2);
	}
	return true;
}

/// <summary>
/// Met � jour toutes les instances de la classe qui sont actives
/// </summary>
/// <param name="timeSpend">Le temps �coul�</param>
void Explosion::updateActiveInstances(const float& timeSpend)
{
	for (int i = 0; i < MAX_NB_EXPLOSIONS; i++)
	{
		if (instances[i].isActive())
		{
			// On met � jour l'instance si elle est active
			instances[i].setTextureRect(anims[instances[i].animator++]);
			if (instances[i].animator >= NB_ANIMS)
			{
				// On d�sactive l'instance si sa dur�e de vie atteint z�ro
				instances[i].setActive(false);
				instances[i].chronometer = 0;
				instances[i].animator = 0;
			}
		}
	}
}

/// <summary>
/// Dessine toutes les instances de la classe qui sont actives
/// </summary>
/// <param name="mainWin">Fen�tre de jeu principale</param>
void Explosion::drawActiveInstances(sf::RenderWindow & mainWin)
{
	for (int i = 0; i < MAX_NB_EXPLOSIONS; i++)
	{
		if (instances[i].isActive())
		{
			// Dessiner l'instance � l'�cran si elle est active
			mainWin.draw(instances[i]);
		}
	}
}

/// <summary>
	/// D�sactive toutes les instances de la classe
	/// </summary>
void Explosion::disableAllActiveInstances()
{
	for (int i = 0; i < MAX_NB_EXPLOSIONS; i++)
	{
		if (instances[i].isActive())
		{
			// On d�sactive l'instance si elle est active
			instances[i].setActive(false);
			instances[i].chronometer = 0;
			instances[i].animator = 0;
		}
	}
}

/// <summary>
/// Active une explosion
/// </summary>
/// <param name="position">La position 2D</param>
void Explosion::spawnAnExplosion(const sf::Vector2f & position)
{
	for (int i = 0; i < MAX_NB_EXPLOSIONS; i++)
	{
		if (!instances[i].isActive())
		{
			// Initialiser la premi�re explosion inactictive
			instances[i].setPosition(position);
			instances[i].setActive(true);
			break;
		}
	}
}
