#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include <SFML\Graphics.hpp>
enum : int32_t
{
	ROUND = 1 << 1,
	RECT = 1 << 2,
	STATIC = 1 << 3,
	AT_REST = 1 << 4,
	INACTIVE = 1 << 5,
	HAS_COLLIDED = 1 << 6,
	GLIDING = 1 << 7
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
	float FrictionCoefficient() const;
	int32_t Flags() const;
	float Width() const;
	float Height() const;
	float Rotation() const;
	float AngularVelocity() const;
	sf::Vector2f TopLeft() const;

	void SetPosition(const sf::Vector2f& pos);
	void SetVelocity(const sf::Vector2f& vel);
	void SetAngularVelocity(float angvel);
	void SetForce(const sf::Vector2f& force);
	void AddForce(const sf::Vector2f& force);
	void SetRotation(float rotation);
	void SetMass(float mass);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetGravityAcc(const sf::Vector2f& g);
	void SetCollisionCoefficient(float e);
	void SetFrictionCoefficient(float f);
	void EnableFlag(int32_t flag);
	void DisableFlag(int32_t flag);
	void ToggleFlag(int32_t flag);

	bool Collision(PhysicsComponent& body);

	float MomentOfInertia() const;
	
	void DebugRender();
	static sf::Vector2f _gravity;
private:
	
	void CollisionResponse(const sf::Vector2f ep, const sf::Vector2f& en, const sf::Vector2f& pointOfContact, PhysicsComponent& body);
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _acceleration;
	sf::Vector2f _force;

	sf::Vector2f _epOfLastCollision;


	float _mass;
	float _collisionCoefficient;
	float _frictionCoefficient = 0.2f;
	float _rotation;
	float _angularVelocity; //degrees/s. Negative values are counter clockwise
	float _angularAcceleration;
	int32_t _flags;

	
	float _width;
	float _height;
	struct Line
	{
		sf::Vector2f o;
		sf::Vector2f d;
		float length;
	};
	struct PointLine
	{
		sf::Vector2f p0;
		sf::Vector2f p1;
	};

	void _GetLines(PointLine* lines) const;
	bool _LineVsLine(const PointLine& l1, const PointLine& l2, sf::Vector2f& intersection) const;

	
};


#endif

