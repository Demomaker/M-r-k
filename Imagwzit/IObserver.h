#pragma once

class Subject;

/// <summary>
/// Repr�sente le concept logique d'un observateur en jeu
/// </summary>
class IObserver
{
public:	
	/// <summary>
	/// �tre notifi� selon un certain sujet.
	/// </summary>
	/// <param name="subject">Le sujet.</param>
	virtual void notify(Subject* subject) = 0;
};

