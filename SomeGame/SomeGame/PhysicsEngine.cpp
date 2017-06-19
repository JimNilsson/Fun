#include "PhysicsEngine.h"
#include "sfmath.h"
PhysicsEngine::PhysicsEngine() : _gravity({ 0, 0 })
{
	_objects.reserve(_maxObjects);
	_staticObjects.reserve(_maxStaticObjects);
	_contactCache.resize(_maxObjects);
	memset(_contactCache.data(), -1, _contactCache.size() * sizeof(int));
	PhysicsComponent::_gravity = _gravity;
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Update(float dt)
{
	_frame++;
	////Attraction test...
	//for (auto &o : _objects)
	//{
	//	sf::Vector2f center = { 400.0f, 320.0f };
	//	sf::Vector2f forceVec = center - o.Position();
	//	float dist = sfm::length(forceVec);
	//	forceVec /= dist;
	//	forceVec *= 1000000000.0f;
	//	dist = dist * dist;
	//	float mass = o.Mass();
	//	forceVec /= dist;
	//	o.SetForce(forceVec + _gravity * mass);


	//}
	//Update dynamic objects and check collision against static objects
	int indexD = 0;
	for (auto& o : _objects)
	{
		o.Update(dt);
		int indexS = 0;
		for (auto& so : _staticObjects)
		{
			if (_contactCache[indexD] != indexS)
			{
				if (o.Collision(so))
				{
					_contactCache[indexD] = indexS;
					o.DisableFlag(GLIDING);
					break;
				}
			}
			indexS++;
		}
		indexD++;
	}
	if (_frame == 10)
	{
		memset(_contactCache.data(), -1, _objects.size() * sizeof(int));
		//for (auto& o : _objects)
		//	o.DisableFlag(HAS_COLLIDED);
		_frame = 0;
	}

	//Check dynamic objects against dynamic objects
	for (int i = 0; i < _objects.size(); i++)
	{
		for (int j = i + 1; j < _objects.size(); j++)
		{
			if (_objects[i].Collision(_objects[j]))
			{
				_objects[i].DisableFlag(GLIDING);
				_objects[j].DisableFlag(GLIDING);
			}
		}
	}

}

void PhysicsEngine::ClearObjects()
{
	_objects.clear();
	_objects.reserve(1000); //In case a reallocation happens.
	_staticObjects.clear();
	_staticObjects.reserve(1000);
}

void PhysicsEngine::RenderDebug()
{
	for (auto& o : _objects)
		o.DebugRender();
}

PhysicsComponent * PhysicsEngine::CreatePhysicsComponent(const sf::Vector2f & position, float mass, int32_t flags, float width, float height, float rotation, float collisionCoefficient, float frictionCoefficient)
{
	//Game objects store references to entries in the vector, as such we cannot allow a reallocation to happen since that
	//would invalidate the references. The restriction to this is that we are limited to a certain number of physics objects.
	//This could be solved by having several memory pools but that is a hassle. We won't have more than a certain number of
	//physics objects per level either way.
	if (!(flags & STATIC))
	{
		if (_objects.size() < _maxObjects)
		{
			_objects.push_back(PhysicsComponent(position, mass, flags));
			auto& p = _objects.back();
			p.SetWidth(width);
			p.SetHeight(height);
			p.SetRotation(rotation);
			p.SetGravityAcc(_gravity);
			p.SetCollisionCoefficient(collisionCoefficient);
			p.SetFrictionCoefficient(frictionCoefficient);
			
			return &_objects[_objects.size() - 1];
		}
		else
		{
			throw std::exception("Max number of dynamic physics objects reached.");
		}
	}
	else
	{
		//Yeah gotta refactor this
		if (_staticObjects.size() < _maxStaticObjects)
		{
			_staticObjects.push_back(PhysicsComponent(position, mass, flags));
			auto& p = _staticObjects.back();
			p.SetWidth(width);
			p.SetHeight(height);
			p.SetRotation(rotation);
			p.SetGravityAcc({ 0,0 });
			p.SetCollisionCoefficient(collisionCoefficient);
			p.SetFrictionCoefficient(frictionCoefficient);

			return &_staticObjects[_staticObjects.size() - 1];
		}
		else
		{
			throw std::exception("Max number of static physics objects reached.");
		}
	}
}
