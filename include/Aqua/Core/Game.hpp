namespace Aqua {
class Game {
public:
	Game(const char* title);
	
	Game(const Game& other) = delete;
	Game operator=(const Game& other) = delete;

	~Game();

	virtual void Init();
	
	// Consistent time update.
	virtual void Tick();
	// Fast as possible update.
	virtual void Update();

	void Render();

	virtual void Shutdown();
private:
	const char* title;
};
}
