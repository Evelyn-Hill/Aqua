#include <Aqua/Core/Game.hpp>

namespace Aqua {
Game::Game(const char* title) {
	this->title = title;
}

Game::~Game() {
	Shutdown();
}

void Game::Render() {

}

}
