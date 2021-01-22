#include "GameObject.h"
#include <algorithm>
#include "Zombie.h"
#include "Ghost.h"
#include "Projectile.h"
#include "Bomberman.h"
#include "Bomb.h"
#include "Spawner.h"

/// <summary>
/// Liste des instances de la classe
/// </summary>
std::list<GameObject*> GameObject::instances;

/// <summary>
/// Constructeur d'un GameObject
/// </summary>
GameObject::GameObject()
{
	active = false;
	// On ajoute l'instance � la liste d'instances
	instances.push_back(this);
}

/// <summary>
/// D�constructeur d'un GameObject
/// </summary>
GameObject::~GameObject()
{
	// On s'assure d'effacer l'instance de la liste d'instances
	std::list<GameObject*>::iterator gameObject =
		std::find(instances.begin(), instances.end(), this);
	if (gameObject != instances.end())
		instances.erase(gameObject);
}

/// <summary>
/// Met � jour l'�tat du GameObject (Actif ou inactif)
/// </summary>
/// <param name="active">�tat actif ou non du GameObject</param>
void GameObject::setActive(const bool& active)
{
	this->active = active;
}

/// <summary>
/// D�termine si le GameObject est actif
/// </summary>
/// <returns>�tat actif ou non du GameObject</returns>
bool GameObject::isActive() const 
{
	return active;
}

/// <summary>
/// Obtient le cercle de collision du GameObject
/// </summary>
/// <returns>Cercle de collision du GameObject</returns>
CollisionCircle GameObject::getCollisionCircle() const
{
	return CollisionCircle(getGlobalBounds().width / 2, getPosition().x, getPosition().y);;
}

/// <summary>
/// Dessiner toute les instances de la classe qui sont actives
/// </summary>
/// <param name="mainWin">Fen�tre de jeu principale</param>
void GameObject::drawActiveInstances(sf::RenderWindow & mainWin)
{
	// Parcourir la liste d'instances et afficher celles qui sont actives
	for (auto* instance : instances) {
		if (instance->isActive())
			mainWin.draw(*instance);
	}
}

/// <summary>
/// D�tecter la collision avec d'autres.
/// </summary>
/// <param name="gameObject">L'objet pour d�tecter.</param>
/// <returns>true si vrai, false sinon</returns>
bool GameObject::detectCollisionWithOthers(GameObject * gameObject)
{
	// Parcourir la liste d'instances et afficher celles qui sont actives
	for (auto* other : instances) 
	{
		if (other->isActive() == false || gameObject == other || dynamic_cast<Enemy*>(other) == nullptr && dynamic_cast<Enemy*>(gameObject) != nullptr || typeid(*other) == typeid(Spawner) && typeid(*gameObject) == typeid(Enemy))
		{
			continue;
		}
		if (other->getCollisionCircle().checkCollision(gameObject->getCollisionCircle())) 
		{
			PowerUp::Bonus * bonus = dynamic_cast<PowerUp::Bonus*>(other);
			if (bonus != nullptr && typeid(*bonus) != typeid(PowerUp::Bomb)) 
			{
				// On ne veut pas que les projectile collisionnent avec les bonus qui ne sont pas des bombes
				return false;
			}
			Projectile * proj = dynamic_cast<Projectile*>(gameObject);
			if (proj != nullptr && proj->isShotByPlayer() && Player::getInstance() == other)
			{
				// Emp�cher la bombe d'exploser dans la face du joueur quand il la tire
				return false;
			}
			else if (proj != nullptr && !proj->isShotByPlayer() && typeid(*other) == typeid(Bomberman))
			{
				// Emp�cher la bombe d'exploser dans la face de l'ennemi qui la tire
				return false;
			}
			return true;
		}
	}
	return false;
}

/// <summary>
/// D�sactiver tous les objets de jeu actifs
/// </summary>
void GameObject::disableAllActiveGameObjects()
{
	for (auto* instance: instances)
	{
		instance->active = false;
	}
}

