#include "AsteroidsGame.h"

namespace AsteroidsGame
{

AsteroidsGame::AsteroidsGame()
{}

AsteroidsGame::~AsteroidsGame()
{
    // delete _player;

    // for (auto &a : _asteroids)
    //     delete a;
    // for (auto &b : _bullets)
    //     delete b;
}

void AsteroidsGame::WrapCoordinates(SpaceObject *spaceObject)
{
    if (spaceObject->X() < 0.0f)
        spaceObject->X(spaceObject->X() + (float)GetScreenWidth());
    if (spaceObject->X() > (float)GetScreenWidth())
        spaceObject->X(spaceObject->X() - (float)GetScreenWidth());
    if (spaceObject->Y() < 0.0f)
        spaceObject->Y(spaceObject->Y() + (float)GetScreenHeight());
    if (spaceObject->Y() > (float)GetScreenHeight())
        spaceObject->Y(spaceObject->Y() - (float)GetScreenHeight());
}

void AsteroidsGame::DrawPoint(const int x, const int y, const GameEngineBase::Color color)
{
    // float newX, newY;
    // WrapCoordinates(x, y, newX, newY);
    GameEngineBase::DrawPoint(x, y, color);
}

void AsteroidsGame::OnUserCreate()
{
    srand(time(NULL));
    
    // Create player
    _player = new Player(GetScreenWidth() / 2.0f, 
                         GetScreenHeight() / 2.0f,
                         0.0f, 0.0f, 5, 0.0f);
    
    // Create asteroids
    for (int i = 0; i < 5; i++)
        _asteroids.push_back(new Asteroid(GetScreenWidth(), GetScreenHeight(), 30));
}

void AsteroidsGame::HandleUserInput(const float elapsedTime)
{
    const Uint8 *keyState = GetKeyState();
    SDL_Event e;
    
    // Steer
    if (keyState[SDL_SCANCODE_LEFT])
    {
        _player->Theta(_player->Theta() - 5.0f * elapsedTime);
    }
    if (keyState[SDL_SCANCODE_RIGHT])
    {
        _player->Theta(_player->Theta() + 5.0f * elapsedTime);
    }
    // Thrust
    if (keyState[SDL_SCANCODE_UP])
    {
        // Acceleration
        _player->Dx(_player->Dx() + sinf(_player->Theta()) * 150.0f * elapsedTime);
        _player->Dy(_player->Dy() - cosf(_player->Theta()) * 150.0f * elapsedTime) ;
    }
    // Create bullet entity
    if (keyState[SDL_SCANCODE_SPACE] && SDL_PollEvent(&e) && e.type == SDL_KEYUP)
    {
        SpaceObject* newBullet = new SpaceObject(_player->X() + (15.0f * sinf(_player->Theta())), 
                                                 _player->Y() + (15.0f * -cosf(_player->Theta())),200.0f * sinf(_player->Theta()),
                                                 200.0f * -cosf(_player->Theta()), 
                                                 1,
                                                 0.0f);
        for (int i = 0; i < 25; i++)
        {
            float angle = ((float)i / (float)25) * 2 * M_PI;
            float radius = 1.0f; // unit circle        
            newBullet->PushWireFrameCoordinatePair(radius * cosf(angle), radius * sinf(angle));
        }
        _bullets.push_back(newBullet);
    }


}

const inline bool AsteroidsGame::ShouldDisposeBullet(SpaceObject *bullet) const
{
    return bullet != nullptr && 
        (bullet->X() < 1 || bullet->X() > GetScreenWidth() 
            || bullet->Y() < 1 || bullet->Y() > GetScreenHeight());
}


void AsteroidsGame::OnUserUpdate(const float elapsedTime)
{
    HandleUserInput(elapsedTime);

    // Update player position
    _player->UpdatePosition(elapsedTime);
    WrapCoordinates(_player);
    DrawSpaceObject(_player);

    // Update and draw asteroids
    for (auto &a : _asteroids)
    {
        a->UpdatePosition(elapsedTime);
        WrapCoordinates(a);
        DrawSpaceObject(a);
    }

    vector<Asteroid*> newAsteroids;

    // Update and draw bullets
    for (auto &b : _bullets)
    {
        b->UpdatePosition(elapsedTime);

        // Remove off-screen bullets
        if (!ShouldDisposeBullet(b))
            DrawSpaceObject(b);
        else
            removeSpaceObject(_bullets, b);
        
        // Check for bullet collision with asteroids
        for (auto &a : _asteroids)
        {
            if (IsPointInsideCircle(a->X(), a->Y(), a->Size(), b->X(), b->Y()))
            {
                removeSpaceObject(_bullets, b);
                
                // Create smaller asteroids
                if (a->Size() > MIN_ASTEROID_SIZE)
                {
                    float randAngle = getRandomFloat() * 2 * M_PI;
                    Asteroid* firstAsteroidChild = new Asteroid(a->X(), a->Y(), 
                        10.0f * sinf(randAngle), 10.0f * cosf(randAngle), a->Size() / 2, 0.0f);
                    randAngle = getRandomFloat() * 2 * M_PI;
                    Asteroid* secondAsteroidChild = new Asteroid(a->X(), a->Y(), 
                        10.0f * sinf(randAngle), 10.0f * cosf(randAngle), a->Size() / 2, 0.0f);
                    newAsteroids.push_back(firstAsteroidChild);
                    newAsteroids.push_back(secondAsteroidChild);


                    
                }
                removeSpaceObject(_asteroids, a);
            }
        }

        if (newAsteroids.size() > 0)
            for (auto &a : newAsteroids)
                _asteroids.push_back(new Asteroid(*(a)));

    }





}

void AsteroidsGame::DrawSpaceObject(SpaceObject *spaceObject)
{
    vector<pair<float, float>> transformedModel = spaceObject->ApplyTransformations();
    int numPairs = transformedModel.size();

    // Draw closed polygon
    for (int i = 0; i < numPairs; i++)
    {
        int j = i + 1;
        GameEngineBase::DrawLine(transformedModel[i % numPairs].first,
                                 transformedModel[i % numPairs].second,
                                 transformedModel[j % numPairs].first,
                                 transformedModel[j % numPairs].second,
                                 GameEngineBase::Color::WHITE);
    }
}

const inline  bool AsteroidsGame::IsPointInsideCircle(const float circleX, const float circleY, 
                                                      const float circleSize, const float pointX,
                                                      const float pointY) const
{
    return sqrtf( ((pointX - circleX) * (pointX - circleX)) + 
                  ((pointY - circleY) * (pointY - circleY)) ) < circleSize;
}

const inline int AsteroidsGame::getRandomInt(const int min, const int max) const
{
    if (max < min)
	{
		std::cerr << "Error: Max less than min! Cannot generate random number." << std::endl;
		return INT_MIN;
	}
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

const inline float AsteroidsGame::getRandomFloat() const
{
    return (float)rand() / (float)RAND_MAX;
}

void AsteroidsGame::removeSpaceObject(vector<SpaceObject*> &vector, const SpaceObject *spaceObj)
{
    vector.erase(remove(vector.begin(), vector.end(), spaceObj), vector.end());
}

} // namespace AsteroidsGame