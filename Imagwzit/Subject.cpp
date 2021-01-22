#include "Subject.h"

/// <summary>
/// La liste des observateurs
/// </summary>
vector<IObserver*> Subject::observers;

/// <summary>
/// Ajouter un observateur
/// </summary>
/// <param name="observer">L'observateur.</param>
void Subject::addObserver(IObserver* observer)
{
	//Si l'observateur n'est pas déjà dans la liste...
	if (!(std::find(observers.begin(), observers.end(), observer) != observers.end()))
	{
		observers.push_back(observer);
	}
}

/// <summary>
/// Enlever un observateur.
/// </summary>
/// <param name="observer">L'observateur.</param>
void Subject::removeObserver(IObserver* observer)
{
	for (int i = 0; i < observers.size(); i++)
	{
		if (observers[i] == observer)
		{
			observers.erase(observers.begin() + i);
			return;
		}
	}
}

/// <summary>
/// Notifier tous les observateurs.
/// </summary>
void Subject::notifyAllObservers()
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->notify(this);
	}
}