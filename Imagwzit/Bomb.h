#pragma once
#include "Bonus.h"
#include "IObserver.h"

namespace PowerUp
{
	/// <summary>
	/// Représente le concept d'une bombe
	/// </summary>
	class Bomb : public Bonus, public IObserver
	{
	public:
		/// <summary>
		/// Constructeur d'une bombe
		/// </summary>
		/// <param name="bombType">Type de bombe</param>
		Bomb(BonusType bombType);

		/// <summary>
		/// Active le bonus
		/// </summary>
		void pickUp() override;

		/// <summary>
		/// Permet de notifier l'observateur
		/// </summary>
		/// <param name="subject">Sujet qui notifie</param>
		void notify(Subject * subject) override;

		/// <summary>
		/// Obtient le type de la bombe
		/// </summary>
		/// <return>Le type de la bombe</return>
		BonusType getBombType() const;

	private:		
		/// <summary>
		/// Le type de la bombe
		/// </summary>
		BonusType bombType;
	};
}

