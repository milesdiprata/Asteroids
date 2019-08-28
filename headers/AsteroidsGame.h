#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "GameEngineBase.h"
#include "SpaceObject.h"
#include "Asteroid.h"

using namespace std;

const int MIN_ASTEROID_SIZE = 10;

class Asteroid;
class SpaceObject;

class AsteroidsGame : public GameEngineBase
{
public:
    AsteroidsGame();
    ~AsteroidsGame();

    void WrapCoordinates(SpaceObject* spaceObject);
    void HandleUserInput(const float elapsedTime);
    const bool ShouldDisposeBullet(SpaceObject* bullet);
    void DrawSpaceObject(SpaceObject* spaceObject);
    const bool IsPointInsideCircle(const float circleX, const float circleY, const float circleSize,
                                   const float pointX, const float pointY);
protected:
    virtual void OnUserCreate();
    virtual void OnUserUpdate(const float elaspedTime);
    virtual void DrawPoint(const int x, const int y, const Color color);

private:
    const int getRandomInt(const int min, const int max);
    const float getRandomFloat();
    void removeSpaceObject(vector<SpaceObject*>& vector, SpaceObject*& spaceObj);


    vector<SpaceObject*> _asteroids;
    vector<SpaceObject*> _bullets;
    SpaceObject* _player;
    
    vector<pair<float, float> > _playerModel;
    vector<pair<float, float> > _asteroidModel;
};

#endif // ASTEROIDSGAME_H