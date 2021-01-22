#include "Spider.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneGame.h"

/// <summary>
/// Rectangles d'animation de l'ennemi
/// </summary>
sf::IntRect Spider::intRects[MAX_ANIMATIONS_PER_LAYER * MAX_ANIMATION_LAYERS];

/// <summary>
/// Texture de l'ennemi
/// </summary>
sf::Texture Spider::spiderT;

/// <summary>
/// Constructeur d'un spider
/// </summary>
Spider::Spider() : Enemy(1)
{
	speed = MOVE_SPEED;
	setTexture(spiderT);
	setOrigin(intRects[0].width / 2, intRects[0].height / 2);
	setTextureRect(intRects[0]);
	frames = rand() % 40;
	projectileType = ProjectileType::SpiderWeb;
}

/// <summary>
/// Met à jour le spider
/// </summary>
/// <param name="playerPosition">La position du joueur</param>
/// <param name="playerIsActive">Le joueur est en vie ou non</param>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
void Spider::update(const float& timeSpend, SceneGame & scene)
{
	if (!isActive())
		return;

	Vector2f playerPosition = Player::getInstance()->getPosition();

	frames++;
	timeSinceLastShoot += timeSpend / FRAMES_PER_SECOND;

	weaponAngle = atan2(playerPosition.y - getPosition().y, playerPosition.x - getPosition().x);

	if (!isSlowed && sqrt(pow(playerPosition.y - getPosition().y, 2) + pow(playerPosition.x - getPosition().x, 2)) < 500 && timeSinceLastShoot > 2)
	{
		// L'ennemi tire un projectile
		timeSinceLastShoot = 0;
		Projectile::spawnAProjectile(weaponAngle, *this, false);
	}

	(abs(weaponAngle) > M_PI / 2 && abs(weaponAngle) < 3 * M_PI / 2 ? animationLayer = 1 : animationLayer = 3);

	// Le spider change de direction si le joueur est inactif
	if (!Player::getInstance()->isActive())
	{
		switch (animationLayer)
		{
		case 1:
			animationLayer = 3;
			break;
		case 3:
			animationLayer = 1;
			break;
		}
		weaponAngle -= M_PI;
	}

	// Si le spider est presque sur le joueur
	else if (Player::getInstance()->isActive() && abs(playerPosition.y - getPosition().y) < POSITION_THRESHOLD && abs(playerPosition.x - getPosition().x) < POSITION_THRESHOLD)
	{
		setPosition(playerPosition);
		movement = Vector2f(0, 0);
	}
	else
	{
		animation = (frames / (FRAMES_BEFORE_ANIMATION_CHANGE)) % MAX_ANIMATIONS_PER_LAYER;
		animate(animationLayer, animation);
		if (sqrt(pow(playerPosition.y - getPosition().y, 2) + pow(playerPosition.x - getPosition().x, 2)) > 500)
		{
			movement = Vector2f(cos(weaponAngle) * speed, sin(weaponAngle) * speed);
		}
		else 
		{
			movement = Vector2f(0,0);
		}
		// Déplacer le spider
		scene.isWalkableArea(movement, getPosition());
	}

	Enemy::update(timeSpend, scene);
}

/// <summary>
/// Animer l'ennemi
/// </summary>
/// <param name="layer">Le niveau d'animation.</param>
/// <param name="animation">Le numéro d'animation.</param>
void Spider::animate(int layer, int animation)
{
	animation += MAX_ANIMATIONS_PER_LAYER * layer;
	setTextureRect(intRects[animation]);
}

/// <summary>
/// Initialise les composants utiles à la classe
/// </summary>
/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
bool Spider::init()
{
	if (!spiderT.loadFromFile("Sprites\\FreeArt\\spider.png"))
	{
		return false;
	}

	int localAnimation = 0;
	int localLayer = 0;

	// Initialiser les rectangles d'animation
	for (int i = 0; i < MAX_ANIMATIONS_PER_LAYER * MAX_ANIMATION_LAYERS; i++)
	{
		if (i % MAX_ANIMATIONS_PER_LAYER == 0 && i != 0) {
			localAnimation = 0;
			localLayer++;
		}
		intRects[i].top = TILE_SIZE * (localLayer);
		intRects[i].left = TILE_SIZE * (localAnimation);
		
		intRects[i].width = TILE_SIZE;
		intRects[i].height = TILE_SIZE;
		localAnimation++;
	}

	return true;
}