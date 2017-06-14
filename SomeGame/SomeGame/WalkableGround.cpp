#include "WalkableGround.h"
#include "PhysicsEngine.h"
#include "Application.h"

WalkableGround::WalkableGround(PhysicsEngine * physEng, const sf::Vector2f & topLeftPos, float width, float height, float rotation)
{
	sf::Vector2f centerPos = topLeftPos + sf::Vector2f(width * 0.5f, height * 0.5f);
	_physicsComponent = physEng->CreatePhysicsComponent(centerPos, 0, STATIC | RECT, width, height, rotation, 0.15f);
	
	
	sf::Texture& grassTexture = Application::GetInstance()->Textures()->GetTexture("Textures/grass.png");
	_grass.setPosition(_physicsComponent->TopLeft() + sf::Vector2f(0.0f, -(float)grassTexture.getSize().y / 8));
	grassTexture.setRepeated(true);
	_grass.setTexture(&grassTexture);
	_grass.setTextureRect({0,0, (int)width, (int)grassTexture.getSize().y });
	_grass.setSize({ width, (float)grassTexture.getSize().y / 4 });
	_grass.setRotation(rotation);
	


	_dirt.setPosition(_physicsComponent->TopLeft());
	sf::Texture& dirtTexture = Application::GetInstance()->Textures()->GetTexture("Textures/dirt.png");
	dirtTexture.setRepeated(true);
	_dirt.setTexture(&dirtTexture);
	_dirt.setTextureRect({ 0,0, (int)width, (int)dirtTexture.getSize().y });
	_dirt.setSize({ width, height });
	_dirt.setRotation(rotation);


}

WalkableGround::~WalkableGround()
{
}

void WalkableGround::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(_dirt);
	target.draw(_grass);
}
