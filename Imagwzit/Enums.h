#pragma once
/// <summary>
/// Types de projectile disponible en jeu
/// </summary>
enum ProjectileType { Bullet = -1,Flame = 0, Missile = 1, Scatter = 2, Bomb = 3, Laser = 4, SpiderWeb = 5};

/// <summary>
/// Types de scènes
/// </summary>
enum SceneType { TITLE, GAME, EXIT, CREDITS, INSTRUCTIONS, END };

/// <summary>
/// Types d'événements sur l'interface graphique
/// </summary>
enum UIEventType { LEFT_MOUSE_PRESSED, LEFT_MOUSE_RELEASED, CONTINUE, BACK };

/// <summary>
/// Types de bonus
/// </summary>
enum BonusType { StarType, ScoreMultiplierType, FlameAmmoBoxType, MissileAmmoBoxType, ScatterAmmoBoxType, RocketLauncherAmmoBoxType, LaserAmmoBoxType, GreenShieldType, BlueShieldType, RedShieldType, GreenBombType, BlueBombType, RedBombType, GasBombType };

/// <summary>
/// Types d'ennemis
/// </summary>
enum EnemyType { ZOMBIE, GHOST, SPIDER, SKELETON, BOMBERMAN };

/// <summary>
/// Types de lettres appuyées
/// </summary>
enum LetterPressed { P, O, T, E };