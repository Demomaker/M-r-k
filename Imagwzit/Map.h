#pragma once
class IntMap
{
public:	
	/// <summary>
	/// Obtenir l'instance.
	/// </summary>
	/// <returns>L'instance</returns>
	static IntMap * getInstance();	

	/// <summary>
	/// Réinitialiser la carte
	/// </summary>
	void reset();
	
	/// <summary>
	/// Obtenir un élément selon les coordonnées spécifiées.
	/// </summary>
	/// <param name="x">La coordonnée en x.</param>
	/// <param name="y">La coordonnée en y.</param>
	/// <returns>L'élément associé</returns>
	int getElement(int x, int y);
	
	/// <summary>
	/// Mettre l'élément aux coordonnées égal à la valeur spécifiée.
	/// </summary>
	/// <param name="x">La coordonnée en x.</param>
	/// <param name="y">La coordonnée en y.</param>
	/// <param name="value">La valeur.</param>
	void setElement(int x, int y, int value);
	
	/// <summary>
	/// Libérer la mémoire
	/// </summary>
	static void release();
private:
	/// <summary>
	/// La référence de la carte
	/// </summary>
	int** mapReference;
	
	/// <summary>
	/// Instance de la classe
	/// </summary>
	static IntMap* instance;
};

