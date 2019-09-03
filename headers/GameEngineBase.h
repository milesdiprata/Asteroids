#ifndef GAMEENGINEBASE_H
#define GAMEENGINEBASE_H

// #pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace GameEngineBase
{

static constexpr int FRAMES_PER_SECOND = 60;

class GameEngineBase
{
public:

	enum Color { RED, BLUE, GREEN, WHITE };

    GameEngineBase();
    ~GameEngineBase();

	void InitalizeGraphics(const char *windowTitle, const int width, const int height);	
	const Uint8 *GetKeyState() const;	
	void DrawLine(const int x1, const int y1, const int x2, const int y2, const Color color);
	void DrawRectangle(const int x, const int y, const int width, const int height, 
					   const Color color);
    void Start(const int fps = FRAMES_PER_SECOND);
	const int GetScreenWidth() const;
	const int GetScreenHeight() const;

protected:
	virtual void DrawPoint(const int x, const int y, const Color color);	
    virtual void OnUserCreate();
    virtual void OnUserUpdate(const float elapsedTime);
	
private:
    SDL_Window *_window;
	SDL_Renderer *_renderer;

	int _screenWidth;
	int _screenHeight;

	const bool HasUserQuit() const;
	void ClearScreen();
	void UpdateScreen();
    void SetRendererColor(const Color color);
};

} // namespace GameEngineBase

#endif // GAMEENGINE_H