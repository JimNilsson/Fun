#include "SnakeGameState.h"
#include "MenuState.h"
#include "Application.h"

SnakeState::SnakeState(Application * app) : IState(app), _snake(0.10f, 32)
{
	_clock.restart();

	_apple.setTexture(&(_app->Textures()->GetTexture("Textures/apple.png")));
	_apple.setSize({ _blockSize,_blockSize });

	float x = (rand() % (_app->Width() / (uint32_t)_blockSize)) * _blockSize;
	float y = (rand() % (_app->Height() / (uint32_t)_blockSize)) * _blockSize;
	_apple.setPosition({ x,y });

	_loserText.setString("You lose.\nPress Esc to go back to menu");
	_loserText.setFont(_app->Fonts()->GetFont("Fonts/arial.ttf"));
	float midX = _app->Width() / 2;
	float midY = _app->Height() / 2;
	_loserText.setPosition({ midX - _loserText.getGlobalBounds().width / 2, midY - _loserText.getGlobalBounds().height / 2 });

	_scoreText.setString("Score 00000");
	_scoreText.setFont(_app->Fonts()->GetFont("Fonts/arial.ttf"));
	_scoreText.setPosition({ _app->Width() - _scoreText.getGlobalBounds().width - 10, 10 });
}

SnakeState::~SnakeState()
{
}

void SnakeState::Update()
{
	
	float dt = _clock.restart().asSeconds();
	if (_app->Events()->KeySinglePress(sf::Keyboard::Escape))
		_app->ChangeState(new MenuState(_app));

	if (!_gameLost)
	{
		if (_snake.Update(dt) == Snake::SnakeStatus::COLLIDED)
			_gameLost = true;

		if (_snake.HeadBoundingBox().intersects(_apple.getGlobalBounds()))
		{
			_snake.Grow();
			do {
				float x = (rand() % (_app->Width() / (uint32_t)_blockSize)) * _blockSize;
				float y = (rand() % (_app->Height() / (uint32_t)_blockSize)) * _blockSize;
				_apple.setPosition({ x,y });
			} while (_snake.OnBody(_apple.getGlobalBounds()));
			_score += 10;

			//Calculate how many digits the score consists of
			int digits = 1;
			int tempScore = _score;
			while (tempScore /= 10)
				digits++;
			std::string scoreString = "Score ";
			//5 is number of digits in score text
			for (int i = digits; i < 5; i++)
				scoreString.append("0");
			scoreString.append(std::to_string(_score));
			_scoreText.setString(scoreString);

		}

	}
}

void SnakeState::Draw()
{
	_app->Render(_snake);
	_app->Render(_apple);
	_app->Render(_scoreText);
	if (_gameLost)
		_app->Render(_loserText);
}
