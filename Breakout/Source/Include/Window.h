#pragma once
#include <SDL_video.h>
#include <SDL_events.h>

enum class GameState {
	LOADING = 0,
	MENU,
	LEVEL,
	GAMEOVER,
	NOT_RUNNING
};

class Window {
public:
	Window();
	~Window();
	void Draw();
	void Poll();
	inline GameState getGameState() const {
		return mWindowState;
	}
private:
	SDL_Window* mWindowPtr;
	SDL_Surface* mSurfacePtr;
	uint16_t mWidth;
	uint16_t mHeight;

	GameState mWindowState;
	// Scenes
	// Maybe events enum?
};