#include "PhysGame.h"
#include "Application.h"

PhysGame::PhysGame(Application * app) : IState(app)
{
	Events = _app->Events();

	_gameObjects.push_back(GameObject(&_physEngine, { 200, 10 }, 10, ROUND, 100, 100, 0));
	//_gameObjects.back().Physics()->SetVelocity({ 50, 0 });
	_gameObjects.push_back(GameObject(&_physEngine, { 650, 50 }, 10, ROUND, 100, 100, 0));
//	_gameObjects.push_back(GameObject(&_physEngine, { 550, 50 }, 10, ROUND, 100, 100, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 200, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 100, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 400, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 500, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	_gameObjects.push_back(GameObject(&_physEngine, { 200, 320 }, 100, RECT | STATIC, 600, 100, 15));
	_gameObjects.push_back(GameObject(&_physEngine, { 600, 320 }, 100, RECT | STATIC, 600, 100, -15));
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
