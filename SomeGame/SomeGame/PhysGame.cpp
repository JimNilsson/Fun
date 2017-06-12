#include "PhysGame.h"
#include "Application.h"

PhysGame::PhysGame(Application * app) : IState(app)
{
	Events = _app->Events();

	_gameObjects.push_back(GameObject(&_physEngine, { 250, 200 }, 10, ROUND, 100, 100, 0));
	_gameObjects.push_back(GameObject(&_physEngine, { 200, 500 }, 100, ROUND | STATIC, 100, 100, 0));
}

PhysGame::~PhysGame()
{
}

void PhysGame::Update()
{
	float dt = _clock.restart().asSeconds();
	_physEngine.Update(dt);
	for (auto& o : _gameObjects)
	{
		o.Update();
	}
}

void PhysGame::Draw()
{
	for (auto& o : _gameObjects)
		_app->Render(o);
}
