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
		// On génère la map
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
/// Réinitialiser la carte
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
/// Obtenir un élément selon les coordonnées spécifiées.
/// </summary>
/// <param name="x">La coordonnée en x.</param>
/// <param name="y">La coordonnée en y.</param>
/// <returns>L'élément associé</returns>
int IntMap::getElement(int x, int y)
{
	return mapReference[x][y];
}

/// <summary>
/// Mettre l'élément aux coordonnées égal à la valeur spécifiée.
/// </summary>
/// <param name="x">La coordonnée en x.</param>
/// <param name="y">La coordonnée en y.</param>
/// <param name="value">La valeur.</param>
void IntMap::setElement(int x, int y, int value)
{
	mapReference[x][y] = value;
}

/// <summary>
/// Libérer la mémoire
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


