#pragma once
#include "Types.hpp"
#include <Aqua/Core/Log.hpp>
#include <Aqua/Core/Window.hpp>
#include <Aqua/Core/Renderer.hpp>
#include <Aqua/Core/AssetManager.hpp>

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

	virtual void Render();

protected:
	const char* title = {};
	Window* gameWindow = {};
	Renderer* renderer = {};
	AssetManager* assetManager = {};

	f64 deltaTime= {};
	f64 fixedDelta = {};
	f64 time = {};
private:
	const f64 fixedUpdateTime = 1.0 / 60;
	f64 fixedAccumulator = {};
	void GlErrorLoop();
};
}
