// #include <math.h>
// #include "Ship.h"

// // Ship::Ship(const float x, const float y, const float dx, const float dy, const int size, const float theta) 
// //     : SpaceObject(x, y, dx, dy, size, theta)
// // {
    
// // }

// Ship::~Ship()
// {

// }

// void Ship::SteerLeft(const float time)
// {
//     _theta -= ANGULAR_STEER_SPEED * time;
// }

// void Ship::SteerRight(const float time)
// {
//     _theta += ANGULAR_STEER_SPEED * time;
// }

// void Ship::Thrust(const float acceleration, const float time)
// {
//     _dx += sinf(_theta) * acceleration * time;
//     _dy += -cosf(_theta) * acceleration * time;
// }