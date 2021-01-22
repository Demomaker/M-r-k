#pragma once
#include "Character.h"
#include "Enums.h"
#include "Weapon.h"
#include "Shield.h"
#include "IObserver.h"
#include "pch.h"
class Subject;
class SceneGame;
/// <summary>
/// Repr�sente le concept logique et graphique d'un joueur dans l'espace de jeu
/// </summary>
/// <seealso cref="Character" />
class Player : public Character, public IObserver
{
public:		
	/// <summary>
	/// Obtenir l'instance
	/// </summary>
	/// <returns>L'instance</returns>
	static Player *getInstance();
	
	/// <summary>
	/// Lib�rer la m�moire
	/// </summary>
	static void release();
	
	/// <summary>
	/// �tre notifi� selon un certain sujet.
	/// </summary>
	/// <param name="subject">Le sujet.</param>
	void notify(Subject * subject) override;

	/// <summary>
	/// Met � jour le joueur dans l'espace de jeu
	/// </summary>
	/// <param name="angle">Orientation du joueur</param>
	/// <param name="timeSpend">Temps �coul� � la derni�re frame</param>
	/// <param name="ammoText">Composant destin� � l'affichage du nombre de munition(s)</param>
	void update(const float& angle, const float& timeSpend, sf::Text& ammoText, SceneGame & scene);

	/// <summary>
	/// Met � jour les contr�les du joueur
	/// </summary>
	void getInputs();	
	
	/// <summary>
	/// Prendre des dommages selon une certaine couleur
	/// </summary>
	/// <param name="damage">Les dommages � prendre.</param>
	/// <param name="damagedByColor">La couleur.</param>
	/// <returns>Vrai si la partie est termin�e, faux sinon</returns>
	bool takeDamage(const float & damage, sf::Color damagedByColor = sf::Color::Yellow);

	/// <summary>
	/// Ajoute une �limination au score du joueur
	/// </summary>
	/// <returns>Nombre de points ajout�s</returns>
	int addAKill();	

	/// <summary>
	/// Obtient le score du joueur
	/// </summary>
	/// <returns>Le score du joueur</returns>
	int getScore() const;

	/// <summary>
	/// Obtient le nombre de vie restantes
	/// </summary>
	/// <returns>Le nombre de vie restantes</returns>
	int getRemainingLives() const;
	
	/// <summary>
	/// Obtenir la vie en ce moment
	/// </summary>
	/// <returns>La vie en ce moment</returns>
	int getCurrentHealth() const;
	
	/// <summary>
	/// Obtenir le shield en ce moment.
	/// </summary>
	/// <returns>Le shield en ce moment</returns>
	Shield * getCurrentShield() const;
	
	/// <summary>
	/// D�terminer si l'instance est invincible.
	/// </summary>
	/// <returns>
	///   <c>true</c> si l'instance est invincible; sinon, <c>false</c>.
	/// </returns>
	bool isInvincible() const;
		
	/// <summary>
	/// D�terminer si l'instance est morte.
	/// </summary>
	/// <returns>
	///   <c>true</c> si l'instance est morte; sinon, <c>false</c>.
	/// </returns>
	bool isDead() const;

	/// <summary>
	/// Obtient le nombre de munitions restantes
	/// </summary>
	/// <returns>Le nombre de munitions restantes</returns>
	int getCurrentAmmo() const;
	
	/// <summary>
	/// Change l'arme du joueur pour la suivante
	/// </summary>
	void setNextWeapon();
	
	/// <summary>
	/// Change l'arme du joueur pour la pr�c�dente
	/// </summary>
	void setPrevWeapon();

	/// <summary>
	/// Obtient le type de projectile utilis�
	/// </summary>
	/// <returns>Le type de projectile utilis�</returns>
	ProjectileType getCurrentProjectileType() const;	
	
	/// <summary>
	/// Prendre des dommages durant une dur�e pr�d�termin�e, � chaque x seconde, un nombre x de fois.
	/// </summary>
	/// <param name="damage">Les dommages � prendre.</param>
	/// <param name="timeInSeconds">Le temps en secondes.</param>
	/// <param name="numberOfTimes">Le nombre de fois.</param>
	void takeDamageEverySetTimeDuringSetDuration(float damage, float timeInSeconds, int numberOfTimes);
	
	/// <summary>
	/// Ralentir pendant un certain nombre de secondes
	/// </summary>
	/// <param name="timeInSeconds">Le temps en secondes.</param>
	void slowDown(float timeInSeconds);
	
	/// <summary>
	/// Initialiser selon le jeu sp�cifi�.
	/// </summary>
	/// <param name="game">Le jeu.</param>
	/// <returns>Vrai si succ�s, faux sinon</returns>
	bool init(SceneGame * game);
	
	/// <summary>
	/// Mettre � jour le hud du joueur.
	/// </summary>
	void UpdatePlayerHUD();
	
	/// <summary>
	/// Dessiner le hud du joueur selon la fen�tre de jeu
	/// </summary>
	/// <param name="mainWin">La fen�tre de jeu.</param>
	void drawPlayerHUD(sf::RenderWindow & mainWin);

private:
	//Ceci est dans tous les singletons
	Player();				       // constructeur priv�
	static Player *instance;        // pointeur statique vers le singleton

	Player(const Player&);       // d�clarer (sans les d�finir) les op�rations de
	void operator=(const Player&);  // copie en private, pour emp�cher leur utilisation
	
	/// <summary>
	/// La gage de vie
	/// </summary>
	sf::RectangleShape lifeGauge;	

	/// <summary>
	/// La gage de shield
	/// </summary>
	sf::RectangleShape shieldGauge;	

	/// <summary>
	/// The gage de fond
	/// </summary>
	sf::RectangleShape gaugeBackground;
	
	/// <summary>
	/// Le jeu
	/// </summary>
	SceneGame * game;
	
	/// <summary>
	/// Le sprite du shield
	/// </summary>
	sf::CircleShape shieldSprite;

	/// <summary>
	/// Enl�ve une vie au joueur
	/// </summary>
	/// <returns>Vrai lorsque le joueur n'a plus de vie, faux sinon</returns>
	bool die();

	/// <summary>
	/// Vitesse de d�placement
	/// </summary>
	const int MOVE_SPEED = 5;	

	/// <summary>
	/// D�lai de r�apparition
	/// </summary>
	const int REASPAWN_COUNTDOWN = 2;

	/// <summary>
	/// Dur�e de l'invincibilit�
	/// </summary>
	const int INVINCIBILITY_COUNTDOWN = 3;	

	/// <summary>
	/// Cadence de tir par d�faut
	/// </summary>
	const float BASE_FIRE_RATE = 1.0f / 6.0f;	

	/// <summary>
	/// Cadence de tir pour les projectiles de type "Scatter"
	/// </summary>
	const float SCATTER_FIRE_RATE = 1.0f / 3.0f;

	/// <summary>
	/// Cadence de tir pour les projectiles de type "Bomb"
	/// </summary>
	const float BOMB_FIRE_RATE = 1.0f;

	/// <summary>
	/// Cadence de tir pour les projectiles de type "Flame"
	/// </summary>
	const float FLAME_FIRE_RATE = 1.0f / 20.0f;

	/// <summary>
	/// Cadence de tir pour les projectiles de type "Missile"
	/// </summary>
	const float MISSILE_FIRE_RATE = 1.0f / 2.0f;

	/// <summary>
	/// Cadence de tir pour les projectiles de type "Laser"
	/// </summary>
	const float LASER_FIRE_RATE = 1.0f / 1.5f;

	/// <summary>
	/// Nombre de points pour acqu�rir une vie suppl�mentaire
	/// </summary>
	const int POINTS_TO_EARN_A_LIFE = 5000;	

	/// <summary>
	/// Score maximum par �limination
	/// </summary>
	const int MAX_POINTS_PER_KILL = 500;

	/// <summary>
	/// Score par �limination
	/// </summary>
	const int POINTS_PER_KILL = 100;	

	/// <summary>
	/// Score par s�rie d'�liminations
	/// </summary>
	const int POINTS_PER_KILL_STREAK = 10;	

	/// <summary>
	/// Temps maximum entre les s�rie d'�liminations
	/// </summary>
	const int MAX_TIME_BETWEEN_KILL_STREAK = 1;	

	/// <summary>
	/// Nombre de vies initial
	/// </summary>
	const int LIVES_AT_BEGINNING = 5;	

	/// <summary>
	/// Chronom�tre de r�apparition
	/// </summary>
	float respawnChronometer = 0;	

	/// <summary>
	/// Chronom�tre de dommages
	/// </summary>
	float damageChronometer = 0;
	
	/// <summary>
	/// Chronom�tre pour ralentir
	/// </summary>
	float slowDownChronometer = 0;

	/// <summary>
	/// Chronom�tre de s�rie d'�liminations
	/// </summary>
	float lastKillChronometer = 0;	

	/// <summary>
	/// S�rie d'�liminations en cours
	/// </summary>
	int currentKillStreak = 0;	

	/// <summary>
	/// �tat invincible du joueur
	/// </summary>
	bool invincible = false;

	/// <summary>
	/// �tat mort du joueur
	/// </summary>
	bool dead = false;	
	
	/// <summary>
	/// �tat �toile activ�e
	/// </summary>
	bool starActivated = false;

	/// <summary>
	/// Vies restantes
	/// </summary>
	int remainingLives = LIVES_AT_BEGINNING;

	/// <summary>
	/// Socre de la partie en cours
	/// </summary>
	int currentScore = 0;	

	/// <summary>
	/// Temps �coul� depuis le dernier tir du joueur
	/// </summary>
	float lastShot = 0;
	
	/// <summary>
	/// Le temps restant pour la multiplication du score
	/// </summary>
	float remainingScoreMultiplierTime = 0;
	
	/// <summary>
	/// Le temps restant pour l'�toile
	/// </summary>
	float remainingStarTime = 0;
	
	/// <summary>
	/// Le multiplicateur de cadence de feu
	/// </summary>
	float fireRateMultiplier = 1;
	
	/// <summary>
	/// Le multiplicateur de cadence de feu sur la bombe de gaz
	/// </summary>
	const float FIRERATE_MULTIPLIER_ON_GAS_BOMB = 1.5f;
	
	/// <summary>
	/// Le multiplicateur de score
	/// </summary>
	int scoreMultiplier = 1;
		
	/// <summary>
	/// Ajoute un shield.
	/// </summary>
	/// <param name="color">La couleur du shield.</param>
	void addShield(const sf::Color& color);

	/// <summary>
	/// Texture du joueur
	/// </summary>
	sf::Texture texture;
	
	/// <summary>
	/// Les rectangles d'entiers
	/// </summary>
	sf::IntRect* intRects;
	
	/// <summary>
	/// L'animation
	/// </summary>
	int animator = 0;
	
	/// <summary>
	/// Les armes
	/// </summary>
	CircularDoubleLinkedList<Weapon> * weapons;
	
	/// <summary>
	/// L'arme en cours
	/// </summary>
	Weapon * weapon;
	
	/// <summary>
	/// Les shields
	/// </summary>
	Stack<Shield> * shields;

	/// <summary>
	/// Fl�che de gauche enfonc�e
	/// </summary>
	bool left = false;

	/// <summary>
	/// Fl�che de droite enfonc�e
	/// </summary>
	bool right = false;

	/// <summary>
	/// Fl�che du haut enfonc�e
	/// </summary>
	bool up = false;

	/// <summary>
	/// Fl�che du bas enfonc�e
	/// </summary>
	bool down = false;

	/// <summary>
	/// Bouton gauche de la souris enfonc�
	/// </summary>
	bool fire = false;
	
	/// <summary>
	/// L'ammo qui reste
	/// </summary>
	int remainingAmmo[3];
	
	/// <summary>
	/// �tat de dommage
	/// </summary>
	bool takingDamage = false;
	
	/// <summary>
	/// Damage � prendre � chaque fois que le joueur prend des dommages en �tant empoisonn�
	/// </summary>
	float damageToTakeEverySetTime = 0;
	
	/// <summary>
	/// Temps avant que le joueur prenne du dommage en �tant empoisonn�
	/// </summary>
	float timeBeforeDamageIsTaken = 0;
	
	/// <summary>
	/// Le temps que le joueur est ralenti
	/// </summary>
	float timeSlownDown = 0;
	
	/// <summary>
	/// �tat ralenti du personnage
	/// </summary>
	bool slowedDown = false;
	
	/// <summary>
	/// Le nombre de fois que les dommages sont pris
	/// </summary>
	int numberOfTimesDamageIsTaken = 0;
	
	/// <summary>
	/// Le temps pour le multiplicateur de score
	/// </summary>
	const static int SCORE_MULTIPLIER_TIME = 10;
	
	/// <summary>
	/// Le temps pour l'�toile
	/// </summary>
	const static int STAR_TIME = 4;
};

