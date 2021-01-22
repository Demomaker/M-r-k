#include "ScoreMultiplier.h"


/// <summary>
/// Constructeur d'un multiplicateur de score
/// </summary>
PowerUp::ScoreMultiplier::ScoreMultiplier()
{
	setTexture(bonusT[BonusType::ScoreMultiplierType]);
}

/// <summary>
/// Active le bonus
/// </summary>
void PowerUp::ScoreMultiplier::pickUp()
{
	Bonus::pickUp();
}
