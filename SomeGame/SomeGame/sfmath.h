#ifndef _SFMATH_H_
#define _SFMATH_H_

#include <SFML\System\Vector2.hpp>

namespace sfm
{
	sf::Vector2f normalize(const sf::Vector2f& v);
	float dot(const sf::Vector2f& u, const sf::Vector2f& v);
	sf::Vector2f halfvector(const sf::Vector2f& u, const sf::Vector2f& v);
	float length(const sf::Vector2f& u);
	sf::Vector2f rotateDeg(const sf::Vector2f& v, float degrees);

};



#endif

