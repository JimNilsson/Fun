#include "PhysGame.h"
#include "Application.h"
#include "MenuState.h"

PhysGame::PhysGame(Application * app) : IState(app)
{


	_gameObjects.push_back(GameObject(&_physEngine, { 200, 150 }, 5000, ROUND, 50, 50, 0));
	//_gameObjects.back().Physics()->SetVelocity({ 50, 0 });
//	_gameObjects.push_back(GameObject(&_physEngine, { 650, 150 }, 50, ROUND, 100, 100, 0));
//	_gameObjects.push_back(GameObject(&_physEngine, { 550, 50 }, 10, ROUND, 100, 100, 0));
	_gameObjects.push_back(GameObject(&_physEngine, { 400, 320 }, 100, ROUND | STATIC, 20, 20, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 100, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 400, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	//_gameObjects.push_back(GameObject(&_physEngine, { 500, 400 }, 100, ROUND | STATIC, 100, 100, 0));
	_gameObjects.push_back(GameObject(&_physEngine, { 400, 0 }, 100, RECT | STATIC, 800, 100, 0));
//	_gameObjects.push_back(GameObject(&_physEngine, { 400, 640 }, 100, RECT | STATIC, 800, 100, 0));
	_gameObjects.push_back(GameObject(&_physEngine, { 0, 320 }, 100, RECT | STATIC, 800, 100, 90));
	_gameObjects.push_back(GameObject(&_physEngine, { 800, 320 }, 100, RECT | STATIC, 800, 100, 90));
	_ground.push_back(WalkableGround(&_physEngine, { 0, 580 }, 800, 100, 0));
	_ground.push_back(WalkableGround(&_physEngine, { 400, 480 }, 700, 100, -25));
	_ground.push_back(WalkableGround(&_physEngine, { -400, 480 }, 700, 100, 25));
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

	if (_app->Events()->LeftMousePress())
	{
		sf::Vector2f target = _app->Events()->MousePos();
		target = target - _gameObjects[0].Physics()->Position();
		_gameObjects[0].Physics()->SetVelocity(target*4.0f);

	}

	if (_app->Events()->RightMousePress())
	{
		sf::Vector2f pos = _app->Events()->MousePos();
		_gameObjects.push_back(GameObject(&_physEngine, pos, 1, ROUND, 10, 10, 0));
	}

	if (_app->Events()->KeySinglePress(sf::Keyboard::Escape))
	{
		_app->ChangeState(new MenuState(_app));
	}
}

void PhysGame::Draw()
{
	for (auto& o : _gameObjects)
		_app->Render(o);
	for (auto& g : _ground)
		_app->Render(g);
	_physEngine.RenderDebug();
}
