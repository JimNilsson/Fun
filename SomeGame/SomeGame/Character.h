#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <SFML\Graphics.hpp>
class PhysicsComponent;
class PhysicsEngine;


class Character : public sf::Drawable
{
public:
	Character(PhysicsEngine* phys, const sf::Vector2f& pos);
	~Character();

	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	PhysicsComponent* _physComponent;
	sf::RectangleShape _sprite;
};



#endif

