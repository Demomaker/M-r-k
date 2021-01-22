#include "Map.h"
#include "Constants.h"

/// <summary>
/// L'instance de la classe
/// </summary>
IntMap* IntMap::instance;

/// <summary>
/// Obtenir l'instance.
/// </summary>
/// <returns>L'instance</returns>
IntMap * IntMap::getInstance()
{
	if (instance == nullptr) 
	{
		instance = new IntMap();
		// On g�n�re la map
		instance->mapReference = new int*[MAP_SIZE];
		for (int i = 0; i < MAP_SIZE; ++i)
		{
			instance->mapReference[i] = new int[MAP_SIZE];
			for (int j = 0; j < MAP_SIZE; j++)
			{
				instance->mapReference[i][j] = 1;
			}
		}
	}
	return instance;
}

/// <summary>
/// R�initialiser la carte
/// </summary>
void IntMap::reset() 
{
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			mapReference[i][j] = 1;
		}
	}
}

/// <summary>
/// Obtenir un �l�ment selon les coordonn�es sp�cifi�es.
/// </summary>
/// <param name="x">La coordonn�e en x.</param>
/// <param name="y">La coordonn�e en y.</param>
/// <returns>L'�l�ment associ�</returns>
int IntMap::getElement(int x, int y)
{
	return mapReference[x][y];
}

/// <summary>
/// Mettre l'�l�ment aux coordonn�es �gal � la valeur sp�cifi�e.
/// </summary>
/// <param name="x">La coordonn�e en x.</param>
/// <param name="y">La coordonn�e en y.</param>
/// <param name="value">La valeur.</param>
void IntMap::setElement(int x, int y, int value)
{
	mapReference[x][y] = value;
}

/// <summary>
/// Lib�rer la m�moire
/// </summary>
void IntMap::release()
{
	if (instance != nullptr) {
		for (int i = 0; i < MAP_SIZE; i++)
		{
			delete[] instance->mapReference[i];
		}
		delete[] instance->mapReference;
		delete instance;
		instance = nullptr;
	}
}


