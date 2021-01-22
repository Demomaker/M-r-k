#pragma once
#include "Bonus.h"

namespace PowerUp
{
	/// <summary>
	/// Représente le concept d'un multiplicateur de score en jeu
	/// </summary>
	class ScoreMultiplier : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'un multiplicateur de score
		/// </summary>
		ScoreMultiplier();

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;
	};
}

