#include "Skeleton.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneGame.h"

/// <summary>
/// Rectangles d'animation de l'ennemi
/// </summary>
sf::IntRect Skeleton::intRects[MAX_ANIMATIONS_PER_LAYER * MAX_ANIMATION_LAYERS];

/// <summary>
/// Texture de l'ennemi
/// </summary>
sf::Texture Skeleton::skeletonT;

/// <summary>
/// Constructeur d'un skeleton
/// </summary>
Skeleton::Skeleton() : Enemy(1)
{
	speed = MOVE_SPEED;
	setTexture(skeletonT);
	setOrigin(intRects[0].width / 2, intRects[0].height / 2);
	setTextureRect(intRects[0]);
	frames = rand() % 40;
	projectileType = ProjectileType::Bullet;
}

/// <summary>
/// Met à jour le skeleton
/// </summary>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
void Skeleton::update(const float& timeSpend, SceneGame & scene)
{
	if (!isActive())
		return;

	frames++;
	timeSinceLastShoot += timeSpend / FRAMES_PER_SECOND;
	Vector2f playerPosition = Player::getInstance()->getPosition();
	weaponAngle = atan2(playerPosition.y - getPosition().y, playerPosition.x - getPosition().x);

	if (!isSlowed && sqrt(pow(playerPosition.y - getPosition().y, 2) + pow(playerPosition.x - getPosition().x, 2)) < 1000 && timeSinceLastShoot > 2)
	{
		// L'ennemi tire un projectile
		timeSinceLastShoot = 0;
		Projectile::spawnAProjectile(weaponAngle, *this, false);
	}

	(abs(weaponAngle) > M_PI / 2 && abs(weaponAngle) < 3 * M_PI / 2 ? animationLayer = 1 : animationLayer = 2);

	// Le skeleton change de direction si le joueur est inactif
	if (!Player::getInstance()->isActive())
	{
		switch (animationLayer)
		{
		case 1:
			animationLayer = 2;
			break;
		case 2:
			animationLayer = 1;
			break;
		}
		weaponAngle -= M_PI;
	}

	// Si le skeleton est presque sur le joueur
	else if (Player::getInstance()->isActive() && abs(playerPosition.y - getPosition().y) < POSITION_THRESHOLD && abs(playerPosition.x - getPosition().x) < POSITION_THRESHOLD)
	{
		setPosition(playerPosition);
		movement = Vector2f(0, 0);
	}
	else
	{
		animation = (frames / (FRAMES_BEFORE_ANIMATION_CHANGE)) % MAX_ANIMATIONS_PER_LAYER;
		animate(animationLayer, animation);
		movement = Vector2f(cos(weaponAngle) * speed, sin(weaponAngle) * speed);
		// Déplacer le skeleton
		scene.isWalkableArea(movement, getPosition());
	}

	Enemy::update(timeSpend, scene);
}

/// <summary>
/// Animer l'ennemi
/// </summary>
/// <param name="layer">Le niveau d'animation.</param>
/// <param name="animation">Le numéro d'animation.</param>
void Skeleton::animate(int layer, int animation)
{
	animation += MAX_ANIMATIONS_PER_LAYER * layer;
	setTextureRect(intRects[animation]);
}

/// <summary>
/// Initialise les composants utiles à la classe
/// </summary>
/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
bool Skeleton::init()
{
	if (!skeletonT.loadFromFile("Sprites\\FreeArt\\skeleton.png"))
	{
		return false;
	}

	int localAnimation = 0;
	int localLayer = 0;

	// Initialiser les rectangles d'animation
	for (int i = 0; i < MAX_ANIMATIONS_PER_LAYER * MAX_ANIMATION_LAYERS; i++)
	{
		if (i % MAX_ANIMATIONS_PER_LAYER == 0 && i != 0) 
		{
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