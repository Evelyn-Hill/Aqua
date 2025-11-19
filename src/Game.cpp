#include <Aqua/Core/Game.hpp>


namespace Aqua {
Game::Game(const char* title) {
	this->title = title;

	Log::InitLog(title);
	Log::AquaLog()->Info("Game Initialized");
	
	gameWindow = new Window(1176, 768, title);
}

Game::~Game() {
	Log::AquaLog()->Info("Destroying Game!");
}

void Game::Run() {
	while (!gameWindow->ShouldClose()) {
		//TODO: FixedUpdate 
		Update(0.0);
		Render();
	

		gameWindow->PollEvents();
	}
}

void Game::Render() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gameWindow->SwapBuffers();
}

void Game::SetInitCallback(InitFunc func) {
	Init = func;
}

void Game::SetUpdateCallback(UpdateFunc func) {
	Update = func;
}

void Game::SetFixedUpdateCallback(FixedUpdateFunc func) {
	FixedUpdate = func;
}

void Game::SetShutdownCallback(ShutdownFunc func) {
	Shutdown = func;
}

}
