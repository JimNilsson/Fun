#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <SFML\Graphics.hpp>
#include <vector>

class Snake : public sf::Drawable
{
public:
	Snake(float _timePerMovement = 0.25f);
	~Snake();
	enum SnakeStatus
	{
		ALL_FINE,
		COLLIDED
	};
	SnakeStatus Update(float dt);
	void Grow();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	sf::FloatRect HeadBoundingBox() const;
	bool SelfCollide() const;

private:
	std::vector<sf::RectangleShape> _segments;
	sf::Vector2f _velocity;
	sf::Vector2f _pendingVelocity;
	float _timePerMovement;
	float _accumulatedTime;
	int _segmentSize;
};



#endif
