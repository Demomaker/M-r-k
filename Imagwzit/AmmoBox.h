#pragma once
#include "Bonus.h"

namespace PowerUp
{
	/// <summary>
	/// Repr�sente le contexte graphique et logique d'un bonus de munitions dans l'espace de jeu
	/// </summary>
	class AmmoBox : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'une bo�te de munitions
		/// </summary>
		/// <param name="ammoType">Type de bo�te de munitions</param>
		AmmoBox(BonusType ammoType);

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;

		/// <summary>
		/// Obtient le type de la bo�te de munitions
		/// </summary>
		/// <return>Le type de la bo�te de munitions</return>
		BonusType getAmmoBoxType() const;

	private:		
		/// <summary>
		/// Le type d'ammo
		/// </summary>
		BonusType ammoType;
	};
}

