#include "PhysicsEngine.h"
#include "sfmath.h"
PhysicsEngine::PhysicsEngine() : _gravity({ 0, 100 })
{
	_objects.reserve(_maxObjects);
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Update(float dt)
{
	//Update dynamic objects and check collision against static objects
	for (auto& o : _objects)
	{
		o.Update(dt);
		for (auto& so : _staticObjects)
		{
			o.Collision(so);
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

PhysicsComponent * PhysicsEngine::CreatePhysicsComponent(const sf::Vector2f & position, float mass, int32_t flags, float width, float height, float rotation)
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

			return &_objects[_objects.size() - 1];
		}
		else
		{
			throw std::exception("Max number of dynamic physics objects reached.");
		}
	}
	else
	{
		if (_objects.size() < _maxObjects)
		{
			_staticObjects.push_back(PhysicsComponent(position, mass, flags));
			auto& p = _staticObjects.back();
			p.SetWidth(width);
			p.SetHeight(height);
			p.SetRotation(rotation);
			p.SetGravityAcc(_gravity);

			return &_staticObjects[_staticObjects.size() - 1];
		}
		else
		{
			throw std::exception("Max number of static physics objects reached.");
		}
	}
}
