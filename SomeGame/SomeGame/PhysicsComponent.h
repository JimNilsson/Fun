#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include <SFML\Graphics.hpp>
enum : int32_t
{
	ROUND = 1 << 1,
	RECT = 1 << 2,
	STATIC = 1 << 3,
	AT_REST = 1 << 4,
	INACTIVE = 1 << 5
};

class PhysicsComponent
{
public:
	PhysicsComponent(const sf::Vector2f& position, float mass, int32_t flags);
	~PhysicsComponent();

	void Update(float dt);

	sf::Vector2f Position() const;
	sf::Vector2f PositionWithOffset() const;
	sf::Vector2f Velocity() const;
	sf::Vector2f Acceleration() const;
	float Mass() const;
	float ResititutionCoefficient() const;
	int32_t Flags() const;
	float Width() const;
	float Height() const;
	float Rotation() const;
	sf::Vector2f TopLeft() const;

	void SetPosition(const sf::Vector2f& pos);
	void SetVelocity(const sf::Vector2f& vel);
	void SetForce(const sf::Vector2f& force);
	void AddForce(const sf::Vector2f& force);
	void SetRotation(float rotation);
	void SetMass(float mass);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetGravityAcc(const sf::Vector2f& g);
	void SetCollisionCoefficient(float e);

	bool Collision(PhysicsComponent& body);
	
	void DebugRender();

private:
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _acceleration;
	sf::Vector2f _force;


	float _mass;
	float _collisionCoefficient;
	float _rotation;
	int32_t _flags;

	
	float _width;
	float _height;

	
};


#endif

