#ifndef _SNAKE_GAME_STATE_H_
#define _SNAKE_GAME_STATE_H_

#include <SFML\Graphics.hpp>
#include "IState.h"
#include "Snake.h"

class SnakeState : public IState
{
public:
	SnakeState(Application* app);
	~SnakeState();

	void Update();
	void Draw();
private:
	sf::Clock _clock;

	Snake _snake;
	sf::RectangleShape _apple;

	float _blockSize = 32;

	bool _gameLost = false;
	sf::Text _loserText;

	unsigned _score = 0;
	sf::Text _scoreText;
	

};



#endif
