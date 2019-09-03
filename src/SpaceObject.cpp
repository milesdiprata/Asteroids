#include "SpaceObject.h"

namespace AsteroidsGame
{

SpaceObject::SpaceObject()
{}

SpaceObject::~SpaceObject()
{}

SpaceObject::SpaceObject(const float x, const float y, 
                         const float dx, const float dy, 
                         const int size, const float theta) : _x(x), _y(y),
                                                              _dx(dx), _dy(dy),
                                                              _size(size), _theta(theta) {}

SpaceObject::SpaceObject(const SpaceObject &spaceObject) : _x(spaceObject._x),
                                                           _y(spaceObject._y),
                                                           _dx(spaceObject._dx),
                                                           _dy(spaceObject._dy),
                                                           _size(spaceObject._size),
                                                           _theta(spaceObject._theta),
                                                           _wireFrameCoordinatePairs(spaceObject._wireFrameCoordinatePairs) {}

const float SpaceObject::X() const
{
    return _x;
}

void SpaceObject::X(const float x)
{
    _x = x;
}

const float SpaceObject::Y() const
{
    return _y;
}

void SpaceObject::Y(const float y)
{
    _y = y;
}

const float SpaceObject::Dx() const
{
    return _dx;
}

void SpaceObject::Dx(const float dx)
{
    _dx = dx;
}

const float SpaceObject::Dy() const
{
    return _dy;
}

void SpaceObject::Dy(const float dy)
{
    _dy = dy;
}

const int SpaceObject::Size() const
{
    return _size;
}

void SpaceObject::Size(const int size)
{
    _size = size;
}

const float SpaceObject::Theta() const
{
    return _theta;
}

void SpaceObject::Theta(const float theta)
{
    _theta = theta;
}

const vector<pair<float, float> > SpaceObject::WireFrameCoordinatePairs() const
{
    return _wireFrameCoordinatePairs;
}

void SpaceObject::PushWireFrameCoordinatePair(const float x, const float y)
{
    _wireFrameCoordinatePairs.push_back(std::make_pair(x, y));
}

void SpaceObject::UpdatePosition(const float elapsedTime)
{
    _x += _dx * elapsedTime;
    _y += _dy * elapsedTime;
}

const vector<pair<float, float>> SpaceObject::ApplyTransformations() const
{
    vector<pair<float, float>> transformedCoordinatePairs;
    int numPairs = _wireFrameCoordinatePairs.size();
    transformedCoordinatePairs.resize(numPairs);

    // Rotate
    for (int i = 0; i < numPairs; i++)
    {
        transformedCoordinatePairs[i].first = rotateX(_wireFrameCoordinatePairs[i].first, _wireFrameCoordinatePairs[i].second);
        transformedCoordinatePairs[i].second = rotateY(_wireFrameCoordinatePairs[i].first, _wireFrameCoordinatePairs[i].second);
    }

    // Scale
    for (int i = 0; i < numPairs; i++)
    {
        transformedCoordinatePairs[i].first *= _size;
        transformedCoordinatePairs[i].second *= _size;
    }
    
    // Translate
    for (int i = 0; i < numPairs; i++)
    {
        transformedCoordinatePairs[i].first += _x;
        transformedCoordinatePairs[i].second += _y;
    }

    return transformedCoordinatePairs;
}


const inline float SpaceObject::rotateX(const float initialX, const float initialY) const
{
    return initialX * cosf(_theta) - initialY * sinf(_theta);
}

const inline float SpaceObject::rotateY(const float initialX, const float initialY) const
{
    return initialX * sinf(_theta) + initialY * cosf(_theta);
}

void SpaceObject::GenerateWireFrameModel()
{}

} // namespace AsteroidsGame