#include "MenuState.h"
#include "Application.h"
#include "SnakeGameState.h"
#include "PillPuzzleState.h"
#include "PhysGame.h"

MenuState::MenuState(Application * app) : IState(app)
{
	_selections.SetPosition(_app->View().getSize() / 2.0f);
	_selections.AddOption("Snake", [this]() {_app->ChangeState(new SnakeState(_app)); });
	_selections.AddOption("Pill Puzzle", [this]() {_app->ChangeState(new PillPuzzleState(_app)); });
	_selections.AddOption("Physics Game", [this]() {_app->ChangeState(new PhysGame(_app)); });
	_selections.AddOption("Quit", [this]() {_app->Quit(); });
	_selections.CenterOnPos(true);
	_selections.CenterItems(true);
	
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
