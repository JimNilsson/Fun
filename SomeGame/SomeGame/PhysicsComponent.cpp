#include "PhysicsComponent.h"
#include "sfmath.h"
PhysicsComponent::PhysicsComponent(const sf::Vector2f& position, float mass, int32_t flags) : _position(position), _mass(mass), _velocity(0,0), _acceleration(0,0), _force(0,0), _flags(flags), _collisionCoefficient(0.80f)
{

}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(float dt)
{
	if ((_flags & AT_REST) || (_flags & STATIC))
		return;
	
	
	_position = _position + _velocity * dt + _acceleration * dt * dt * 0.5f;

	_velocity = _velocity + _acceleration * dt;
	_acceleration = _force / _mass;
	

}

inline sf::Vector2f PhysicsComponent::Position() const
{
	return _position;
}

inline sf::Vector2f PhysicsComponent::Velocity() const
{
	return _velocity;
}

inline sf::Vector2f PhysicsComponent::Acceleration() const
{
	return _acceleration;
}

inline float PhysicsComponent::Mass() const
{
	return _mass;
}

float PhysicsComponent::ResititutionCoefficient() const
{
	return _collisionCoefficient;
}

int32_t PhysicsComponent::Flags() const
{
	return _flags;
}

float PhysicsComponent::Width() const
{
	if (_flags & RECT)
		return _width;
	else
		return _width * 2.0f;
}

float PhysicsComponent::Height() const
{
	if (_flags & RECT)
		return _height;
	else
		return _height * 2.0f;
}

void PhysicsComponent::SetPosition(const sf::Vector2f & pos)
{
	_flags = _flags ^ AT_REST;
	_position = pos;
}

void PhysicsComponent::SetVelocity(const sf::Vector2f & vel)
{
	_flags = _flags ^ AT_REST;
	_velocity = vel;
}

void PhysicsComponent::SetForce(const sf::Vector2f & force)
{
	_flags = _flags ^ AT_REST;
	_force = force;
}

void PhysicsComponent::AddForce(const sf::Vector2f & force)
{
	_flags = _flags ^ AT_REST;
	_force = _force +  force;
}

void PhysicsComponent::SetRotation(float rotation)
{
	_rotation = rotation;

}

void PhysicsComponent::SetMass(float mass)
{
	_mass = mass;
}

void PhysicsComponent::SetWidth(float width)
{
	_width = width;
}

void PhysicsComponent::SetHeight(float height)
{
	_height = height;
}

void PhysicsComponent::SetGravityAcc(const sf::Vector2f & g)
{
	_force = _mass * g;
}



bool PhysicsComponent::Collision(PhysicsComponent & body)
{
	//Two circular objects collide
	if ((_flags & ROUND) && (body.Flags() && ROUND))
	{
		sf::Vector2f ep;
		ep = _position - body.Position();
		float distance = sfm::length(ep);
		ep = ep / distance;
		if (distance < _width + body._width)
		{
			//We have collision
			//First move them apart as to not get stuck
			if (!(_flags & STATIC))
				_position = _position + ep * (_width + body._width - distance + 1);
			else
				body.SetPosition(body._position - ep * (_width + body._width - distance + 1));

			//velocity along collision vector before collision
			float v1p = sfm::dot(_velocity, ep);
			float v2p = sfm::dot(body.Velocity(), ep);
			float totMass = _mass + body.Mass();

			//velocity along collision vector after collision
			float e = (_collisionCoefficient + body.ResititutionCoefficient()) * 0.5f;
			float u1p = ((_mass - body.Mass()*e) / totMass)*v1p + (((1 - e)*body.Mass()) / totMass)*v2p;
			float u2p = ((1 - e)*body.Mass() / totMass)*v1p + ((body.Mass() - _mass*e) / totMass)*v2p;

			if(!(_flags & STATIC))
				_velocity = _velocity + (u1p - v1p) * ep;
			if(!(body.Flags() & STATIC))
				body.SetVelocity(body._velocity + (u2p - v2p) * ep);

		}
		
	}
	else if ((_flags & ROUND) && (body.Flags() && RECT))
	{

	}
	else if ((_flags & RECT) && (body.Flags() && ROUND))
	{

	}
	else if ((_flags & RECT) && (body.Flags() && RECT))
	{

	}
	return false;
}
