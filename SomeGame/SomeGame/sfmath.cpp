#include "sfmath.h"
#include <math.h>
#define SFM_PI 3.14159265f
sf::Vector2f sfm::normalize(const sf::Vector2f & v)
{
	return v / sqrtf(v.x * v.x + v.y * v.y);
}

float sfm::dot(const sf::Vector2f & u, const sf::Vector2f & v)
{
	return u.x * v.x + u.y * v.y;
}
float sfm::cross(const sf::Vector2f & u, const sf::Vector2f & v)
{
	//Two dimensional cross product.
	return u.x*v.y - u.y*v.x;
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

sf::Vector2f sfm::rotateDeg(const sf::Vector2f & v, float degrees)
{
	float rad = degrees * (SFM_PI / 180.0f);
	return sf::Vector2f(cosf(rad)*v.x - sinf(rad)*v.y, sinf(rad)*v.x + cosf(rad)*v.y);
}

int sfm::IndexOfMax(int * arr, int size)
{
	int max = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > arr[max])
			max = i;
	}
	return max;
}


