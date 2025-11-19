#pragma once
#include "Types.hpp"
#include <Aqua/Core/Log.hpp>
#include <Aqua/Core/Window.hpp>

namespace Aqua {
class Game {
public:
	Game(const char* title);
	
	Game(const Game& other) = delete;
	Game operator=(const Game& other) = delete;

	~Game();

	void Run();

	virtual void Init();

	virtual void Update(f32 deltaTime);
	virtual void FixedUpdate(f32 deltaTime);

	virtual void Shutdown();

	void Render();

private:
	const char* title;
	Window* gameWindow;
};
}
