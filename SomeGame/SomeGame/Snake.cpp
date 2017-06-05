#include "Snake.h"
#include "Application.h"

Snake::Snake(float timePerMovement, float segmentSize)
{
	Application* app = Application::GetInstance();
	
	_timePerMovement = timePerMovement;
	_segmentSize = segmentSize;
	float startPosX = _segmentSize * ((app->Width() / (uint32_t)_segmentSize) / 2);
	float startPosY = _segmentSize * ((app->Height() / (uint32_t)_segmentSize) / 2);
	_velocity = { 0, 0 };
	_pendingVelocity = { 0,0 };
	

	_segments.push_back(sf::RectangleShape({ (float)_segmentSize, (float)_segmentSize }));
	_segments.push_back(sf::RectangleShape({ (float)_segmentSize, (float)_segmentSize }));
	_segments.push_back(sf::RectangleShape({ (float)_segmentSize, (float)_segmentSize }));
	_segments[0].setPosition({ startPosX , startPosY });
	_segments[0].setTexture(&(app->Textures()->GetTexture("Textures/snakehead.png")));
	_segments[1].setPosition({ startPosX + 1 * (_segmentSize), startPosY });
	_segments[1].setTexture(&(app->Textures()->GetTexture("Textures/snakebody.png")));
	_segments[2].setPosition({ startPosX + 2 * (_segmentSize), startPosY });
	_segments[2].setTexture(&(app->Textures()->GetTexture("Textures/snaketail.png")));
}

Snake::~Snake()
{
}

Snake::SnakeStatus Snake::Update(float dt)
{
	Application* app = Application::GetInstance();

	SnakeStatus status = SnakeStatus::ALL_FINE;

	if (app->Events()->KeyDown(sf::Keyboard::Up) && _velocity.y == 0)
	{
		_pendingVelocity = sf::Vector2f(0, -_segmentSize);
	}
	else if (app->Events()->KeyDown(sf::Keyboard::Down) && _velocity.y == 0)
	{
		_pendingVelocity = sf::Vector2f(0, _segmentSize);
	}
	else if (app->Events()->KeyDown(sf::Keyboard::Left) && _velocity.x == 0)
	{
		_pendingVelocity = sf::Vector2f(-_segmentSize, 0);
	}
	else if (app->Events()->KeyDown(sf::Keyboard::Right) && _velocity.x == 0)
	{
		_pendingVelocity = sf::Vector2f(_segmentSize, 0);
	}

	_accumulatedTime += dt;
	if (_accumulatedTime >= _timePerMovement && _pendingVelocity != sf::Vector2f(0,0))
	{
		_velocity = _pendingVelocity;
		_accumulatedTime = 0;

		sf::Vector2f previousPos = _segments[0].getPosition();
		_segments[0].move(_velocity);
		for (size_t i = 1; i < _segments.size(); i++)
		{
			sf::Vector2f temp = _segments[i].getPosition();
			_segments[i].setPosition(previousPos);
			previousPos = temp;
		}
		if (SelfCollide())
			status = SnakeStatus::COLLIDED;
		sf::Vector2f headPos = _segments[0].getPosition();
		if (headPos.x < 0 || headPos.x >= app->Width() || headPos.y < 0 || headPos.y >= app->Height())
			status = SnakeStatus::COLLIDED;
	}
	return status;
	
}

void Snake::Grow()
{
	_segments.push_back(sf::RectangleShape({ (float)_segmentSize, (float)_segmentSize }));
	_segments.back().setTexture(_segments[_segments.size() - 2].getTexture());
	_segments[_segments.size() - 2].setTexture(_segments[_segments.size() - 3].getTexture());
	_segments.back().setPosition(_segments[_segments.size() - 2].getPosition());
}

void Snake::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	for (auto& segment : _segments)
		target.draw(segment);
}

sf::FloatRect Snake::HeadBoundingBox() const
{
	return _segments[0].getGlobalBounds();
}

bool Snake::SelfCollide() const
{
	sf::FloatRect head = HeadBoundingBox();
	for (size_t i = 2; i < _segments.size(); i++)
		if (head.intersects(_segments[i].getGlobalBounds()))
			return true;
	return false;
}

bool Snake::OnBody(const sf::FloatRect & rect) const
{
	for (auto& segment : _segments)
		if (segment.getGlobalBounds().intersects(rect))
			return true;
	return false;
}
