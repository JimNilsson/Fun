#include "sfmath.h"
#include <math.h>
sf::Vector2f sfm::normalize(const sf::Vector2f & v)
{
	return v / sqrtf(v.x * v.x + v.y * v.y);
}

float sfm::dot(const sf::Vector2f & u, const sf::Vector2f & v)
{
	return u.x * v.x + u.y * v.y;
}
/*Normalizes u and v and returns normalized half vector*/
sf::Vector2f sfm::halfvector(const sf::Vector2f & u, const sf::Vector2f & v)
{
	return normalize((normalize(u) + normalize(v)));
}

float sfm::length(const sf::Vector2f & u)
{
	return sqrtf(u.x * u.x + u.y * u.y);
}


