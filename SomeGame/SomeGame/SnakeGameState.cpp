#include "SnakeGameState.h"
#include "MenuState.h"
#include "Application.h"

SnakeState::SnakeState(Application * app) : IState(app), _snake(0.10f)
{
	box.setPosition({ 0,0 });
	box.setTexture(_app->Textures()->GetTexture("Textures/face.png"));
	box.setScale({ 0.25f,0.25f });
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
		if (_app->Events()->KeyDown(sf::Keyboard::A))
			box.move({ -dt * 100, 0 });
		if (_app->Events()->KeyDown(sf::Keyboard::D))
			box.move({ dt * 100, 0 });
		if (_app->Events()->KeyDown(sf::Keyboard::S))
			box.move({ 0, dt * 100 });
		if (_app->Events()->KeyDown(sf::Keyboard::W))
			box.move({ 0, -dt * 100 });

		if (_snake.Update(dt) == Snake::SnakeStatus::COLLIDED)
			_gameLost = true;

		if (_snake.HeadBoundingBox().intersects(_apple.getGlobalBounds()))
		{
			_snake.Grow();
			float x = (rand() % (_app->Width() / (uint32_t)_blockSize)) * _blockSize;
			float y = (rand() % (_app->Height() / (uint32_t)_blockSize)) * _blockSize;
			_apple.setPosition({ x,y });
		}

	}
}

void SnakeState::Draw()
{
	_app->Render(box);
	_app->Render(_snake);
	_app->Render(_apple);
	if (_gameLost)
		_app->Render(_loserText);
}
