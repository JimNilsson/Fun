#include "EventHandler.h"
#include <iostream>
void EventHandler::Update()
{
	_mousePressLeft = false;
	_mousePressRight = false;
	_mouseMove = false;
	_resize = false;
	_close = false;
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
			_mousePos = _window->mapPixelToCoords({ ev.mouseMove.x, ev.mouseMove.y });
			_mouseMove = true;
		}
		else if (ev.type == sf::Event::EventType::MouseButtonPressed)
		{
			_mousePos = _window->mapPixelToCoords( {ev.mouseButton.x,ev.mouseButton.y });
			if (ev.mouseButton.button == sf::Mouse::Left)
				_mousePressLeft = true;
			else if (ev.mouseButton.button == sf::Mouse::Right)
				_mousePressRight = true;
			
		}
		else if (ev.type == sf::Event::Closed)
		{
			_close = true;
		}
		else if (ev.type == sf::Event::Resized)
		{
			sf::View v = _window->getView();
			v.setSize({ (float)ev.size.width, (float)ev.size.height });
			_window->setView(v);
			_resize = true;
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

bool EventHandler::Resized() const
{
	return _resize;
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

bool EventHandler::MouseMoved() const
{
	return _mouseMove;
}
