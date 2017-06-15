#ifndef _PHYS_ENGINE_H_
#define _PHYS_ENGINE_H_

#include "PhysicsComponent.h"
#include <vector>

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(float dt);
	void ClearObjects();
	void RenderDebug();
	PhysicsComponent* CreatePhysicsComponent(const sf::Vector2f& position, float mass, int32_t flags, float width, float height, float rotation, float collisionCoefficient = 0.80f, float frictionCoefficient = 0.80f);

private:
	std::vector<PhysicsComponent> _objects;
	std::vector<PhysicsComponent> _staticObjects;
	std::vector<int> _contactCache;
	const int _maxObjects = 1000;
	const int _maxStaticObjects = 1000;
	sf::Vector2f _gravity;
	int _frame = 0;

};


#endif

