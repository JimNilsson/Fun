#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "PhysicsEngine.h"
#include <SFML\Graphics.hpp>

class GameObject : public sf::Drawable
{
public:
	GameObject(PhysicsEngine* p, const sf::Vector2f & position, float mass, int32_t flags, float width, float height, float rotation);
	~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void Update();
	PhysicsComponent* Physics();

private:

	sf::RectangleShape _sprite;
	PhysicsComponent* _physComponent;

};



#endif

