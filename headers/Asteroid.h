#ifndef ASTEROID_H
#define ASTEROID_H

#include "SpaceObject.h"

class Asteroid : public SpaceObject
{
public: 
    Asteroid();
    Asteroid(const int maxXSpawn, const int maxYSpawn, const int size);
    Asteroid(const float x, const float y, const float dx, const float dy, const int size,
             const float theta);
    Asteroid(const Asteroid& asteroid);
    ~Asteroid();

protected:
    virtual void GenerateWireFrameModel();

private:
    const inline float getRandomFloat() const;
    const inline int getRandomInt(const int min, const int max) const;


};

#endif // ASTEROID_H