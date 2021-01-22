#include "Ghost.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneGame.h"

/// <summary>
/// Rectangles d'animation de l'ennemi
/// </summary>
sf::IntRect Ghost::intRects[4];

/// <summary>
/// Texture de l'ennemi
/// </summary>
sf::Texture Ghost::ghostT;

/// <summary>
/// Constructeur d'un ghost
/// </summary>
Ghost::Ghost() : Enemy(1)
{
	speed = MOVE_SPEED;
	setTexture(ghostT);
	setOrigin(intRects[0].width / 2, intRects[0].height / 2);
	setTextureRect(intRects[0]);
	frames = rand() % 40;
}

/// <summary>
/// Met à jour le ghost
/// </summary>
/// <param name="playerPosition">La position du joueur</param>
/// <param name="playerIsActive">Le joueur est en vie ou non</param>
/// <param name="timeSpend">Le temps écoulé à la dernière frame</param>
void Ghost::update(const float& timeSpend, SceneGame & scene)
{
	if (!isActive())
		return;

	Vector2f playerPosition = Player::getInstance()->getPosition();
	frames++;

	weaponAngle = atan2(playerPosition.y - getPosition().y, playerPosition.x - getPosition().x);
	(abs(weaponAngle) > M_PI / 2 && abs(weaponAngle) < 3 * M_PI / 2 ? setScale(1, 1) : setScale(-1, 1));

	// Le ghost change de direction si le joueur est inactif
	if (!Player::getInstance()->isActive())
	{
		int scaleNumber = getScale().x;
		scaleNumber *= -1;
		setScale(scaleNumber, 1);
	}

	// Si le ghost est presque sur le joueur
	else if (Player::getInstance()->isActive() && abs(playerPosition.y - getPosition().y) < POSITION_THRESHOLD && abs(playerPosition.x - getPosition().x) < POSITION_THRESHOLD)
	{
		animationLayer = 0;
		animate(animationLayer,animation);
		setPosition(playerPosition);
		movement = Vector2f(0, 0);
		animation = (frames / (FRAMES_BEFORE_ANIMATION_CHANGE)) % MAX_ANIMATIONS_PER_LAYER;
	}
	else
	{
		animationLayer = 1;
		animation = (frames / (FRAMES_BEFORE_ANIMATION_CHANGE)) % MAX_ANIMATIONS_PER_LAYER;
		animate(animationLayer, animation);
		movement = Vector2f(cos(weaponAngle) * speed, sin(weaponAngle) * speed);
	}

	if (getCollisionCircle().checkCollision(Player::getInstance()->getCollisionCircle()))
	{
		// Inflige des dégâts au joueur s'il entre en collision avec ce dernier
		randomTeleport();
		Player::getInstance()->takeDamage(1,getColor());
	}

	Enemy::update(timeSpend, scene);
}

/// <summary>
/// Animer l'ennemi
/// </summary>
/// <param name="layer">Le niveau d'animation.</param>
/// <param name="animation">Le numéro d'animation.</param>
void Ghost::animate(int layer, int animation)
{
	animation += MAX_ANIMATIONS_PER_LAYER * layer;
	setTextureRect(intRects[animation]);
}

/// <summary>
/// Initialise les composants utiles à la classe
/// </summary>
/// <returns>Vrai lorsque l'initialisation a fonctionné, faux sinon</returns>
bool Ghost::init()
{
	if (!ghostT.loadFromFile("Sprites\\FreeArt\\Ghost.png"))
	{
		return false;
	}

	// Initialiser les rectangles d'animation
	for (int i = 0; i < 4; i++)
	{
		intRects[i].top = TILE_SIZE  * (i % MAX_ANIMATIONS_PER_LAYER);
		intRects[i].left = TILE_SIZE * (i % MAX_ANIMATIONS_PER_LAYER);
		intRects[i].width = TILE_SIZE;
		intRects[i].height = TILE_SIZE;
	}
	return true;
}

/// <summary>
/// Téléporter le fantôme à une position aléatoire
/// </summary>
void Ghost::randomTeleport()
{
	// Ce n'est pas grave s'il apparaît sur le joueur, car le joueur devient invincible si dégâts
	setPosition(rand() % MAP_SIZE * TILE_SIZE, MAP_SIZE * TILE_SIZE);
}