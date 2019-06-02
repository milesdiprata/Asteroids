#include "Asteroid.h"

using namespace std;

Asteroid::Asteroid() : SpaceObject()
{
}

Asteroid::Asteroid(const int screenWidth, const int screenHeight, const int size)
{
    // Random position and velocity asteroid constructor
    X(getRandomInt(0, screenWidth));
    Y(getRandomInt(0, screenHeight));
    Dx((float)getRandomInt(0,15));
    Dy((float)getRandomInt(0,15));
    Size(size);
    Theta(0.0f);

    GenerateWireFrameModel();
}

Asteroid::Asteroid(const float x, const float y, const float dx, const float dy, const int size,
                   const float theta) : SpaceObject(x, y, dx, dy, size, theta)
{
    GenerateWireFrameModel();
}

Asteroid::Asteroid(const Asteroid& asteroid) : SpaceObject(asteroid)
{
}

void Asteroid::GenerateWireFrameModel()
{
    int verts = 25;
    for (int i = 0; i < verts; i++)
    {
        float angle = ((float)i / (float)verts) * 2 * M_PI;
        float noise = getRandomFloat() * 0.5f;
        float radius = 1.0f + noise; // unit circle        
        PushWireFrameCoordinatePair(radius * cosf(angle), radius * sinf(angle));
    }
}

const float Asteroid::getRandomFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

const int Asteroid::getRandomInt(const int min, const int max)
{
    if (max < min)
	{
		cerr << "Error: Max less than min! Cannot generate random number." << endl;
		return INT_MIN;
	}
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}