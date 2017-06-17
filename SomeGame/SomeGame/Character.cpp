#include "Character.h"
#include "PhysicsEngine.h"
#include "Application.h"

Character::Character(PhysicsEngine * phys, const sf::Vector2f & pos)
{
	_physComponent = phys->CreatePhysicsComponent(pos, 80.0f, RECT, 64.0f, 170.0f, 0.0f, 0.05f, 1.0f);
	_sprite.setPosition(_physComponent->TopLeft());
	_sprite.setSize({ 64.0f, 170.0f });
	_sprite.setTexture(&(Application::GetInstance()->Textures()->GetTexture("Textures/char_placeholder.png")));

}

Character::~Character()
{
}

void Character::Update(float dt)
{
	_sprite.setPosition(_physComponent->TopLeft());
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}
