#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <iostream>
#include <limits>
#include <vector>
#include <math.h>

using std::vector;
using std::pair;

namespace AsteroidsGame
{

class SpaceObject
{
public:
    SpaceObject();
    SpaceObject(const float x, const float y, const float dx, const float dy, const int size,
                const float theta);
    SpaceObject(const SpaceObject &spaceObject);
    ~SpaceObject();

    const float X() const;
    void X(const float x);

    const float Y() const;
    void Y(const float y);

    const float Dx() const;
    void Dx(const float dx);

    const float Dy() const;
    void Dy(const float dy);

    const int Size() const;
    void Size(const int size);
    
    const float Theta() const;
    void Theta(const float theta);

    const vector<pair<float, float> > WireFrameCoordinatePairs() const;

    void PushWireFrameCoordinatePair(const float x, const float y);

    void GenerateUnitCircleWireFrame(bool shouldUseNoise = false);

    void UpdatePosition(const float elapsedTime);

    const vector<pair<float, float> > ApplyTransformations()  const;
    

protected:
    virtual void GenerateWireFrameModel();
    

private:
    float _x;
    float _y;
    float _dx;
    float _dy;
    int _size;
    float _theta;

    vector<pair<float, float>> _wireFrameCoordinatePairs;

    const inline float rotateX(const float initialX, const float initialY) const;
    const inline float rotateY(const float initialX, const float initialY) const;


};

} // namespace AsteroidsGame

#endif // SPACEOBJECT_H