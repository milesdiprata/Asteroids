#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H

#include <algorithm>
#include "GameEngineBase.h"
#include "Asteroid.h"
#include "Player.h"

namespace AsteroidsGame
{

static constexpr int MIN_ASTEROID_SIZE = 10;

class AsteroidsGame : public GameEngineBase::GameEngineBase
{
public:
    AsteroidsGame();
    ~AsteroidsGame();

    void WrapCoordinates(SpaceObject *spaceObject);
    void HandleUserInput(const float elapsedTime);
    const inline bool ShouldDisposeBullet(SpaceObject *const bullet) const;
    void DrawSpaceObject(SpaceObject *const spaceObject);
    const inline bool IsPointInsideCircle(const float circleX, const float circleY, const float circleSize,
                                          const float pointX, const float pointY) const;
protected:
    virtual void OnUserCreate();
    virtual void OnUserUpdate(const float elaspedTime);
    virtual void DrawPoint(const int x, const int y, const GameEngineBase::Color color);

private:
    const inline int getRandomInt(const int min, const int max) const;
    const inline float getRandomFloat() const;
    inline void removeSpaceObject(vector<SpaceObject*> &vector, const SpaceObject *const spaceObj);


    vector<SpaceObject*> _asteroids;
    vector<SpaceObject*> _bullets;
    Player *_player;
};

} // namespace AsteroidsGame

#endif // ASTEROIDSGAME_H