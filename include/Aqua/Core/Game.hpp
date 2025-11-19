#include "Types.hpp"

namespace Aqua {
class Game {
public:
	Game(const char* title);
	
	Game(const Game& other) = delete;
	Game operator=(const Game& other) = delete;

	~Game();

	virtual void Init();
	
	// Consistent time update.
	virtual void Tick(f32 deltaTime);
	// Fast as possible update.
	virtual void Update(f32 deltaTime);

	void Render();

	virtual void Shutdown();
private:
	const char* title;
};
}
