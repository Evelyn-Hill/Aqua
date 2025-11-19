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
	virtual void Update(f64 deltaTime);
	virtual void FixedUpdate(f64 deltaTime);
	virtual void Shutdown();

	void Render();

private:
	const char* title;
	Window* gameWindow = {};
		
	f64 deltaTime= {};
	f64 fixedDelta = {};

	const f64 fixedUpdateTime = 1.0 / 60;
	f64 fixedAccumulator = {};

};
}
