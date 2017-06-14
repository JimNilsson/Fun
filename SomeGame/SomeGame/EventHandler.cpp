#include "EventHandler.h"
#include <iostream>
void EventHandler::Update()
{
	_mousePressLeft = false;
	_mousePressRight = false;
	for (auto& status : _keyStatus)
	{
		if (status.second & KeyStatus::WAS_PRESSED)
			status.second ^= KeyStatus::WAS_PRESSED;
		if (status.second & KeyStatus::WAS_RELEASED)
			status.second = KeyStatus::NOTHING;
	}
	
	sf::Event ev;
	while (_window->pollEvent(ev))
	{
		if (ev.type == sf::Event::EventType::KeyPressed)
		{
			_keyStatus[ev.key.code] |= KeyStatus::WAS_PRESSED;
			if (_keyStatus[ev.key.code] & KeyStatus::IS_DOWN)
				_keyStatus[ev.key.code] &= ~(KeyStatus::WAS_PRESSED);
			_keyStatus[ev.key.code] |= KeyStatus::IS_DOWN;
		}
		else if (ev.type == sf::Event::EventType::KeyReleased)
		{
			_keyStatus[ev.key.code] = KeyStatus::WAS_RELEASED;
		}
		else if (ev.type == sf::Event::EventType::MouseMoved)
		{
			_mousePos = { (float)ev.mouseMove.x, (float)ev.mouseMove.y };
		}
		else if (ev.type == sf::Event::EventType::MouseButtonPressed)
		{
			_mousePos = { (float)ev.mouseButton.x,(float)ev.mouseButton.y };
			if (ev.mouseButton.button == sf::Mouse::Left)
				_mousePressLeft = true;
			else if (ev.mouseButton.button == sf::Mouse::Right)
				_mousePressRight = true;
			
		}
		else if (ev.type == sf::Event::Closed)
		{
			_close = true;
		}
	}
	
}

bool EventHandler::KeyDown(sf::Keyboard::Key keycode) const
{
	auto& key = _keyStatus.find(keycode);
	if (key == _keyStatus.end())
		return false;
	return key->second & KeyStatus::IS_DOWN;
}

bool EventHandler::KeySinglePress(sf::Keyboard::Key keycode) const
{
	auto& key = _keyStatus.find(keycode);
	if (key == _keyStatus.end())
		return false;
	return key->second & KeyStatus::WAS_PRESSED;
}

bool EventHandler::KeyRelease(sf::Keyboard::Key keycode) const
{
	auto& key = _keyStatus.find(keycode);
	if (key == _keyStatus.end())
		return false;
	return key->second & KeyStatus::WAS_RELEASED;
}

bool EventHandler::WindowClose() const
{
	return _close;
}

sf::Vector2f EventHandler::MousePos() const
{
	return _mousePos;
}

bool EventHandler::LeftMousePress() const
{
	return _mousePressLeft;
}

bool EventHandler::RightMousePress() const
{
	return _mousePressRight;
}
