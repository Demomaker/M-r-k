#include "Projectile.h"
#include "Zombie.h"
#include "Ghost.h"
#include "Bomb.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneGame.h"

/// <summary>
/// Tableau qui contient les textures des projectiles disponibles en jeu
/// </summary>
sf::Texture Projectile::projectileT[6];

/// <summary>
/// Tableau qui contient les instances de la classe
/// </summary>
Projectile Projectile::instances[Projectile::MAX_NB_PROJECTILES + Projectile::MAX_NB_PROJECTILES_ENNEMIS]; 

/// <summary>
/// Durée de vie des munitions de type "Flame"
/// </summary>
const float Projectile::FLAME_LIFE_TIME = 0.3f;

/// <summary>
/// Durée de vie des munitions de type "Laser"
/// </summary>
const float Projectile::LASER_LIFE_TIME = 0.2f;

/// <summary>
/// Constructeur d'un projectile
/// </summary>
Projectile::Projectile()
{
	type = ProjectileType::Bullet;
	speed = BASE_SPEED;
}

/// <summary>
/// Fait apparaître un projectile dans l'espace de jeu
/// </summary>
/// <param name="_angle">Angle du projectile</param>
/// <param name="_player">Le joueur</param>
void Projectile::spawn(const float& angle, const Character& character, bool shotByPlayer)
{
	this->angle = angle;
	this->shotByPlayer = shotByPlayer;
	setPosition(character.getPosition() + sf::Vector2f(cos(angle) * (character.getGlobalBounds().width / 2), sin(angle) * (character.getGlobalBounds().height / 2)));
	setRotation(angle * 180 / M_PI);
	setActive(true);
}

/// <summary>
/// Met à jour le projectile
/// </summary>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
/// <param name="sceneGame">Référence à la partie en cours</param>
void Projectile::update(const float& timeSpend, SceneGame & sceneGame)
{
	if (type == ProjectileType::Flame || type == ProjectileType::Laser)
	{
		// Gérer la durée de vie d'un projectile de feu et de laser
		chronometer += timeSpend / FRAMES_PER_SECOND;
		if (chronometer > ((type == Flame) ? FLAME_LIFE_TIME : LASER_LIFE_TIME))
		{
			chronometer = 0;
			setActive(false);
			return;
		}
	}

	if (type == Bomb) 
	{
		if (detectCollisionWithOthers(this)) 
		{
			// On fait exploser une bombe sur sa position s'il y a une collision
			PowerUp::Bomb bomb = PowerUp::Bomb(GreenBombType);
			bomb.setPosition(getPosition());
			bomb.pickUp();
			setActive(false);
			return;
		}
	}

	// Déplacer le projectile
	move(cos(angle) * speed * timeSpend, sin(angle) * speed * timeSpend);

	// Désactiver le projectile lorsqu'il sort de la zone de jeu
	if (type != Laser) 
	{
		if (getPosition().x < 0 || getPosition().x > WORLD_WIDTH || getPosition().y < 0 || getPosition().y > WORLD_HEIGHT || !sceneGame.isWalkableArea(Vector2f(0, 0), getPosition()))
		{
			if (type == Bomb)
			{
				// On fait exploser une bombe sur sa position s'il entre en collision avec un mur
				PowerUp::Bomb bomb = PowerUp::Bomb(GreenBombType);
				bomb.setPosition(getPosition());
				bomb.pickUp();
			}
			setActive(false);
		}
	}
}

/// <summary>
/// Obtient le type de projectile
/// </summary>
/// <returns>Type de projectile</returns>
ProjectileType Projectile::getType() const
{
	return type;
}

/// <summary>
/// Détermine si le projectile a été tiré par le joueur
/// </summary>
/// <returns>Vrai si tiré par le joueur, faux sinon</returns>
bool Projectile::isShotByPlayer() const
{
	return shotByPlayer;
}

/// <summary>
/// Mettre à jour le type de projectile
/// </summary>
/// <param name="type">Type de projectile</param>
void Projectile::setType(const ProjectileType & type)
{
	this->type = type;
	// Mettre à jour l'apparence du projectile
	setTexture(projectileT[static_cast<int>(type) + 1], true);
	setOrigin(projectileT[static_cast<int>(type) + 1].getSize().x / 2, projectileT[static_cast<int>(type) + 1].getSize().y / 2);
	// Mettre à jour la vitesse du projectile
	switch (type)
	{
	case ProjectileType::Bullet:
		speed = BASE_SPEED;
		break;
	case ProjectileType::Flame:
		speed = FLAME_SPEED;
		break;
	case ProjectileType::Missile:
		speed = MISSILE_SPEED;
		break;
	case ProjectileType::Scatter:
		speed = SCATTER_SPEED;
		break;
	case ProjectileType::Laser:
		speed = LASER_SPEED;
		setOrigin(Vector2f(0, getLocalBounds().height / 2));
		break;
	case ProjectileType::SpiderWeb:
		speed = SPIDERWEB_SPEED;
		break;
	case ProjectileType::Bomb:
		speed = BOMB_SPEED;
		break;
	}
}

/// <summary>
/// Initialise les composants de la classe
/// </summary>
/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
bool Projectile::init()
{
	if (!projectileT[0].loadFromFile("Sprites\\Projectiles\\Bullet.png"))
	{
		return false;
	}

	if (!projectileT[1].loadFromFile("Sprites\\Projectiles\\Flame.png"))
	{
		return false;
	}

	if (!projectileT[2].loadFromFile("Sprites\\Projectiles\\Missile.png"))
	{
		return false;
	}

	if (!projectileT[3].loadFromFile("Sprites\\Projectiles\\Scatter.png"))
	{
		return false;
	}

	if (!projectileT[4].loadFromFile("Sprites\\Projectiles\\RocketLauncher.png"))
	{
		return false;
	}

	if (!projectileT[5].loadFromFile("Sprites\\Projectiles\\Laser.png"))
	{
		return false;
	}
	if (!projectileT[6].loadFromFile("Sprites\\FreeArt\\spiderweb.png"))
	{
		return false;
	}
	// Initialiser les instances de projectile
	for (int i = 0; i < MAX_NB_PROJECTILES; i++)
	{
		instances[i].setTexture(projectileT[0]);
		instances[i].setOrigin(projectileT[0].getSize().x / 2, projectileT[0].getSize().y / 2);
	}
	for (int i = MAX_NB_PROJECTILES; i < MAX_NB_PROJECTILES + MAX_NB_PROJECTILES_ENNEMIS; i++) {

		instances[i].setTexture(projectileT[6]);
		instances[i].setOrigin(projectileT[6].getSize().x / 2, projectileT[6].getSize().y / 2);
	}

	return true;
}

/// <summary>
/// Met à jour toutes les instances de la classe qui sont actives
/// </summary>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
/// <param name="sceneGame">Référence à la partie en cours</param>
void Projectile::updateActiveInstances(const float& timeSpend, SceneGame & sceneGame)
{
	for (int i = 0; i < MAX_NB_PROJECTILES + MAX_NB_PROJECTILES_ENNEMIS; i++)
	{
		if (instances[i].isActive()) 
		{
			// On met à jour le projectile s'il est actif
			instances[i].update(timeSpend, sceneGame);
		}
	}
}

/// <summary>
/// Active un projectile
/// </summary>
/// <param name="player">Le joueur</param>
/// <param name="angle">L'orientation du projectile</param>
/// <param name="shotByPlayer">Vrai si tiré par le joueur</param>
void Projectile::spawnAProjectile(const float& angle, const Character & character, bool shotByPlayer)
{
	// Multiplicateur de l'angle pour faire apparâitre les trois projectiles à dispersion
	int scatterAngleMultiplier = -1;
	for (int i = 0; i < MAX_NB_PROJECTILES && scatterAngleMultiplier < 2; i++)
	{
		// On vérifie que le projectile est inactif
		if (!instances[i].isActive())
		{
			ProjectileType newType = (shotByPlayer ? Player::getInstance()->getCurrentProjectileType() : static_cast<const Enemy*>(&character)->getProjectileType());
			if (instances[i].getType() != newType)
			{
				// Changer le projectile pour celui du joueur si besoin
				instances[i].setType(newType);
			}
			if (instances[i].getType() == ProjectileType::Scatter) 
			{
				// Faire apparaître un projectile de dispersion
				instances[i].spawn(angle + scatterAngleMultiplier * M_PI / 8, character, shotByPlayer);
				// On passe à l'angle suivant
				scatterAngleMultiplier++;

			}
			else 
			{
				// On fait apparaître le projectile
				instances[i].spawn(angle, character, shotByPlayer);
				break;
			}
		}
	}
}

/// <summary>
/// Détermine si le bonus est en collision avec l'object de jeu spécifié
/// </summary>
/// <param name="other">GameObject avec lequel on teste la collision</param>
/// <returns>Vrai s'il y a une collision, faux sinon</returns>
Projectile * Projectile::checkCollisionWith(const GameObject & other)
{
	for (int i = 0; i < MAX_NB_PROJECTILES + MAX_NB_PROJECTILES_ENNEMIS; i++) 
	{
		if (instances[i].isActive() && instances[i].type != Bomb) 
		{
			// Si le projectile actif n'est pas une bombe
			if (instances[i].type == Laser)
			{
				// On fait un test entre les FloatRect s'il s'agit d'un laser
				if (instances[i].getGlobalBounds().intersects(other.getGlobalBounds()))
					return &instances[i];
			}
			else
			{
				// Sinon test avec cercles de collision
				if (instances[i].getCollisionCircle().checkCollision(other.getCollisionCircle())) 
				{
					return &instances[i];
				}
			}
		}
	}
	return nullptr;
}
