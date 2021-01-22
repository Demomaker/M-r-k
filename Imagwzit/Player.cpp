#include "Player.h"
#include "Projectile.h"
#include "ScoreIndicator.h"
#include "SceneGame.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Constants.h"
#include "ContainerFactory.h"
#include <algorithm>
#include "Subject.h"
#include "ScoreMultiplier.h"
#include "Star.h"
#include "AmmoBox.h"
#include "ShieldBonus.h"
#include "Bomb.h"
#include "GasBomb.h"

/// <summary>
/// Instance de la classe
/// </summary>
Player * Player::instance = nullptr;

/// <summary>
/// Obtenir l'instance
/// </summary>
/// <returns>L'instance</returns>
Player* Player::getInstance()
{
	if (!instance) 
	{
		instance = new Player();
		Subject::addObserver(instance);
	}
	return instance;
}

/// <summary>
/// Libérer la mémoire
/// </summary>
void Player::release()
{
	Subject::removeObserver(instance);
	delete[] instance->intRects;
	int nbWeapons = instance->weapons->getSize();
	for (int i = 0; i < nbWeapons; i++)
	{
		delete instance->weapons->remove_end();
	}
	delete instance->weapons;
	delete instance->weapon;
	int nbShields = instance->shields->getSize();
	for (int i = 0; i < nbShields; i++)
	{
		delete instance->shields->pop();
	}
	delete instance->shields;
	delete instance;
	instance = nullptr;
}

/// <summary>
/// Être notifié selon un certain sujet.
/// </summary>
/// <param name="subject">Le sujet.</param>
void Player::notify(Subject * subject)
{
	if (typeid(*subject) == typeid(PowerUp::ScoreMultiplier))
	{
		scoreMultiplier++;
		remainingScoreMultiplierTime = SCORE_MULTIPLIER_TIME;
		setColor(Color::Blue);
	}
	else if (typeid(*subject) == typeid(PowerUp::Star))
	{
		starActivated = true;
		remainingStarTime = STAR_TIME;
		invincible = true;
		timeSlownDown = 0;
		slowedDown = false;
		setColor(Color(240, 255, 0, 255));
	}
	else if (typeid(*subject) == typeid(PowerUp::AmmoBox))
	{
		//Casting de notre sujet dans son bon type... vive le polymorphisme
		PowerUp::AmmoBox * ammoBox = static_cast<PowerUp::AmmoBox*>(subject);
		ProjectileType currentProjectile = getCurrentProjectileType();
		switch (ammoBox->getAmmoBoxType())
		{
		case FlameAmmoBoxType:
			for (int i = 0; i < weapons->getSize() && getCurrentProjectileType() != Flame; i++) 
			{
				setNextWeapon();
			}
			if (getCurrentProjectileType() == Flame) 
			{
				weapon->addAmmo(NB_FLAME_AMMO);
			}
			else
			{
				// Ajout de l'arme si le joueur ne l'a pas déjà
				weapons->add_start(new Weapon(FLAME_FIRE_RATE, NB_FLAME_AMMO, Flame));
			}
			break;
		case ScatterAmmoBoxType:
			for (int i = 0; i < weapons->getSize() && getCurrentProjectileType() != Scatter; i++)
			{
				setNextWeapon();
			}
			if (getCurrentProjectileType() == Scatter)
			{
				weapon->addAmmo(NB_SCATTER_AMMO);
			}
			else
			{
				// Ajout de l'arme si le joueur ne l'a pas déjà
				weapons->add_start(new Weapon(SCATTER_FIRE_RATE, NB_SCATTER_AMMO, Scatter));
			}
			break;
		case MissileAmmoBoxType:
			for (int i = 0; i < weapons->getSize() && getCurrentProjectileType() != Missile; i++)
			{
				setNextWeapon();
			}
			if (getCurrentProjectileType() == Missile)
			{
				weapon->addAmmo(NB_MISSILE_AMMO);
			}
			else
			{
				// Ajout de l'arme si le joueur ne l'a pas déjà
				weapons->add_start(new Weapon(MISSILE_FIRE_RATE, NB_MISSILE_AMMO, Missile));
			}
			break;
		case RocketLauncherAmmoBoxType:
			for (int i = 0; i < weapons->getSize() && getCurrentProjectileType() != Bomb; i++)
			{
				setNextWeapon();
			}
			if (getCurrentProjectileType() == Bomb)
			{
				weapon->addAmmo(NB_BOMB_AMMO);
			}
			else
			{
				// Ajout de l'arme si le joueur ne l'a pas déjà
				weapons->add_start(new Weapon(BOMB_FIRE_RATE, NB_BOMB_AMMO, Bomb));
			}
			break;
		case LaserAmmoBoxType:
			for (int i = 0; i < weapons->getSize() && getCurrentProjectileType() != Laser; i++)
			{
				setNextWeapon();
			}
			if (getCurrentProjectileType() == Laser)
			{
				weapon->addAmmo(NB_LASER_AMMO);
			}
			else
			{
				// Ajout de l'arme si le joueur ne l'a pas déjà
				weapons->add_start(new Weapon(LASER_FIRE_RATE, NB_LASER_AMMO, Laser));
			}
			break;
		}
		// On remet l'arme que le joueur avait entre ses mains
		while (getCurrentProjectileType() != currentProjectile)
		{
			setNextWeapon();
		}
	}
	else if (typeid(*subject) == typeid(PowerUp::Shield))
	{
		//Casting de notre sujet dans son bon type... vive le polymorphisme
		PowerUp::Shield * shield = static_cast<PowerUp::Shield*>(subject);
		switch (shield->getShieldType()) 
		{
		case RedShieldType:
			addShield(Color::Red);
			break;
		case BlueShieldType:
			addShield(Color::Blue);
			break;
		case GreenShieldType:
			addShield(Color::Green);
			break;
		}
	}
	else if (typeid(*subject) == typeid(PowerUp::Bomb))
	{
		//Casting de notre sujet dans son bon type... vive le polymorphisme
		PowerUp::Bomb * bomb = static_cast<PowerUp::Bomb*>(subject);
		if (getCurrentShield() != nullptr) 
		{
			switch (bomb->getBombType())
			{
			case BlueBombType:
				if(getCurrentShield()->getColor() == Color::Blue) return;
				break;
			case RedBombType:
				if (getCurrentShield()->getColor() == Color::Red) return;
				break;
			case GreenBombType:
				if (getCurrentShield()->getColor() == Color::Green) return;
				break;
			}
		}
		int diffY = bomb->getPosition().y - getPosition().y;
		int diffX = bomb->getPosition().x - getPosition().x;
		int distance = sqrt((diffY * diffY) + (diffX * diffX));
		// On prend des dégâts en fonction de la distance
		takeDamage(std::max((300 - distance) / 40, 0));
	}
	else if (typeid(*subject) == typeid(PowerUp::GasBomb))
	{
		PowerUp::GasBomb * gasBomb = static_cast<PowerUp::GasBomb*>(subject);
		if (!gasBomb->isPickedByPlayer())
		{
			// Bombe ramassée par un ennemi
			slowDown(GAS_BOMB_DURATION);
			fireRateMultiplier = FIRERATE_MULTIPLIER_ON_GAS_BOMB;
		}
	}
}

/// <summary>
/// Constructeur d'un joueur
/// </summary>
Player::Player() : Character(10)
{
	weapons = ContainerFactory<Weapon>::getCircularDoubleLinkedList();
	shields = ContainerFactory<Shield>::getStack();
	weapon = new Weapon(BASE_FIRE_RATE, 999, Bullet);
	setActive(true);
	speed = MOVE_SPEED;
}

/// <summary>
/// Initialiser selon le jeu spécifié.
/// </summary>
/// <param name="game">Le jeu.</param>
/// <returns>Vrai si succès, faux sinon</returns>
bool Player::init(SceneGame * game)
{
	if (!texture.loadFromFile("Sprites\\FreeArt\\character.png"))
	{
		return false;
	}

	this->game = game;

	texture.setSmooth(true);
	setTexture(texture, true);

	intRects = new IntRect[4];

	for (int i = 0; i < 4; i++)
	{
		intRects[i].left = TILE_SIZE * i;
		intRects[i].top = 0;
		intRects[i].width = TILE_SIZE;
		intRects[i].height = TILE_SIZE;
	}

	setTextureRect(intRects[0]);
	setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);

	shieldSprite.setOrigin(getOrigin());
	shieldSprite.setRadius(getLocalBounds().width / 2);

	lifeGauge.setSize(sf::Vector2f(64, 5));
	lifeGauge.setFillColor(Color(76, 255, 76));
	lifeGauge.setOrigin(lifeGauge.getSize() * 0.5f);
	lifeGauge.setPosition(10, 10);


	shieldGauge.setSize(sf::Vector2f(64, 5));
	shieldGauge.setFillColor(Color(76, 76, 255));
	shieldGauge.setOrigin(shieldGauge.getSize() * 0.5f);
	shieldGauge.setPosition(10, 16);

	gaugeBackground.setSize(sf::Vector2f(66, 13));
	gaugeBackground.setFillColor(Color::White);
	gaugeBackground.setOrigin(gaugeBackground.getSize() * 0.5f);
	gaugeBackground.setPosition(9, 9);

	UpdatePlayerHUD();

	return true;
}

/// <summary>
/// Mettre à jour le hud du joueur.
/// </summary>
void Player::UpdatePlayerHUD()
{
	if (getCurrentShield() != nullptr)
	{
		shieldGauge.setFillColor(getCurrentShield()->getColor());
		shieldGauge.setSize(Vector2f(getCurrentShield()->getCurrentResistance() / (float)getCurrentShield()->MAX_RESISTANCE * 64, shieldGauge.getSize().y));
		// On met à jour la couleur du bouclier en ajoutant de la transparance
		shieldSprite.setFillColor(getCurrentShield()->getColor() - Color(0, 0, 0, 200));
	}
	else
	{
		lifeGauge.setSize(Vector2f(Player::getInstance()->getCurrentHealth() / (float)MAX_HEALTH * 64, lifeGauge.getSize().y));
		shieldGauge.setSize(Vector2f(0, shieldGauge.getSize().y));
	}
}

/// <summary>
/// Dessiner le hud du joueur selon la fenêtre de jeu
/// </summary>
/// <param name="mainWin">La fenêtre de jeu.</param>
void Player::drawPlayerHUD(RenderWindow & mainWin)
{
	if (Player::getInstance()->isActive())
	{
		if (getCurrentShield() != nullptr)
		{
			shieldSprite.setPosition(getPosition());
			mainWin.draw(shieldSprite);
		}
		lifeGauge.setPosition(getPosition().x, getPosition().y - 50);
		shieldGauge.setPosition(getPosition().x, lifeGauge.getPosition().y + 6.0f);
		gaugeBackground.setPosition(getPosition().x, lifeGauge.getPosition().y + 3.0f);
		mainWin.draw(gaugeBackground);
		mainWin.draw(lifeGauge);
		mainWin.draw(shieldGauge);
	}
}

/// <summary>
/// Met à jour le joueur dans l'espace de jeu
/// </summary>
/// <param name="angle">Orientation du joueur</param>
/// <param name="timeSpend">Temps écoulé à la dernière frame</param>
/// <param name="ammoText">Composant destiné à l'affichage du nombre de munition(s)</param>
void Player::update(const float& angle, const float& timeSpend, sf::Text& ammoText, SceneGame & scene)
{
	lastKillChronometer += timeSpend / FRAMES_PER_SECOND;

	if (remainingScoreMultiplierTime > 0)
	{
		remainingScoreMultiplierTime -= timeSpend / FRAMES_PER_SECOND;
		if (remainingScoreMultiplierTime <= 0)
		{
			// Remettre le multiplicateur à 1
			scoreMultiplier = 1;
			setColor(Color(255, 255, 255, 255));
		}
	}

	if (dead)
	{
		// Le joueur est mort
		respawnChronometer -= timeSpend / FRAMES_PER_SECOND;
		if (respawnChronometer < 0)
		{
			// La mort du joueur prend fin
			dead = false;
			invincible = true;
			setColor(sf::Color(255, 255, 255, 125));
			respawnChronometer = INVINCIBILITY_COUNTDOWN;
			health = MAX_HEALTH;
			UpdatePlayerHUD();
			setActive(true);
		}
	}
	else if (starActivated)
	{
		// Le joueur est en mode étoile
		remainingStarTime -= timeSpend / FRAMES_PER_SECOND;
		if (remainingStarTime < 0)
		{
			starActivated = false;
			// L'invicibilité prend fin
			invincible = false;
			setColor(sf::Color(255, 255, 255, 255));
		}
	}
	else if (invincible)
	{
		// Le joueur est invincible
		respawnChronometer -= timeSpend / FRAMES_PER_SECOND;
		if (respawnChronometer < 0)
		{
			// L'invicibilité prend fin
			invincible = false;
			setColor(sf::Color(255, 255, 255, 255));
		}
	} 

	Projectile * proj = Projectile::checkCollisionWith(*this);
	// Gérer les collisions entre le joueur et les projectiles
	if (proj != nullptr)
	{
		if (proj->getType() == ProjectileType::SpiderWeb)
		{
			// Le joueur a été touché par une toile d'arraignée
			takeDamageEverySetTimeDuringSetDuration(0.5, 1, 3);
			slowDown(2);
			proj->setActive(false);
		}
		if (proj->getType() == ProjectileType::Bullet)
		{
			// Le joueur a été touché par une balle ennemie
			takeDamage(1);
			proj->setActive(false);
		}
	}

	if (!isActive())
		return;

	if (slowedDown)
	{
		// Le joueur est au ralenti
		slowDownChronometer += timeSpend / FRAMES_PER_SECOND;
		if (slowDownChronometer >= timeSlownDown)
		{
			// Le ralentissement prend fin
			slowDownChronometer = 0;
			slowedDown = false;
			speed = MOVE_SPEED;
			fireRateMultiplier = 1;
		}
		else 
		{
			speed = MOVE_SPEED / 2;
		}
	}
	if (takingDamage && !invincible)
	{
		damageChronometer += timeSpend / FRAMES_PER_SECOND;
		if (damageChronometer >= timeBeforeDamageIsTaken && numberOfTimesDamageIsTaken > 0)
		{
			// Le joueur prend des dégâts
			numberOfTimesDamageIsTaken--;
			takeDamage(damageToTakeEverySetTime);
			damageChronometer = 0;
		}
		else if (numberOfTimesDamageIsTaken <= 0)
		{
			// Le joueur ne prend plus de dégât
			takingDamage = false;
			damageChronometer = 0;
		}
	}

	this->weaponAngle = angle;
	(abs(angle) > M_PI / 2 && abs(angle) < 3 * M_PI / 2 ? setScale(-1, 1) : setScale(1, 1));

	// Si le joueur peut tirer et qu'il tire
	if (fire && weapon->FIRE_RATE * fireRateMultiplier <= lastShot && weapon->getCurrentAmmo() > 0)
	{
		// On fait apparaître un projectile
		Projectile::spawnAProjectile(weaponAngle, *this, true);
		lastShot = 0;
		if (weapon->PROJECTILE_TYPE != ProjectileType::Bullet)
		{
			weapon->addAmmo(-1);
			if (weapon->getCurrentAmmo() <= 0) 
			{
				// On détruit l'arme si plus de munition
				delete weapon;
				weapon = weapons->remove_start();
			}
				
			ammoText.setString(std::to_string(weapon->getCurrentAmmo()));
		}
	}

	lastShot += timeSpend / FRAMES_PER_SECOND;


	// Déplacer le joueur
	float moveX = 0.0f;
	float moveY = 0.0f;

	if (left) moveX -= 1.0f;
	if (right) moveX += 1.0f;
	if (up) moveY -= 1.0f;
	if (down) moveY += 1.0f;

	float newSpeed = speed;

	// Pour mettre à jour la vitesse si déplacement en diagonale
	if (moveX != 0.0f && moveY != 0.0f)
		newSpeed /= std::sqrt(2.0f);

	movement = Vector2f(moveX * newSpeed * timeSpend, moveY * newSpeed * timeSpend);
	scene.isWalkableArea(movement, getPosition());

	//Changement de frame aux 10 frames
	setTextureRect(intRects[(animator++ / 5) % 4]);

	Character::update();
}

/// <summary>
/// Met à jour les contrôles du joueur
/// </summary>
void Player::getInputs()
{
	up = Keyboard::isKeyPressed(Keyboard::W);
	down = Keyboard::isKeyPressed(Keyboard::S);
	left = Keyboard::isKeyPressed(Keyboard::A);
	right = Keyboard::isKeyPressed(Keyboard::D);
	fire = Mouse::isButtonPressed(Mouse::Left);
}

/// <summary>
/// Enlève une vie au joueur
/// </summary>
/// <returns>Vrai lorsque le joueur n'a plus de vie, faux sinon</returns>
bool Player::die()
{
	if (isActive())
	{
		// Le joueur meurt s'il est en vie
		respawnChronometer = REASPAWN_COUNTDOWN;
		dead = true;
		setActive(false);
		remainingLives--;
	}
	return remainingLives <= 0;
}

/// <summary>
/// Ajoute un shield.
/// </summary>
/// <param name="color">La couleur du shield.</param>
void Player::addShield(const sf::Color& color)
{
	Shield * current = getCurrentShield();
	int resistance = rand() % 3 + 1;
	if (current != nullptr && current->getColor() == color)
	{
		// Le joueur a déjà un bouclier de cette couleur
		int remainingResistanceToAdd = current->addResistance(resistance);
		// On en ajoute un nouveau si déjà plein
		if (remainingResistanceToAdd > 0)
			shields->push(new  Shield(remainingResistanceToAdd, color));
	}
	else
	{
		// Nouveau bouclier
		shields->push(new Shield(resistance, color));
	}
	UpdatePlayerHUD();
}

/// <summary>
/// Prendre des dommages selon une certaine couleur
/// </summary>
/// <param name="damage">Les dommages à prendre.</param>
/// <param name="damagedByColor">La couleur.</param>
/// <returns>Vrai si la partie est terminée, faux sinon</returns>
bool Player::takeDamage(const float & damage, sf::Color damagedByColor)
{
	if (isInvincible() || damage <= 0)
		return false;

		if (shields->getSize() > 0)
		{
			if (shields->top()->getColor() == damagedByColor) 
			{
				// Pas de dégâts si le bouclier absorbe les dégâts
				return false;
			}
			int resistance = shields->top()->takeDamage(damage);
			if (resistance <= 0)
			{
				delete shields->pop();
				// On lui fait prendre les dommages restants
				takeDamage(resistance);
			}
		}
		else
		{
			Destructible::addHealth(-damage);
			if (health <= 0)
			{
				UpdatePlayerHUD();
				if (die())
				{
					// Fin de la partie si le joueur n'a plus de vie
					game->endGame();
					return true;
				}
			}
		}
		invincible = true;
		setColor(sf::Color(255, 255, 255, 125));
		respawnChronometer = INVINCIBILITY_COUNTDOWN;
		UpdatePlayerHUD();
		return false;
}

/// <summary>
/// Ajoute une élimination au score du joueur
/// </summary>
/// <returns>Nombre de points ajoutés</returns>
int Player::addAKill()
{
	// On met à jour la série d'éliminations
	currentKillStreak += (lastKillChronometer <= MAX_TIME_BETWEEN_KILL_STREAK) ? 1 : -currentKillStreak;

	int scoreToAdd = std::min(MAX_POINTS_PER_KILL, (POINTS_PER_KILL + POINTS_PER_KILL_STREAK * currentKillStreak));
	scoreToAdd *= remainingScoreMultiplierTime > 0 ? scoreMultiplier : 1;

	currentScore += scoreToAdd;

	// On ajoute une vie au joueur si son score le permet
	if (currentScore % POINTS_TO_EARN_A_LIFE < scoreToAdd)
		remainingLives++;

	lastKillChronometer = 0;

	return scoreToAdd;
}

/// <summary>
/// Obtient le score du joueur
/// </summary>
/// <returns>Le score du joueur</returns>
int Player::getScore() const
{
	return currentScore;
}

/// <summary>
/// Obtient le nombre de vie restantes
/// </summary>
/// <returns>Le nombre de vie restantes</returns>
int Player::getRemainingLives() const
{
	return remainingLives;
}

/// <summary>
/// Obtenir la vie en ce moment
/// </summary>
/// <returns>La vie en ce moment</returns>
int Player::getCurrentHealth() const
{
	return health;
}

/// <summary>
/// Obtenir le shield en ce moment.
/// </summary>
/// <returns>Le shield en ce moment</returns>
Shield * Player::getCurrentShield() const
{
	return shields->getSize() > 0 ? shields->top() : nullptr;
}

/// <summary>
/// Déterminer si l'instance est invincible.
/// </summary>
/// <returns>
///   <c>true</c> si l'instance est invincible; sinon, <c>false</c>.
/// </returns>
bool Player::isInvincible() const
{
	return invincible;
}

/// <summary>
/// Déterminer si l'instance est morte.
/// </summary>
/// <returns>
///   <c>true</c> si l'instance est morte; sinon, <c>false</c>.
/// </returns>
bool Player::isDead() const
{
	return dead;
}

/// <summary>
/// Obtient le nombre de munitions restantes
/// </summary>
/// <returns>Le nombre de munitions restantes</returns>
int Player::getCurrentAmmo() const
{
	return weapon->getCurrentAmmo();
}

/// <summary>
/// Change l'arme du joueur pour la suivante
/// </summary>
void Player::setNextWeapon()
{
	weapons->add_end(weapon);
	weapon = weapons->remove_start();
}

/// <summary>
/// Change l'arme du joueur pour la précédente
/// </summary>
void Player::setPrevWeapon()
{
	weapons->add_start(weapon);
	weapon = weapons->remove_end();
}

/// <summary>
/// Obtient le type de projectile utilisé
/// </summary>
/// <returns>Le type de projectile utilisé</returns>
ProjectileType Player::getCurrentProjectileType() const
{
	return weapon->PROJECTILE_TYPE;
}

/// <summary>
/// Prendre des dommages durant une durée prédéterminée, à chaque x seconde, un nombre x de fois.
/// </summary>
/// <param name="damage">Les dommages à prendre.</param>
/// <param name="timeInSeconds">Le temps en secondes.</param>
/// <param name="numberOfTimes">Le nombre de fois.</param>
void Player::takeDamageEverySetTimeDuringSetDuration(float damage, float timeInSeconds, int numberOfTimes)
{
	if (!takingDamage)
	{
		takingDamage = true;
		damageToTakeEverySetTime = damage;
		timeBeforeDamageIsTaken = timeInSeconds;
		numberOfTimesDamageIsTaken = numberOfTimes;
	}
}

/// <summary>
/// Ralentir pendant un certain nombre de secondes
/// </summary>
/// <param name="timeInSeconds">Le temps en secondes.</param>
void Player::slowDown(float timeInSeconds)
{
	if (isInvincible())
		return;

	slowedDown = true;
	timeSlownDown = timeInSeconds;
	slowDownChronometer = 0;
}