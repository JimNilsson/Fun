#ifndef _WALKABLE_GROUND_H_
#define _WALKABLE_GROUND_H_

#include <SFML\Graphics.hpp>
class PhysicsEngine;
class PhysicsComponent;

class WalkableGround : public sf::Drawable
{
public:
	WalkableGround(PhysicsEngine* physEng, const sf::Vector2f& topLeftPos, float width, float height, float rotation = 0);
	~WalkableGround();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

private:
	sf::RectangleShape _grass;
	sf::RectangleShape _dirt;
	PhysicsComponent* _physicsComponent;

};



#endif

