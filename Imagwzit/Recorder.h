#pragma once
#include "Manip.h"
#include "Queue.h"

/* The invoker class */
class Recorder
{
public:	
	/// <summary>
	/// Le destructeur d'un enregistreur de manipulations
	/// </summary>
	~Recorder()
	{
		for (int i = 0; i < manips.getSize(); i++)
		{
			delete manips[i];
			manips.pop();
			size--;
		}
	}	
	/// <summary>
	/// Obtenir les manipulations.
	/// </summary>
	/// <returns>Les manipulations</returns>
	Queue<Manip>* getManips()
	{
		return &manips;
	}
	
	/// <summary>
	/// Obtenir le nombre de manipulations
	/// </summary>
	/// <returns>Le nombre de manipulations</returns>
	int getSize() {
		return size;
	}
	
	/// <summary>
	/// Garder en mémoire une certaine manipulation
	/// </summary>
	/// <param name="manip">La manipulation</param>
	void store(Manip* manip)
	{
		manips.push(manip);
		size++;
	}

	//Si après un certain temps on veut que la première commande ajoutée soit retirée
	void removeCommand()
	{
		delete manips[0];
		manips.pop();
		size--;
	}

private:	
	/// <summary>
	/// Les manipulations
	/// </summary>
	Queue<Manip> manips;	

	/// <summary>
	/// La quantité de manipulations
	/// </summary>
	int size = 0;
};