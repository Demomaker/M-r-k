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
	/// R�initialiser la carte
	/// </summary>
	void reset();
	
	/// <summary>
	/// Obtenir un �l�ment selon les coordonn�es sp�cifi�es.
	/// </summary>
	/// <param name="x">La coordonn�e en x.</param>
	/// <param name="y">La coordonn�e en y.</param>
	/// <returns>L'�l�ment associ�</returns>
	int getElement(int x, int y);
	
	/// <summary>
	/// Mettre l'�l�ment aux coordonn�es �gal � la valeur sp�cifi�e.
	/// </summary>
	/// <param name="x">La coordonn�e en x.</param>
	/// <param name="y">La coordonn�e en y.</param>
	/// <param name="value">La valeur.</param>
	void setElement(int x, int y, int value);
	
	/// <summary>
	/// Lib�rer la m�moire
	/// </summary>
	static void release();
private:
	/// <summary>
	/// La r�f�rence de la carte
	/// </summary>
	int** mapReference;
	
	/// <summary>
	/// Instance de la classe
	/// </summary>
	static IntMap* instance;
};

