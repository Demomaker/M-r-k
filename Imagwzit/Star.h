#pragma once
#include "Bonus.h"

namespace PowerUp
{
	/// <summary>
	/// Repr�sente le concept d'une �toile en jeu
	/// </summary>
	class Star : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'une �toile
		/// </summary>
		Star();

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;
	};
}

