//
//  main.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/9/20.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "3DMath.h"

class line3D
{
public:
    Vector3 origin;
    Vector3 end;
    
    // other memebers
};

class Ray3D
{
public:
    Vector3 rayOrigin;
    Vector3 rayDelta;
};

class Sphere
{
public:
    Vector3 center;
    float Radius;
};

// 计算最佳平面，使得数组中尽可能多的点落在平面上
// Calc the normal of best fit plane make sure most points are in the plane
Vector3 CalcBestFitNormal (const Vector3 a[], int n)
{
    Vector3 result = kZeroVector;
    
    const Vector3* p = &a[n - 1];
    
    for (int i = 0; i < n; i++)
    {
        const Vector3 *c = &a[i];
        
        result.x += (p->z + c->z) * (p->y - c->y);
        result.y += (p->x + c->x) * (p->z - c->z);
        result.z += (p->y + c->y) * (p->x - c->x);
        
        p = c;
    }
    
    result.normalize();
    
    return result;
}

int main(int argc, const char * argv[])
{
    Matrix3x3 m;
    
    m.m11 = 10;
    m.m22 = 20;
    m.m33 = 30;
    
    m.print ();
    inverse (m).print ();
    
    return 0;
}
