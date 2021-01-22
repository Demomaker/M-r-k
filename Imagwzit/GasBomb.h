#pragma once
#include "Bonus.h"

class Character;

namespace PowerUp
{
	/// <summary>
	/// Représente le contexte graphique et logique d'une bombe de gaz dans l'espace de jeu
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
		///  Détermine si la bombe a été prise par le joueur ou non
		/// </summary>
		/// <return>Bombe récupérée par le joueur</return>
		bool isPickedByPlayer() const;

	private:		
		/// <summary>
		/// Booléen indiquant si la bombe a été prise par le joueur ou non
		/// </summary>
		bool pickedByPlayer = true;
	};
}

