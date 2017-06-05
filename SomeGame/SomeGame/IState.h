#ifndef _I_STATE_H_
#define _I_STATE_H_
#include <SFML\Graphics.hpp>
class Application;
class IState
{
protected:
	Application* _app;
	
public:
	IState(Application* app) : _app(app) {};
	virtual ~IState() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	
};

#endif
