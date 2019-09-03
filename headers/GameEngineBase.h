#ifndef GAMEENGINEBASE_H
#define GAMEENGINEBASE_H

// #pragma once

#include <SDL2/SDL.h>

const int FRAMES_PER_SECOND = 60;

enum Color { RED, BLUE, GREEN, BLACK, WHITE };

class GameEngineBase
{
public:
    GameEngineBase();
    ~GameEngineBase();

	void InitalizeGraphics(const char *windowTitle, const int width, const int height);	
						   const Uint8 * GetKeyState();	
	void DrawLine(const int x1, const int y1, const int x2, const int y2, const Color color);
	void DrawRectangle(const int x, const int y, const int width, const int height, 
					   const Color color);
    void Start();
	int GetScreenWidth();
	int GetScreenHeight();

protected:
	virtual void DrawPoint(const int x, const int y, const Color color);	
    virtual void OnUserCreate();
    virtual void OnUserUpdate(const float elapsedTime);
	
private:
    SDL_Window * _window;
	SDL_Renderer * _renderer;

	int _screenWidth;
	int _screenHeight;

	bool HasUserQuit();
	void ClearScreen();
	void UpdateScreen();
    void SetRendererColor(const Color color);
};

#endif // GAMEENGINE_H