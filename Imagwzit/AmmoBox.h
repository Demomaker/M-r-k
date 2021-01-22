#pragma once
#include "Bonus.h"

namespace PowerUp
{
	/// <summary>
	/// Représente le contexte graphique et logique d'un bonus de munitions dans l'espace de jeu
	/// </summary>
	class AmmoBox : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'une boîte de munitions
		/// </summary>
		/// <param name="ammoType">Type de boîte de munitions</param>
		AmmoBox(BonusType ammoType);

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;

		/// <summary>
		/// Obtient le type de la boîte de munitions
		/// </summary>
		/// <return>Le type de la boîte de munitions</return>
		BonusType getAmmoBoxType() const;

	private:		
		/// <summary>
		/// Le type d'ammo
		/// </summary>
		BonusType ammoType;
	};
}

