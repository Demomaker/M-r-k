#pragma once
#include "Bonus.h"

namespace PowerUp
{
	/// <summary>
	/// Représente le concept d'un bonus de bouclier en jeu
	/// </summary>
	class Shield : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'un bonus de bouclier
		/// </summary>
		/// <param name="shieldType">Type de bouclier</param>
		Shield(BonusType shieldType);

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;

		/// <summary>
		/// Obtient le type de bouclier
		/// </summary>
		/// <return>Le type de bouclier</return>
		BonusType getShieldType() const;

	private:		
		/// <summary>
		/// Le type de bouclier
		/// </summary>
		BonusType shieldType;
	};
}

