#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <map>

class EventHandler
{
public:
	EventHandler(sf::RenderWindow* window) : _window(window) {};

	void Update();
	bool KeyDown(sf::Keyboard::Key keycode) const;
	bool KeySinglePress(sf::Keyboard::Key keycode) const;
	bool KeyRelease(sf::Keyboard::Key keycode) const;
	bool WindowClose() const;
	sf::Vector2f MousePos() const;
	bool LeftMousePress() const;

private:
	sf::RenderWindow* _window;

	enum KeyStatus : int32_t
	{
		WAS_PRESSED = 1 << 0,
		IS_DOWN = 1 << 1,
		WAS_RELEASED = 1 << 2,
		NOTHING = 1 << 3
	};

	std::map<sf::Keyboard::Key, int32_t> _keyStatus;
	bool _close = false;
	bool _mousePress = false;
	sf::Vector2f _mousePos;
	
};

#endif
