#pragma once

/// <summary>
/// La taille des tuiles
/// </summary>
static const int TILE_SIZE = 64;

/// <summary>
/// La taille des power-ups
/// </summary>
static const int POWER_UP_SIZE = 50;

/// <summary>
/// La taille minimale d'une chambre
/// </summary>
static const int MIN_ROOM_SIZE = 3;

/// <summary>
/// La taille maximale d'une chambre
/// </summary>
static const int MAX_ROOM_SIZE = 16;

/// <summary>
/// La taille maximale de la carte
/// </summary>
static const int MAP_SIZE = 64;

/// <summary>
/// Le nombre maximal de chambres
/// </summary>
static const int MAX_NB_ROOMS = 10;

/// <summary>
/// Le nombre minimal de chambres
/// </summary>
static const int MIN_NB_ROOMS = 6;

/// <summary>
/// Le nombre maximal d'ennemis
/// </summary>
static const int MAX_NB_ENEMIES = 30;

/// <summary>
/// Le nombre minimal d'ennemis
/// </summary>
static const int MIN_NB_ENEMIES = 10;

/// <summary>
/// La quantité maximale de tentatives pour créer une chambre
/// </summary>
static const int MAX_NB_ATTEMPTS_TO_CREATE_ROOM = 5;

/// <summary>
/// Le nombre de frames par seconde
/// </summary>
static const int FRAMES_PER_SECOND = 60;

/// <summary>
/// Nombre de munitions "FLAME" donné par un bonus
/// </summary>
const static int NB_FLAME_AMMO = 250;

/// <summary>
/// Nombre de munitions "MISSILE" donné par un bonus
/// </summary>
const static int NB_MISSILE_AMMO = 50;

/// <summary>
/// Nombre de munitions "SCATTER" donné par un bonus
/// </summary>
const static int NB_SCATTER_AMMO = 60;

/// <summary>
/// Nombre de munitions "SCATTER" donné par un bonus
/// </summary>
const static int NB_BOMB_AMMO = 5;

/// <summary>
/// Nombre de munitions "SCATTER" donné par un bonus
/// </summary>
const static int NB_LASER_AMMO = 60;

/// <summary>
/// Quantité de bonus disponible en jeu
/// </summary>
const static int MAX_NB_OF_EACH_BONUS = 2;

/// <summary>
/// Largeur logique de l'écran en pixels
/// </summary>
const int SCREEN_WIDTH = 1920;

/// <summary>
/// Hauteur logique de l'écran en pixels
/// </summary>
const int SCREEN_HEIGHT = 1080;

/// <summary>
/// Largeur logique du monde en pixels
/// </summary>
const static int WORLD_WIDTH = 4096;

/// <summary>
/// Hauteur logique du monde en pixels
/// </summary>
const static int WORLD_HEIGHT = 4096;

/// <summary>
/// Nombre de spiders maximum en jeu
/// </summary>
const static int MAX_NB_ZOMBIES = 40;

/// <summary>
/// Nombre de spiders maximum en jeu
/// </summary>
const static int MAX_NB_SPIDERS = 40;

/// <summary>
/// Nombre de spiders maximum en jeu
/// </summary>
const static int MAX_NB_GHOSTS = 40;

/// <summary>
/// Nombre de spiders maximum en jeu
/// </summary>
const static int MAX_NB_SKELETONS = 40;

/// <summary>
/// Nombre de spiders maximum en jeu
/// </summary>
const static int MAX_NB_BOMBERMANS = 40;

/// <summary>
/// Nombre de spawners maximum en jeu
/// </summary>
const static int MAX_NB_SPAWNERS = 20;

/// <summary>
/// Nombre de murs destructibles maximum par chambre en jeu
/// </summary>
const static int MAX_NB_DESTRUCTABLE_WALLS = 20;

/// <summary>
/// Différence de distance pour déterminer si la cible est atteinte
/// </summary>
const static int POSITION_THRESHOLD = 2;

/// <summary>
/// La quantité maximal d'ammo par arme
/// </summary>
const static int MAX_NB_AMMO_WEAPON = 999;

/// <summary>
/// La durée des bombes de gaz
/// </summary>
const static int GAS_BOMB_DURATION = 5;

/// <summary>
/// La probabilité qu'un bonus apparaisse sur 100
/// </summary>
const static int BONUS_PROBABILITY_ON_100 = 20;


