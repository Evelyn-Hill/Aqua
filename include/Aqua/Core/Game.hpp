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
	
	typedef std::function<void()> InitFunc;
	void SetInitCallback(InitFunc func);

	typedef std::function<void(f32 deltaTime)> UpdateFunc;
	void SetUpdateCallback(UpdateFunc update);

	typedef std::function<void(f32 deltaTime)> FixedUpdateFunc;
	void SetFixedUpdateCallback(FixedUpdateFunc update);

	typedef std::function<void()> ShutdownFunc;
	void SetShutdownCallback(ShutdownFunc update);

	void Render();

private:
	const char* title;
	Window* gameWindow;

	InitFunc Init;
	UpdateFunc Update;
	FixedUpdateFunc FixedUpdate;
	ShutdownFunc Shutdown;
};
}
