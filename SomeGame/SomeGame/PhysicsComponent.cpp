#include "PhysicsComponent.h"
#include "sfmath.h"
#include "Application.h"
PhysicsComponent::PhysicsComponent(const sf::Vector2f& position, float mass, int32_t flags) : _position(position), _mass(mass), _velocity(0,0), _acceleration(0,0), _force(0,0), _flags(flags), _collisionCoefficient(0.80f)
{
	if (_flags & STATIC)
		_mass = 9999999999.0f;
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(float dt)
{
	if ((_flags & (AT_REST | STATIC)))
		return;
	



	_acceleration = _force / _mass;
	
	_position = _position + _velocity * dt + _acceleration * dt * dt * 0.5f;

	_velocity = _velocity + _acceleration * dt;
	

}

inline sf::Vector2f PhysicsComponent::Position() const
{
	return _position;
}

sf::Vector2f PhysicsComponent::PositionWithOffset() const
{
	return _position - sf::Vector2f(_width, _height) / 2.0f;
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

float PhysicsComponent::FrictionCoefficient() const
{
	return _frictionCoefficient;
}

int32_t PhysicsComponent::Flags() const
{
	return _flags;
}

float PhysicsComponent::Width() const
{
	return _width;
}

float PhysicsComponent::Height() const
{
	return _height;
}

float PhysicsComponent::Rotation() const
{
	return _rotation;
}

sf::Vector2f PhysicsComponent::TopLeft() const
{
	sf::Vector2f topLeftCorner = _position - sf::Vector2f(_width * 0.5f, _height * 0.5f);
	topLeftCorner = topLeftCorner - _position;
	topLeftCorner = sfm::rotateDeg(topLeftCorner, _rotation);
	
	topLeftCorner = _position + topLeftCorner;
	return topLeftCorner;
}

void PhysicsComponent::SetPosition(const sf::Vector2f & pos)
{
	_flags = _flags & (~AT_REST);
	_position = pos;
}

void PhysicsComponent::SetVelocity(const sf::Vector2f & vel)
{
	_flags = _flags & (~AT_REST);
	if (sfm::length(vel) > 10.0f)
		_velocity = vel;
	else
		_velocity = { 0.0f, 0.0f };
}

void PhysicsComponent::SetForce(const sf::Vector2f & force)
{
	_flags = _flags & (~AT_REST);
	_force = force;
}

void PhysicsComponent::AddForce(const sf::Vector2f & force)
{
	_flags = _flags & (~AT_REST);
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

void PhysicsComponent::SetCollisionCoefficient(float e)
{
	_collisionCoefficient = e;
}

void PhysicsComponent::SetFrictionCoefficient(float f)
{
	_frictionCoefficient = f;
}

void PhysicsComponent::EnableFlag(int32_t flag)
{
	_flags |= flag;
}

void PhysicsComponent::DisableFlag(int32_t flag)
{
	_flags = _flags & (~flag);
}



bool PhysicsComponent::Collision(PhysicsComponent & body)
{
	//Two circular objects collide
	if ((_flags & ROUND) && (body.Flags() & ROUND))
	{
		sf::Vector2f ep;
		ep = _position - body.Position();
		float distance = sfm::length(ep);
		ep = ep / distance;
		if (distance < (_width + body._width) / 2.0f)
		{
			//We have collision
			//First move them apart as to not get stuck
			if (!(_flags & STATIC))
				_position = _position + ep * ((_width + body._width)*0.5f - distance + 2);
			else
				body.SetPosition(body._position - ep * ((_width + body._width)*0.5f - distance + 2));

			//velocity along collision vector before collision
			float v1p = sfm::dot(_velocity, ep);
			float v2p = sfm::dot(body.Velocity(), ep);
			float totMass = _mass + body.Mass();

			//velocity along collision vector after collision
			float e = (_collisionCoefficient + body.ResititutionCoefficient()) * 0.5f;
			float u2p = ((_mass - body.Mass()*e) / totMass)*v1p + (((1.0f - e)*body.Mass()) / totMass)*v2p;
			float u1p = ((1.0f - e)*body.Mass() / totMass)*v1p + ((body.Mass() - _mass*e) / totMass)*v2p;

			if(!(_flags & STATIC))
				SetVelocity(_velocity + (u1p - v1p) * ep);
			if(!(body.Flags() & STATIC))
				body.SetVelocity(body._velocity + (u2p - v2p) * ep);

		}
		
	}
	else if ((_flags & ROUND) && (body.Flags() & RECT))
	{
		body.Collision(*this);
	}
	else if ((_flags & RECT) && (body.Flags() & ROUND))
	{
		//Consider the rectangle to be consisting of 4 lines. One for each edge.

		//Take local corners and transform into global coordinates based on rotation
		sf::Vector2f topLeftCorner = _position - sf::Vector2f(_width * 0.5f, _height * 0.5f);
		topLeftCorner = topLeftCorner - _position;
		topLeftCorner = sfm::rotateDeg(topLeftCorner, _rotation);

		topLeftCorner = _position + topLeftCorner;
		
		sf::Vector2f topRightCorner = _position - sf::Vector2f(-_width * 0.5f, _height * 0.5f);
		topRightCorner = topRightCorner - _position;
		topRightCorner = sfm::rotateDeg(topRightCorner, _rotation);
		topRightCorner = _position + topRightCorner;
		
		sf::Vector2f bottomLeftCorner = _position + sf::Vector2f(-_width * 0.5f, _height * 0.5f);
		bottomLeftCorner = bottomLeftCorner - _position;
		bottomLeftCorner = sfm::rotateDeg(bottomLeftCorner, _rotation);
		bottomLeftCorner = _position + bottomLeftCorner;

		sf::Vector2f bottomRightCorner = _position + sf::Vector2f(_width * 0.5f, _height * 0.5f);
		bottomRightCorner = bottomRightCorner - _position;
		bottomRightCorner = sfm::rotateDeg(bottomRightCorner, _rotation);
		bottomRightCorner = _position + bottomRightCorner;

		//Lines tl->tr, tr->br, br->bl, bl->tl
		struct Line
		{
			sf::Vector2f o;
			sf::Vector2f d;
			float length;
		};
		Line l[4];
		l[0].o = topLeftCorner;
		l[0].d = sfm::normalize(topRightCorner - topLeftCorner);
		l[0].length = sfm::length(topRightCorner - topLeftCorner);
		l[1].o = topRightCorner;
		l[1].d = sfm::normalize(bottomRightCorner - topRightCorner);
		l[1].length = sfm::length(bottomRightCorner - topRightCorner);
		l[2].o = bottomRightCorner;
		l[2].d = sfm::normalize(bottomLeftCorner - bottomRightCorner);
		l[2].length = sfm::length(bottomLeftCorner - bottomRightCorner);
		l[3].o = bottomLeftCorner;
		l[3].d = sfm::normalize(topLeftCorner - bottomLeftCorner);
		l[3].length = sfm::length(topLeftCorner - bottomLeftCorner);

		//Find if a part of the line intersects the circle. If it does, the position on the line that is the closest to the center
		//of the circle is the point which the circle collides with the rect on.
		for (int i = 0; i < 4; i++)
		{
			sf::Vector2f lineToCircle = body.Position() - l[i].o;
			float d = sfm::dot(lineToCircle, l[i].d);
			sf::Vector2f closestPoint = l[i].o + l[i].d * d;
			if (sfm::length(closestPoint - l[i].o) - l[i].length > 0)
				closestPoint = l[i].o + l[i].d * l[i].length;
			if (sfm::dot(closestPoint - l[i].o, l[i].d) < 0)
				closestPoint = l[i].o;
			float distance = sfm::length(closestPoint - body.Position()) - body.Width() * 0.5f;
			if ( distance <= 0.0f )
			{
				//We have collision
				sf::Vector2f ep = sfm::normalize(body.Position() - closestPoint);
				//Make sure we dont get stuck
				if (!(_flags & STATIC))
					_position = _position - ep * (-distance + 0);
				else
					body.SetPosition(body.Position() + ep * (-distance + 0));

				//velocity along collision vector before collision
				float v1p = sfm::dot(_velocity, ep);
				float v2p = sfm::dot(body.Velocity(), ep);
				float totMass = _mass + body.Mass();

				//velocity along collision vector after collision
				float e = (_collisionCoefficient + body.ResititutionCoefficient()) * 0.5f;
				float u1p = ((_mass - body.Mass()*e) / totMass)*v1p + (((1 - e)*body.Mass()) / totMass)*v2p;
				float u2p = ((1 - e)*body.Mass() / totMass)*v1p + ((body.Mass() - _mass*e) / totMass)*v2p;

				sf::Vector2f en;
				en = { -ep.y, ep.x };
				en = -sfm::dot(sfm::normalize(_velocity + body.Velocity()), en)*en;

				float friction = (_frictionCoefficient + body.FrictionCoefficient()) * 0.5f;

				if (!(_flags & STATIC))
					SetVelocity(_velocity + (u1p - v1p) * (ep + en*friction));
				if (!(body.Flags() & STATIC))
					body.SetVelocity(body._velocity + (u2p - v2p) * (ep + en*friction));
				
		/*		body.EnableFlag(ADJACENT_BELOW);
				EnableFlag(ADJACENT_BELOW);*/

				//No need to check other lines
				break;
			}
		}


	}
	else if ((_flags & RECT) && (body.Flags() & RECT))
	{

	}
	return false;
}

void PhysicsComponent::DebugRender()
{

	sf::Vector2f topLeftCorner = _position - sf::Vector2f(_width * 0.5f, _height * 0.5f);
	topLeftCorner = topLeftCorner - _position;
	topLeftCorner = sfm::rotateDeg(topLeftCorner, _rotation);

	topLeftCorner = _position + topLeftCorner;

	sf::Vector2f topRightCorner = _position - sf::Vector2f(-_width * 0.5f, _height * 0.5f);
	topRightCorner = topRightCorner - _position;
	topRightCorner = sfm::rotateDeg(topRightCorner, _rotation);
	topRightCorner = _position + topRightCorner;

	sf::Vector2f bottomLeftCorner = _position + sf::Vector2f(-_width * 0.5f, _height * 0.5f);
	bottomLeftCorner = bottomLeftCorner - _position;
	bottomLeftCorner = sfm::rotateDeg(bottomLeftCorner, _rotation);
	bottomLeftCorner = _position + bottomLeftCorner;

	sf::Vector2f bottomRightCorner = _position + sf::Vector2f(_width * 0.5f, _height * 0.5f);
	bottomRightCorner = bottomRightCorner - _position;
	bottomRightCorner = sfm::rotateDeg(bottomRightCorner, _rotation);
	bottomRightCorner = _position + bottomRightCorner;

	sf::Vertex v[4];
	v[0].color = sf::Color::White;
	v[0].position = topLeftCorner;
	v[1].color = sf::Color::White;
	v[1].position = topRightCorner;
	v[2].color = sf::Color::White;
	v[2].position = bottomRightCorner;
	v[3].color = sf::Color::White;
	v[3].position = bottomLeftCorner;
	
	sf::VertexArray va;
	va.setPrimitiveType(sf::PrimitiveType::LineStrip);
	for (int i = 0; i < 4; i++)
		va.append(v[i]);
	va.append(v[0]);
	Application::GetInstance()->Render(va);
}
