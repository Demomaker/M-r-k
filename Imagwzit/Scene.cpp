#include "Scene.h"

/// <summary>
/// Le score du joueur
/// </summary>
int Scene::currentPlayerScore;
/// <summary>
/// Effectue une transition vers une autre sc�ne
/// </summary>
/// <param name="to">Sc�ne vers laquelle on veut faire une transition</param>
void Scene::transitionToScene(SceneType to)
{
	isRunning = false;
	nextScene = to;
}
