#pragma once
#include "GameObject.h"
#include "pch.h"
#include "Enums.h"
#include "Subject.h"

namespace PowerUp 
{
	/// <summary>
	/// Repr�sente le contexte graphique et logique d'un bonus dans l'espace de jeu
	/// </summary>
	class Bonus : public GameObject, public Subject
	{
	public:
		/// <summary>
		/// Constructeur d'un bonus
		/// </summary>
		Bonus();

		/// <summary>
		/// Initialise les diff�rents composants de la classe
		/// </summary>
		/// <returns>Succ�s de l'initialisation</returns>
		static bool init();

		/// <summary>
		/// Lib�re les ressources utilis�es par la classe
		/// </summary>
		static void release();

		/// <summary>
		/// Met � jour les instances de la classe
		/// </summary>
		static void updateInstances();

		/// <summary>
		/// Fait appara�tre un bonus en jeu
		/// </summary>
		/// <param name="position">Position � laquelle on fait appara�tre le bonus</param>
		static void spawnABonus(const sf::Vector2f& position);

		/// <summary>
		/// Active le bonus
		/// </summary>
		virtual void pickUp();

	protected:
		/// <summary>
		/// Tableau qui contient les textures des bonus disponibles en jeu
		/// </summary>
		static sf::Texture bonusT[14];

	private:
		/// <summary>
		/// Liste des instances de la classe
		/// </summary>
		static CircularDoubleLinkedList<Bonus> * instances;

		/// <summary>
		/// D�termine si le bonus est en collision avec le cercle de collision sp�cifi�
		/// </summary>
		/// <param name="otherCollisionCircle">Cercle de collision � tester</param>
		/// <returns>Vrai s'il y a une collision, faux sinon</returns>
		bool checkCollisionWith(const CollisionCircle& otherCollisionCircle) const;

		/// <summary>
		/// Fait appara�tre un bonus en jeu
		/// </summary>
		/// <param name="position">Position � laquelle on fait appara�tre le bonus</param>
		void spawn(const sf::Vector2f& position);
	};
}
