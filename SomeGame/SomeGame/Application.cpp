#include "Application.h"
#include "MenuState.h"
#include <iostream>

Application* Application::_instance = nullptr;

Application* Application::GetInstance()
{
	if (!_instance)
	{
		_instance = new Application();
		_instance->Init();
	}
	return _instance;
}

void Application::Shutdown()
{

	delete _instance;
}

void Application::Init()
{
	_width = 800;
	_height = 640;
	_window.create(sf::VideoMode(_width, _height), "Some Game");
	_view = _window.getView();
	_eventHandler = new EventHandler(&_window);
	_textureManager = new TextureManager();
	_fontManager = new FontManager();
	_running = true;
	ChangeState(new MenuState(_instance));
}

void Application::ChangeState(IState * state)
{
	if(!_pendingStateChange)
		_pendingStateChange = state;

	
}

void Application::PushState(IState * state)
{
	_states.push_back(state);
}

void Application::PopState()
{
	//Disallow pop if there's only one state on the stack
	if(_states.size() > 1)
		_pendingPop = true;
}

bool Application::Running()
{
	return _running;
}

void Application::Quit()
{
	_running = false;
	
}

void Application::Update()
{
	if (_pendingPop)
	{
		delete _states.back();
		_states.pop_back();
	}
	if (_pendingStateChange)
	{
		for (auto& state : _states)
			delete state;
		_states.clear();
		_states.push_back(_pendingStateChange);
		_pendingStateChange = nullptr;
		_view = _window.getDefaultView();
	}
	_eventHandler->Update();
	if (_eventHandler->WindowClose())
		Quit();
	if (_eventHandler->Resized())
		_view = _window.getView();
	_states.back()->Update();
}

void Application::Draw()
{
	_window.setView(_view);
	_states.back()->Draw();
	_window.display();
	_window.clear();
}

sf::View & Application::View()
{
	return _view;
}

void Application::Render(sf::Drawable & d)
{
	_window.draw(d);
}

uint32_t Application::Width() const
{
	return _width;;
}

uint32_t Application::Height() const
{
	return _height;
}

TextureManager * Application::Textures()
{
	return _textureManager;
}

FontManager * Application::Fonts()
{
	return _fontManager;
}

EventHandler * Application::Events()
{
	return _eventHandler;
}

Application::Application()
{
	
	
	
}

Application::~Application()
{
	_window.close();
	delete _eventHandler;
	delete _textureManager;
	delete _fontManager;
	for (auto& state : _states)
		delete state;
}
