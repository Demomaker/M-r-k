#pragma once
#include "Bonus.h"

namespace PowerUp
{
	/// <summary>
	/// Représente le concept d'une étoile en jeu
	/// </summary>
	class Star : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'une étoile
		/// </summary>
		Star();

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;
	};
}

