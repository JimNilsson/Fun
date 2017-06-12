#include "GameObject.h"
#include "Application.h"

GameObject::GameObject(PhysicsEngine * p, const sf::Vector2f & position, float mass, int32_t flags, float width, float height, float rotation)
{
	_physComponent = p->CreatePhysicsComponent(position, mass, flags, width, height, rotation);
	_sprite.setPosition(_physComponent->Position());
	_sprite.setTexture(&(Application::GetInstance()->Textures()->GetTexture("Textures/cyanball.png")));
	_sprite.setSize({ _physComponent->Width(), _physComponent->Height() });
	_sprite.setRotation(rotation);
	
}

GameObject::~GameObject()
{
}

void GameObject::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(_sprite);
}

void GameObject::Update()
{
	_sprite.setPosition(_physComponent->Position() - sf::Vector2f(_physComponent->Width(), -_physComponent->Height()) / 2.0f);
}
