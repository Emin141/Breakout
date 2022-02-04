#pragma once
#include <SDL_video.h>
#include <SDL_events.h>

class Window {
public:
	Window();
	void Draw();
	void Poll();
	inline bool isOpen() const { return openStatus; }
private:
	SDL_Window* mWindowPtr;
	//SDL_Event mEvent;
	uint16_t mWidth;
	uint16_t mHeight;
	bool openStatus;
	// Maybe events?
};