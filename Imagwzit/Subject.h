#pragma once
#include "IObserver.h"
#include <vector>

using std::vector;

/// <summary>
/// Représente le contexte logique d'un sujet en jeu
/// </summary>
class Subject
{
public:	
	/// <summary>
	/// Ajouter un observateur
	/// </summary>
	/// <param name="observer">L'observateur.</param>
	static void addObserver(IObserver* observer);
	
	/// <summary>
	/// Enlever un observateur.
	/// </summary>
	/// <param name="observer">L'observateur.</param>
	static void removeObserver(IObserver* observer);
	
	/// <summary>
	/// Notifier tous les observateurs.
	/// </summary>
	virtual void notifyAllObservers();  //Virtuel seulement pour que typeID fonctionne avec typeid

protected:		
	/// <summary>
	/// La liste des observateurs
	/// </summary>
	static vector<IObserver*> observers;
};
