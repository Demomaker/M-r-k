#include "Scene.h"

/// <summary>
/// Le score du joueur
/// </summary>
int Scene::currentPlayerScore;
/// <summary>
/// Effectue une transition vers une autre scène
/// </summary>
/// <param name="to">Scène vers laquelle on veut faire une transition</param>
void Scene::transitionToScene(SceneType to)
{
	isRunning = false;
	nextScene = to;
}
