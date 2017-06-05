#include "MenuState.h"
#include "Application.h"
#include "SnakeGameState.h"

MenuState::MenuState(Application * app) : IState(app)
{
	
	_selections.AddOption("Snake", [this]() {_app->ChangeState(new SnakeState(_app)); });
	_selections.AddOption("Quit", [this]() {_app->Quit(); });
	
}

MenuState::~MenuState()
{
}

void MenuState::Update()
{
	_selections.Update();


}

void MenuState::Draw()
{
	_app->Render(_selections);
}
