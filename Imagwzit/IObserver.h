#pragma once

class Subject;

/// <summary>
/// Représente le concept logique d'un observateur en jeu
/// </summary>
class IObserver
{
public:	
	/// <summary>
	/// Être notifié selon un certain sujet.
	/// </summary>
	/// <param name="subject">Le sujet.</param>
	virtual void notify(Subject* subject) = 0;
};

