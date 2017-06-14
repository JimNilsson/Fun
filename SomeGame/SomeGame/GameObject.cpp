#include "GameObject.h"
#include "Application.h"

GameObject::GameObject(PhysicsEngine * p, const sf::Vector2f & position, float mass, int32_t flags, float width, float height, float rotation)
{
	_physComponent = p->CreatePhysicsComponent(position, mass, flags, width, height, rotation);
	_sprite.setPosition(_physComponent->Position());
	_sprite.setTexture(&(Application::GetInstance()->Textures()->GetTexture("Textures/cyanball.png")));
	_sprite.setSize({ _physComponent->Width(), _physComponent->Height() });
	//_sprite.setRotation(rotation);
	//_sprite.setOutlineThickness(2.0f);
	//_sprite.setOutlineColor(sf::Color::White);
	
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

	_sprite.setPosition(_physComponent->TopLeft());
	_sprite.setRotation(_physComponent->Rotation());
//	_physComponent->DebugRender();

}

PhysicsComponent * GameObject::Physics()
{
	return _physComponent;
}
