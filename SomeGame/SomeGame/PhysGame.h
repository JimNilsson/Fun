#ifndef _PHYS_GAME_H_
#define _PHYS_GAME_H_

#include "IState.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include <vector>

#include "WalkableGround.h"

class PhysGame : public IState
{
public:
	PhysGame(Application* app);
	~PhysGame();

	virtual void Update();
	virtual void Draw();

private:
	std::vector<WalkableGround> _ground;
	std::vector<GameObject> _gameObjects;
	PhysicsEngine _physEngine;
	sf::Vector2f _gravity;
	sf::Clock _clock;

};


#endif
