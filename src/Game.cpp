#include <Aqua/Core/Game.hpp>
#include <chrono>


namespace Aqua {
Game::Game(const char* title) {
	this->title = title;
	gameWindow = new Window(1176, 768, title);

	deltaTime = 0;
	fixedDelta = 0;
	fixedAccumulator = 0;
}

Game::~Game() {
	Game::Shutdown();
}

void Game::Init() {};
void Game::Update(f64 deltaTime) {};
void Game::FixedUpdate(f64 deltaTime) {};
void Game::Shutdown() {};

void Game::Run() {
	using Clock = std::chrono::high_resolution_clock;
	
	auto lastFrameTime = Clock::now();
	auto lastFixedTime = Clock::now();


	while (!gameWindow->ShouldClose()) {
		// Handle Delta Time and Fixed Update Loop.
		auto currentTime = Clock::now();
		deltaTime = std::chrono::duration<f64>(currentTime - lastFrameTime).count();

		lastFrameTime = currentTime;
		fixedAccumulator -= deltaTime;

		Update(deltaTime);

		if (fixedAccumulator <= 0) {
			fixedDelta = std::chrono::duration<f64>(currentTime - lastFixedTime).count();
			lastFixedTime = currentTime;
			fixedAccumulator = fixedUpdateTime;
			FixedUpdate(fixedDelta);
		}

		gameWindow->PollEvents();
		Render();
	}
}

void Game::Render() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gameWindow->SwapBuffers();
}

}
