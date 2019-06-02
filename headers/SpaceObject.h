#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <iostream>
#include <limits>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

class SpaceObject
{
public:
    SpaceObject();
    SpaceObject(const float x, const float y, const float dx, const float dy, const int size,
                const float theta);
    SpaceObject(const SpaceObject &spaceObject);
    ~SpaceObject();

    const float X();
    void X(const float x);
    const float Y();
    void Y(const float y);
    const float Dx();
    void Dx(const float dx);
    const float Dy();
    void Dy(const float dy);
    const int Size();
    void Size(const int size);
    const float Theta();
    void Theta(const float theta);

    const vector<pair<float, float> > WireFrameCoordinatePairs();
    void PushWireFrameCoordinatePair(const float x, const float y);
    void GenerateUnitCircleWireFrame(bool shouldUseNoise = false);

    void UpdatePosition(const float elapsedTime);
    const vector<pair<float, float> > ApplyTransformations();
    

protected:
    virtual void GenerateWireFrameModel();
    
private:
    float _x;
    float _y;
    float _dx;
    float _dy;
    int _size;
    float _theta;

    vector<pair<float, float> > _wireFrameCoordinatePairs;

    const float rotateX(const float initialX, const float initialY);
    const float rotateY(const float initialX, const float initialY);


};

#endif // SPACEOBJECT_H