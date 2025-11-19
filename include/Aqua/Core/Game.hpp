class Game {
public:
	Game(const char* title);
	
	Game(const Game& other) = delete;
	Game operator=(const Game& other) = delete;

	~Game();

	void Init();

	// Consistent time update.
	void Tick();

	// Fast as possible update.
	void Update();
	void Render();
	void Shutdown();
private:
	const char* title;
};
