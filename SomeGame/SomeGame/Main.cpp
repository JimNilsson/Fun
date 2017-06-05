
#include "Application.h"
#include <crtdbg.h>
#include <random>
int main()
{
	srand(time(NULL));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = Application::GetInstance();

	while (app->Running())
	{
		app->Update();
		app->Draw();

	}

	Application::Shutdown();
	return 0;
}