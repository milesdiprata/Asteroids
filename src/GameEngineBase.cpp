#include "GameEngineBase.h"

namespace GameEngineBase
{

GameEngineBase::GameEngineBase()
{
    _renderer = nullptr;
	_window = nullptr;
    _screenHeight = INT_MIN;
    _screenWidth = INT_MIN;
}

GameEngineBase::~GameEngineBase()
{
    SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = nullptr;
	_window = nullptr;
	SDL_Quit();
}

const int GameEngineBase::GetScreenWidth() const
{
    return _screenWidth;
}

const int GameEngineBase::GetScreenHeight() const
{
    return _screenHeight;
}

void GameEngineBase::InitalizeGraphics(const char *const windowTitle, const int width, const int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Error initalizing SDL! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

    if (width > 0 && height > 0)
    {
        _screenWidth = width;
        _screenHeight = height;
        _window = SDL_CreateWindow(windowTitle, 
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, 
                                   _screenWidth, 
                                   _screenHeight, 
                                   SDL_WINDOW_SHOWN);
    }
    else
    {
        std::cerr << "Error: invalid screen dimensions!" << std::endl;
        return;
    }
	
	if (_window == nullptr)
	{
		std::cerr << "Error creating the SDL window! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
	{
		std::cerr << "Error creating the SDL renderer! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
}

void GameEngineBase::ClearScreen()
{
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF); // Background Color
	SDL_RenderClear(_renderer);
}

void GameEngineBase::UpdateScreen()
{
	SDL_RenderPresent(_renderer);
}

void GameEngineBase::SetRendererColor(const Color color)
{
    switch (color)
    {
	case RED:
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
		break;
	case BLUE:
		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, 0xFF);
		break;
	case GREEN:
		SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0x00, 0xFF);
		break;
    case WHITE:
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}

void GameEngineBase::DrawPoint(const int x, const int y, const Color color)
{
	SetRendererColor(color);
	SDL_RenderDrawPoint(_renderer, x, y);
}

void GameEngineBase::DrawLine(const int x1, const int y1, const int x2, const int y2, 
                              const Color color)
{
    SetRendererColor(color);

    // Drawing lines with Bresenham's Line Algorithm
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }
        DrawPoint(x, y, color);
        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
            {
                px = px + 2 * dy1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y = y + 1;
                }
                else
                {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            DrawPoint(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }
        DrawPoint(x, y, color);
        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
            {
                py = py + 2 * dx1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x = x + 1;
                }
                else
                {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            DrawPoint(x, y, color);
        }
    }
}

void GameEngineBase::DrawRectangle(const int x, const int y, const int width, const int height,                                      const Color color)
{
	SDL_Rect fillArea = { x, y, width, height };
    SetRendererColor(color);
	SDL_RenderFillRect(_renderer, &fillArea);
}

const Uint8 *GameEngineBase::GetKeyState() const
{
    const Uint8 * keyState = SDL_GetKeyboardState(nullptr);
    
    if (keyState != nullptr)
        return keyState;

    return nullptr;
}

const bool GameEngineBase::HasUserQuit() const
{
	SDL_Event e;
	if (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			return true;

	return false;
}

void GameEngineBase::Start(const int fps)
{
    float beforeFrameTime;
    float afterFrameTime;

    OnUserCreate();

    while (!HasUserQuit())
    {
        // Get time before frame
        beforeFrameTime = (float)SDL_GetTicks();

        // Regulate FPS; not using SDL_Delay due to bad accuracy
        while (SDL_GetTicks() - beforeFrameTime < 1000.0f / fps)
        {}

        // Get time after frame
        afterFrameTime = (float)SDL_GetTicks();

        // Do game logic and render, passing in time elapsed rendering the frame
        float deltaFrameTime = (afterFrameTime - beforeFrameTime) / 1000.0f;
        ClearScreen();
        OnUserUpdate(deltaFrameTime);
        UpdateScreen();
    }
}

void GameEngineBase::OnUserCreate()
{}

void GameEngineBase::OnUserUpdate(const float elaspedTime)
{}

} // namespace GameEngineBase