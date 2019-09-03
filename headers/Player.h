#ifndef PLAYER_H
#define PLAYER_H

#include "SpaceObject.h"

namespace AsteroidsGame
{

static constexpr float ANGULAR_STEER_SPEED = 5.0f;

class Player : public SpaceObject
{

public:

    Player();
    Player(const float x, const float y, const float dx, const float dy, const int size,
           const float theta);
    Player(const Player &player);
    ~Player();

    void SteerLeft(const float time);
    void SteerRight(const float time);
    void Thrust(const float acceleration, const float time);

protected:
    virtual void GenerateWireFrameModel();

private:
};

} // namespace AsteroidsGame

#endif // PLAYER_H