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
	
	typedef void(*InitFunc)();
	void SetInitCallback(InitFunc func);

	typedef void(*UpdateFunc)(f32 deltaTime);
	void SetUpdateCallback(UpdateFunc update);

	typedef void(*FixedUpdateFunc)(f32 deltaTime);
	void SetFixedUpdateCallback(FixedUpdateFunc update);

	typedef void(*ShutdownFunc)();
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
