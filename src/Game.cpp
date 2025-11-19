#include <Aqua/Core/Game.hpp>


namespace Aqua {
Game::Game(const char* title) {
	this->title = title;
	aqLog = new Log("Aqua");
	gLog = new Log(title);
	gameWindow = new Window(1176, 768, title);
}

Game::~Game() {
	Game::Shutdown();
}

void Game::Init() {};
void Game::Update(f32 deltaTime) {};
void Game::FixedUpdate(f32 deltaTime) {};
void Game::Shutdown() {};

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

}
