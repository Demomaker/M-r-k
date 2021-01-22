#include "SceneGame.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <iostream>
#include "ScoreIndicator.h"
#include "Explosion.h"
#include "Zombie.h"
#include "Ghost.h"
#include "Spider.h"
#include "Skeleton.h"
#include "Projectile.h"
#include "Bomberman.h"
#include "Enemy.h"
#include "Constants.h"
#include "Room.h"
#include "Manip.h"
#include "Recorder.h"

/// <summary>
/// Constructeur de SceneGame
/// </summary>
SceneGame::SceneGame()
{
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner
	view = View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(WORLD_WIDTH / 2, WORLD_HEIGHT / 2);
	HUD = View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	pause = false;
	pauseKeyPressed = false; 
	timer.restart();
}

/// <summary>
/// Destructeur de SceneGame
/// </summary>
SceneGame::~SceneGame()
{
	// On libère la mémoire
	IntMap::release();
	for (auto instance : spawnerInstances)
	{
		delete instance;
	}
	spawnerInstances.clear();

	for (auto instance : destructableWallInstances)
	{
		delete instance;
	}
	destructableWallInstances.clear();
	delete[] intRectsTiles;
	Player::release();
	PowerUp::Bonus::release();
	Enemy::release();
}

/// <summary>
///  Détermine si le cheat a été activé
/// </summary>
/// <return>Vrai si cheat activé</return>
bool SceneGame::checkCheat()
{
	Queue<Manip>* manips = recorder.getManips();
	int size = manips->getSize();

	//Si on a pas trois moves, c'est terminé, on a besoin ici de trois manips.
	if (size < 6)
	{
		return false;
	}

	Manip* m1 = (*manips)[size - 1];
	Manip* m2 = (*manips)[size - 2];
	Manip* m3 = (*manips)[size - 3];
	Manip* m4 = (*manips)[size - 4];
	Manip* m5 = (*manips)[size - 5];
	Manip* m6 = (*manips)[size - 6];

	return (m6->move == LetterPressed::T && m5->move == LetterPressed::O && m4->move == LetterPressed::T && m3->move == LetterPressed::O && m2->move == LetterPressed::T && m1->move == LetterPressed::E);
}

/// <summary>
/// Boucle principale de la scène
/// </summary>
/// <return>Prochaine scène à charger</return>
SceneType SceneGame::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	// On remet la vue par défaut
	mainWin->setView(mainWin->getDefaultView()); 
	currentPlayerScore = Player::getInstance()->getScore();
	return nextScene;
}

/// <summary>
/// Génère un corridor horizontal
/// </summary>
/// <param name="x1">Position en X de l'extrémité gauche</param>
/// <param name="x2">Position en Y de l'extrémité droite</param>
/// <param name="y">Position en Y</param>
void SceneGame::hCorridor(int x1, int x2, int y) 
{
	for (int x = std::min(x1, x2); x < std::max(x1, x2) + 1; x++)
	{
		IntMap::getInstance()->setElement(x,y,0);
	}
}

/// <summary>
/// Génère un corridor vertical
/// </summary>
/// <param name="x1">Position en Y du haut</param>
/// <param name="x2">Position en Y du bas</param>
/// <param name="y">Position en X</param>
void SceneGame::vCorridor(int y1, int y2, int x) 
{
	for (int y = std::min(y1, y2); y < std::max(y1, y2) + 1; y++)
	{
		IntMap::getInstance()->setElement(x, y, 0);
	}
}

/// <summary>
/// Génère les pièces du niveau
/// </summary>
void SceneGame::placeRooms() 
{
	// Liste des pièces
	std::list<Room> rooms;

	// Nombre de pièces aléatoires
	const int NB_ROOMS = rand() % MAX_NB_ROOMS + MIN_NB_ROOMS;

	int nbBadAttempts = 0;
	for (int i = 0; i < NB_ROOMS; i++) 
	{
		int w = rand() % MAX_ROOM_SIZE + MIN_ROOM_SIZE;
		int h = rand() % MAX_ROOM_SIZE + MIN_ROOM_SIZE;
		int x = rand() % (MAP_SIZE - 1 - w) + 1;
		int y = rand() % (MAP_SIZE - 1 - h) + 1;

		// On crée un nouvelle pièce avec des valeurs aléatoires
		Room newRoom = Room(x, y, w, h);

		bool failed = false;

		for (auto room : rooms) 
		{
			// On vérifie si elle entre en collision avec une autre pièce
			if (newRoom.intersects(room)) 
			{
				failed = true;
				break;
			}
		}
		// Si son emplacement est valdie
		if (!failed)
		{
			Vector2i newCenter = newRoom.getCenter();

			if (rooms.size() != 0)
			{
				// Lier la pièce avec la précédente
				Vector2i prevCenter = rooms.back().getCenter();

				if (rand() % 2 == 1)
				{
					hCorridor(prevCenter.x, newCenter.x, prevCenter.y);
					vCorridor(prevCenter.y, newCenter.y, newCenter.x);
				}
				else
				{
					vCorridor(prevCenter.y, newCenter.y, prevCenter.x);
					hCorridor(prevCenter.x, newCenter.x, newCenter.y);
				}
			}
			// On ajoute la pièce à la liste de pièce
			rooms.push_back(newRoom);
		}
		else if (nbBadAttempts < MAX_NB_ATTEMPTS_TO_CREATE_ROOM)
			// Sinon on essai de créer la pièce à nouveau
		{
			nbBadAttempts++;
			i--;
		}
		else {
			nbBadAttempts = 0;
		}
	}
	float distance = 0;
	for (auto it = rooms.begin(); it != rooms.end(); ++it)
	{
		// Pour chaque pièce
		double newDistance = sqrt(pow((*it).getCenter().x - (*rooms.begin()).getCenter().x, 2) + pow((*it).getCenter().y - (*rooms.begin()).getCenter().y, 2));
		if (newDistance > distance) 
		{
			// Placer la sortie dans la pièce la plus éloignée du joueur
			distance = newDistance;
			exitSprite.setPosition((*it).getCenter().x * TILE_SIZE, (*it).getCenter().y * TILE_SIZE);

		}
		bool spawnerSpawned = false;
		bool dontGoHere = it == rooms.begin();
		int numWallsSpawned = 0;
		for (int x = (*it).getPosition().x; x < ((*it).getPosition().x + (*it).getWidth()); x++)
		{
			for (int y = (*it).getPosition().y; y < ((*it).getPosition().y + (*it).getHeight()); y++)
			{
				IntMap::getInstance()->setElement(x, y, 0);
				int spawnerChance = rand() % 100;
				int wallChance = rand() % 100;
				int enemyChance = rand() % 100;
				if (it == rooms.begin() && x == (*it).getPosition().x + 1 && y == (*it).getPosition().y + 1)
				{
					// On fait aparraître le joueur dans la première pièce
					Player::getInstance()->setPosition(x * TILE_SIZE, y * TILE_SIZE);
					spawnerSpawned = true;
					continue;
				}
				if (!spawnerSpawned && spawnerChance < 3 + level && spawnerInstances.size() < MAX_NB_SPAWNERS) 
				{
					// Gérer l'apparition des spawner
					Spawner * spawner = new Spawner();
					spawner->setPosition(x * TILE_SIZE, y * TILE_SIZE);
					spawner->setActive(true);
					spawnerInstances.push_back(spawner);
					spawnerSpawned = true;
					continue;
				}
				if (!numWallsSpawned < MAX_NB_DESTRUCTABLE_WALLS && wallChance < 3 ) 
				{
					// Gérer l'apparition des murs destructibles
					DestructableWall * destructableWall = new DestructableWall();
					destructableWall->setPosition(x * TILE_SIZE, y * TILE_SIZE);
					destructableWall->setActive(true);
					destructableWall->setPositionDependingOnMap(Vector2f(x,y));
					destructableWallInstances.push_back(destructableWall);
					numWallsSpawned++; 
					IntMap::getInstance()->setElement(x, y, 2);
				}
				if (!dontGoHere && enemyChance < 2 + level)
				{
					Vector2f position(x * TILE_SIZE, y * TILE_SIZE);
					int randEnemy = rand() % 5;
					if (randEnemy == 0)
						Enemy::spawnABomberman(position);
					if (randEnemy == 1)
						Enemy::spawnAGhost(position);
					if (randEnemy == 2)
						Enemy::spawnASkeleton(position);
					if (randEnemy == 3)
						Enemy::spawnASpider(position);
					if (randEnemy == 4)
						Enemy::spawnAZombie(position);
				}
			}
		}
	}
}

/// <summary>
/// Déterminer si l'endroit est marchable
/// </summary>
/// <param name="movement">Le mouvement à effectuer (Modifié dans la méthode si invalide)</param>
/// <param name="position">La position initial de l'objet.</param>
/// <returns>0 (faux) si ce n'est pas marchable, 1 (true) si c'est marchable, 2 (true) si c'est un mur destructible, dans ce cas, faire les traitements nécessaires</returns>
int SceneGame::isWalkableArea(sf::Vector2f & movement, const sf::Vector2f & position) const
{
	bool retval = true;
	const int WIDTH = 0;
	Vector2i tilePosition = Vector2i(position.x / TILE_SIZE, position.y / TILE_SIZE);
	if ((position.x + movement.x) / TILE_SIZE < 0 || (position.x + movement.x) / TILE_SIZE > MAP_SIZE - 1)
	{
		// Movement en X invalide
		retval = false;
		movement.x = 0;
	}
	if ((position.y + movement.y) / TILE_SIZE < 0 || (position.y + movement.y) / TILE_SIZE > MAP_SIZE - 1)
	{
		// Movement en Y invalide
		retval = false;
		movement.y = 0;
	}

	// Obtenir les éléments en foncton du movement
	int elementXPlusMovementYPlus = IntMap::getInstance()->getElement((int)((position.x + WIDTH) / TILE_SIZE), (int)((position.y + movement.y + WIDTH) / TILE_SIZE));
	int elementXMinusMovementYPlus = IntMap::getInstance()->getElement((int)((position.x + WIDTH) / TILE_SIZE), (int)((position.y + movement.y - WIDTH) / TILE_SIZE));
	int elementXPlusMovementYMinus = IntMap::getInstance()->getElement((int)((position.x - WIDTH) / TILE_SIZE), (int)((position.y + movement.y + WIDTH) / TILE_SIZE));
	int elementXMinusMovementYMinus = IntMap::getInstance()->getElement((int)((position.x - WIDTH) / TILE_SIZE), (int)((position.y + movement.y - WIDTH) / TILE_SIZE));
	int elementMovementXPlusYPlus = IntMap::getInstance()->getElement((int)((position.x + movement.x + WIDTH) / TILE_SIZE), (int)((position.y + WIDTH) / TILE_SIZE));
	int elementMovementXMinusYPlus = IntMap::getInstance()->getElement((int)((position.x + movement.x - WIDTH) / TILE_SIZE), (int)((position.y + WIDTH) / TILE_SIZE));
	int elementMovementXPlusYMinus = IntMap::getInstance()->getElement((int)((position.x + movement.x + WIDTH) / TILE_SIZE), (int)((position.y - WIDTH) / TILE_SIZE));
	int elementMovementXMinusYMinus = IntMap::getInstance()->getElement((int)((position.x + movement.x - WIDTH) / TILE_SIZE), (int)((position.y - WIDTH) / TILE_SIZE));

	if ( elementXPlusMovementYPlus == 1 || elementXMinusMovementYPlus == 1 || elementXPlusMovementYMinus == 1 || elementXMinusMovementYMinus == 1)
	{
		// Movement en Y invalide
		retval = false;
		movement.y = 0;
	}
	
	if (elementXPlusMovementYPlus == 2 || elementXMinusMovementYPlus == 2 || elementXPlusMovementYMinus == 2 || elementXMinusMovementYMinus == 2)
	{
		// Movement en Y invalide
		retval = 2;
		movement.y = 0;
	}

	if ( elementMovementXPlusYPlus == 1 || elementMovementXMinusYPlus == 1 ||  elementMovementXPlusYMinus == 1 || elementMovementXMinusYMinus == 1)
	{
		// Movement en X invalide
		retval = false;
		movement.x = 0;
	}

	if (elementMovementXPlusYPlus == 2 || elementMovementXMinusYPlus == 2 || elementMovementXPlusYMinus == 2 || elementMovementXMinusYMinus == 2)
	{
		// Movement en X invalide
		retval = 2;
		movement.x = 0;
	}

	return retval;
}

/// <summary>
/// Charger le prochain niveau
/// </summary>
void SceneGame::loadNextLevel()
{
	IntMap::getInstance()->reset();
	for (auto instance : spawnerInstances)
	{
		delete instance;
	}
	spawnerInstances.clear();

	for (auto instance : destructableWallInstances)
	{
		delete instance;
	}
	level++;
	destructableWallInstances.clear();
	GameObject::disableAllActiveGameObjects();
	// S'assurer de désactiver les explosions
	Explosion::disableAllActiveInstances();
	placeRooms();
	Player::getInstance()->setActive(true);
}

/// <summary>
/// Initialise la scène
/// </summary>
/// <param name="window">Fenêtre de jeu</param>
/// <return>Succès ou non de l'initialisation</return>
bool SceneGame::init(RenderWindow * const window)
{
	srand(time(NULL));

	if (!tilesetT.loadFromFile("Sprites\\FreeArt\\Tiles.png"))
	{
		return false;
	}

	if (!heartT.loadFromFile("Sprites\\FreeArt\\Heart.png")) 
	{
		return false;
	}

	if (!mainFont.loadFromFile("Fonts\\segoepr.ttf"))
	{
		return false;
	}

	if (!music.openFromFile("Sounds\\demomakerthemusette.ogg"))
	{
		return false;
	}

	if (!Player::getInstance()->init(this) || !Enemy::init() || !Projectile::init() || !PowerUp::Bonus::init() 
		|| !Spawner::loadTexture() || !DestructableWall::loadTexture()) {
		return false;
	}

	if (!logosT[0].loadFromFile("Sprites\\Logos\\BulletLogo.png"))
	{
		return false;
	}

	if (!logosT[1].loadFromFile("Sprites\\Logos\\FlameLogo.png"))
	{
		return false;
	}

	if (!logosT[2].loadFromFile("Sprites\\Logos\\MissileLogo.png"))
	{
		return false;
	}

	if (!logosT[3].loadFromFile("Sprites\\Logos\\ScatterLogo.png"))
	{
		return false;
	}

	if (!logosT[4].loadFromFile("Sprites\\Logos\\RocketLauncherLogo.png"))
	{
		return false;
	}

	if (!logosT[5].loadFromFile("Sprites\\Logos\\LaserLogo.png"))
	{
		return false;
	}

	if (!Explosion::init()) 
	{
		return false;
	}


	this->mainWin = window;

	ammoBackground.setSize(sf::Vector2f(95, 256));
	ammoBackground.setFillColor(Color(0, 0, 0, 75));
	ammoBackground.setOutlineThickness(3);
	ammoBackground.setOutlineColor(Color::White);
	ammoBackground.setPosition(10, 10);

	slotsBackground.setSize(sf::Vector2f(800, 84));
	slotsBackground.setOrigin(slotsBackground.getSize().x / 2, slotsBackground.getSize().y);
	slotsBackground.setFillColor(Color(0, 0, 0, 75));
	slotsBackground.setOutlineThickness(3);
	slotsBackground.setOutlineColor(Color::White);
	slotsBackground.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10);

	heart.setTexture(heartT, true);
	heart.setPosition(SCREEN_WIDTH / 2 - slotsBackground.getSize().x / 2, (SCREEN_HEIGHT - (slotsBackground.getSize().y + 20)) - heart.getLocalBounds().height);

	scoreText.setString("0000000");
	scoreText.setFont(mainFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(heart.getPosition().x + slotsBackground.getSize().x - scoreText.getLocalBounds().width, heart.getPosition().y);

	ammoText.setString("000");
	ammoText.setFont(mainFont);
	ammoText.setCharacterSize(20);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(50, 15);

	logo.setTexture(logosT[0]);
	logo.setScale(0.5f, 0.5f);
	logo.setPosition(15, 15);

	placeRooms();

	background.setPosition(0, 0);
	background.setSize(Vector2f(MAP_SIZE * TILE_SIZE, MAP_SIZE * TILE_SIZE));
	background.setFillColor(Color(66, 40, 53));
	tilesetT.setSmooth(true);
	
	tile.setTexture(tilesetT, true);

	intRectsTiles = new IntRect[12];

	for (int i = 0; i < 12; i++)
	{
		intRectsTiles[i].left = TILE_SIZE * i;
		intRectsTiles[i].top = 0;
		intRectsTiles[i].width = TILE_SIZE;
		intRectsTiles[i].height = TILE_SIZE;
	}

	exitSprite.setTexture(tilesetT, true);
	exitSprite.setTextureRect(intRectsTiles[11]);

	ScoreIndicator::initAllInstances(mainFont);

	music.setLoop(true);
	music.play();

	return true;
}

/// <summary>
/// Gère les entrées de l'utilisateur
/// </summary>
void SceneGame::getInputs()
{
	int letter = 0;
	bool keyWasPressed = false;
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			transitionToScene(EXIT);
		}

		if (event.type == Event::KeyPressed)
		{
			// Le joueur veut revenir en arrière (Escape)
			if (event.key.code == sf::Keyboard::Escape)
			{
				transitionToScene(TITLE);
			}
			if (event.key.code == Keyboard::P && !pauseKeyPressed)
			{
				pause = !pause;
				pauseKeyPressed = true;
			}
			if (event.key.code == Keyboard::O && !OKeyPressed)
			{
				OKeyPressed = true;
			}
			if (event.key.code == Keyboard::T && !TKeyPressed)
			{
				TKeyPressed = true;
			}
			if (event.key.code == Keyboard::E && !EKeyPressed)
			{
				EKeyPressed = true;
			}
		}

		if (event.type == Event::MouseWheelMoved)
		{
			// Le joueur veut revenir en arrière (Escape)
			if (event.mouseWheel.delta > 0)
			{
				Player::getInstance()->setPrevWeapon();
			}
			else if (event.mouseWheel.delta < 0)
			{
				Player::getInstance()->setNextWeapon();
			}
		}

		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::P)
			{
				pauseKeyPressed = false;
			}
			if (event.key.code == Keyboard::O)
			{
				OKeyPressed = false;
				letter = LetterPressed::O;
				keyWasPressed = true;
			}
			if (event.key.code == Keyboard::T)
			{
				TKeyPressed = false;
				letter = LetterPressed::T;
				keyWasPressed = true;
			}
			if (event.key.code == Keyboard::E)
			{
				EKeyPressed = false;
				letter = LetterPressed::E;
				keyWasPressed = true;
			}
		}
		
	}

	// Générer des commandes en fonction des entrées
	auto manips = recorder.getManips();
	if (manips->getSize() > 0) {

		if ((keyWasPressed))
		{
			recorder.store(new Manip(letter, timer.getElapsedTime()));
			std::cout << "Stored : " << letter << std::endl;
		}
		if ((timer.getElapsedTime() - (*manips)[0]->whenHappened) >= sf::milliseconds(1000))
		{
			for (int i = 0; i < recorder.getSize(); i++)
			{
				recorder.removeCommand();
			}
			std::cout << "Reset." << std::endl;
		}
	}
	else if (keyWasPressed) 
	{
		recorder.store(new Manip(letter, timer.getElapsedTime()));
	}

	// Mettre à jour les inputs du joueur
	Player::getInstance()->getInputs();
}

/// <summary>
/// Gère la mise à jour de la scène
/// </summary>
void SceneGame::update()
{
	timeSpend = frameClock.restart().asSeconds() * FRAMES_PER_SECOND;

	if (checkCheat()) 
	{
		// Ajouter de la vie au joueur avec le cheat TOTOTE
		Player::getInstance()->addHealth(10);
		Player::getInstance()->UpdatePlayerHUD();
	}

	if (pause) 
	{
		return;
	}

	sf::Vector2f mouseWorldPosition = mainWin->mapPixelToCoords(Mouse::getPosition(*mainWin));

	// Calcul de l'angle entre le joueur et la souris
	float angle = atan2(mouseWorldPosition.y - Player::getInstance()->getPosition().y, mouseWorldPosition.x - Player::getInstance()->getPosition().x);

	// Mettre à jour les bonus
	PowerUp::Bonus::updateInstances();

	// Mettre à jour les projectiles
	Projectile::updateActiveInstances(timeSpend, *this);

	// Mettre à jour les ennemis
	Enemy::updateActiveInstances(timeSpend, *this);

	// Mettre à jour les indicateurs de points
	ScoreIndicator::updateActiveInstances(timeSpend);

	// Mettre à jour les explosions
	Explosion::updateActiveInstances(timeSpend);

	// Mettre à jour le joueur
	Player::getInstance()->update(angle, timeSpend, ammoText, *this);

	for (auto instance : spawnerInstances)
	{
		if (instance->isActive())
		{
			instance->spawnEnemy((EnemyType)(rand() % 5));
		}
	}

	// Gérer les collisions entre les projectiles et les murs
	for (auto instance : destructableWallInstances)
	{
		Projectile * projectile = Projectile::checkCollisionWith(*instance);
		if (instance->isActive() && projectile != nullptr) 
		{
			instance->addHealth(-100);
			projectile->setActive(false);
			if (instance->getHealth() <= 0) 
			{
				IntMap::getInstance()->setElement(instance->getPositionDependingOnMap().x,
					instance->getPositionDependingOnMap().y, 0);
				instance->setActive(false);
			}
		}
	}

	// Gérer les collisions entre les spawners et les murs
	for (auto instance : spawnerInstances)
	{
		Projectile * projectile = Projectile::checkCollisionWith(*instance);
		if (instance->isActive() && projectile != nullptr)
		{
			if (projectile->isShotByPlayer()) 
			{
				instance->addHealth(-100);
				projectile->setActive(false);
				if (instance->getHealth() <= 0)
				{
					instance->setActive(false);
				}
			}
		}
	}

	// Centrer la vue sur le joueur
	view.setCenter(Player::getInstance()->getPosition());

	// Gérer la collision entre le joueur et la fin du niveau
	if (Player::getInstance()->getGlobalBounds().intersects(exitSprite.getGlobalBounds()))
	{
		loadNextLevel();
	}

	//Empêcher les débordements d'écran
	crossingViewLimitsAdjustment();
}

/// <summary>
/// Mettre à jour l'Interface utilisateur.
/// </summary>
void SceneGame::updateUI()
{
	// On met  jour l'UI
	scoreText.setString(std::to_string(Player::getInstance()->getScore()));
	for (int j = 7 - scoreText.getString().getSize(); j > 0; j--)
	{
		scoreText.setString("0" + scoreText.getString());
	}
}

/// <summary>
/// Mettre fin au jeu.
/// </summary>
void SceneGame::endGame()
{
	currentPlayerScore = Player::getInstance()->getScore();
	transitionToScene(END);
}
/// <summary>
/// Gère l'affichage de la scène
/// </summary>
void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	mainWin->clear();
	mainWin->setView(view);
	mainWin->draw(background);
	// Afficher les tuiles
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			tile.setPosition(i * TILE_SIZE, j * TILE_SIZE);
			switch (IntMap::getInstance()->getElement(i,j))
			{
			case 0:
				tile.setTextureRect(intRectsTiles[(i + j * j) % 9]);
				mainWin->draw(tile);
				break;
			case 1:
				if (IntMap::getInstance()->getElement(i,j-1) != 1) {
					tile.setTextureRect(intRectsTiles[10]);
					mainWin->draw(tile);
				}
				else if (IntMap::getInstance()->getElement(i,j + 1) != 1)
				{
					tile.setTextureRect(intRectsTiles[9]);
					mainWin->draw(tile);
				}
				break;
			}
		}
	}
	mainWin->draw(exitSprite);
	// Afficher tous les objets actifs en jeu
	GameObject::drawActiveInstances(*mainWin);
	Player::getInstance()->drawPlayerHUD(*mainWin);
	// Afficher les explosions au dessus des gameobjects
	Explosion::drawActiveInstances(*mainWin);
	// Afficher les indicateurs de points
	ScoreIndicator::drawActiveInstances(*mainWin);
	drawHUD();
	mainWin->display();
}

/// <summary>
/// Dessiner le hud.
/// </summary>
void SceneGame::drawHUD() 
{
	mainWin->setView(HUD);
	mainWin->draw(slotsBackground);
	mainWin->draw(ammoBackground);
	// Afficher les vies du joueur
	Vector2f firstHeartPosition = heart.getPosition();
	for (int i = 0; i < Player::getInstance()->getRemainingLives(); i++) 
	{
		mainWin->draw(heart);
		heart.setPosition(heart.getPosition().x + heart.getLocalBounds().width + 10, heart.getPosition().y);
	}
	heart.setPosition(firstHeartPosition);
	mainWin->draw(scoreText);

	float firstAmmoTextY = ammoText.getPosition().y;
	ProjectileType activeProjectile = Player::getInstance()->getCurrentProjectileType();
	logo.setScale(0.6f, 0.6f);
	ammoText.setCharacterSize(25);
	int i = 0;
	do 
	{
		// Afficher les munitions pour chaque arme
		logo.setTexture(logosT[Player::getInstance()->getCurrentProjectileType() + 1]);
		ammoText.setString(std::to_string(Player::getInstance()->getCurrentAmmo()));
		for (int j = 0; j < 3 - ammoText.getString().getSize(); j++)
		{
			ammoText.setString("0" + ammoText.getString());
		}
		logo.setPosition(logo.getPosition().x, firstAmmoTextY + (i * 30));
		ammoText.setPosition(ammoText.getPosition().x, firstAmmoTextY + (i * 30));
		mainWin->draw(ammoText);
		mainWin->draw(logo);
		logo.setScale(0.5f, 0.5f);
		ammoText.setCharacterSize(20);
		Player::getInstance()->setNextWeapon();
		i++;
	} 
	while (activeProjectile != Player::getInstance()->getCurrentProjectileType());
	logo.setPosition(logo.getPosition().x, firstAmmoTextY);
	ammoText.setPosition(ammoText.getPosition().x, firstAmmoTextY);
	heart.setPosition(firstHeartPosition);
	mainWin->setView(view);
}

/// <summary>
/// Empêche l'écran de dépasser les limites logiques du monde
/// </summary>
void SceneGame::crossingViewLimitsAdjustment()
{
	if (view.getCenter().x < VIEW_LIMIT_MIN_X)
	{
		view.setCenter(VIEW_LIMIT_MIN_X, view.getCenter().y);
	}
	else if (view.getCenter().x > VIEW_LIMIT_MAX_X)
	{
		view.setCenter(VIEW_LIMIT_MAX_X, view.getCenter().y);
	}

	if (view.getCenter().y < VIEW_LIMIT_MIN_Y)
	{
		view.setCenter(view.getCenter().x, VIEW_LIMIT_MIN_Y);
	}
	else if (view.getCenter().y > VIEW_LIMIT_MAX_Y)
	{
		view.setCenter(view.getCenter().x, VIEW_LIMIT_MAX_Y);
	}
}