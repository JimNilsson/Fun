#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "IState.h"
#include "SelectionList.h"

class MenuState : public IState
{
public:
	MenuState(Application* app);
	~MenuState();

	virtual void Update();
	virtual void Draw();

private:
	SelectionList _selections;
};

#endif
