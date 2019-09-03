#include "Player.h"

namespace AsteroidsGame
{

Player::Player()
{}

Player::Player(const float x, const float y, 
               const float dx, const float dy, const int size,
               const float theta) : SpaceObject(x, y, dx, dy, size, theta)
{
    GenerateWireFrameModel();
}

Player::Player(const Player &player) : SpaceObject(player)
{}

void Player::GenerateWireFrameModel()
{
    // Player Wireframe
    SpaceObject::PushWireFrameCoordinatePair(0.0f, -5.0f);
    SpaceObject::PushWireFrameCoordinatePair(-2.5f, 2.5f);
    SpaceObject::PushWireFrameCoordinatePair(2.5f, 2.5f);
}

} // namespace AsteroidsGame