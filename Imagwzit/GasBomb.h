#pragma once
#include "Bonus.h"

class Character;

namespace PowerUp
{
	/// <summary>
	/// Repr�sente le contexte graphique et logique d'une bombe de gaz dans l'espace de jeu
	/// </summary>
	class GasBomb : public Bonus
	{
	public:
		/// <summary>
		/// Constructeur d'une bombe de gaz
		/// </summary>
		GasBomb();

		/// <summary>
		/// Active le bonus par le joueur
		/// </summary>
		void pickUp() override;

		/// <summary>
		/// Active le bonus par un ennemi
		/// </summary>
		void enemyPickUp();

		/// <summary>
		///  D�termine si la bombe a �t� prise par le joueur ou non
		/// </summary>
		/// <return>Bombe r�cup�r�e par le joueur</return>
		bool isPickedByPlayer() const;

	private:		
		/// <summary>
		/// Bool�en indiquant si la bombe a �t� prise par le joueur ou non
		/// </summary>
		bool pickedByPlayer = true;
	};
}

