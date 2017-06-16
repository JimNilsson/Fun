#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "IState.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "EventHandler.h"
#include <vector>

class Application
{
public:
	static Application* GetInstance();
	static void Shutdown();

	void Init();
	void ChangeState(IState* state);
	void PushState(IState* state);
	void PopState();
	bool Running();
	void Quit();

	void Update();
	void Draw();
	sf::View& View();

	void Render(sf::Drawable& d);

	uint32_t Width() const;
	uint32_t Height() const;

	TextureManager* Textures();
	FontManager* Fonts();
	EventHandler* Events();
	

private:
	Application();
	~Application();
	sf::RenderWindow _window;
	sf::View _view;
	std::vector<IState*> _states;
	IState* _pendingStateChange = nullptr;
	bool _pendingPop = false;

	static Application* _instance;

	TextureManager* _textureManager = nullptr;
	FontManager* _fontManager = nullptr;
	EventHandler* _eventHandler = nullptr;

	uint32_t _width;
	uint32_t _height;

	bool _running;
	

};


#endif

