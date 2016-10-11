//
//  Vector3.hpp
//  3D Math
//
//  Created by 梅宇宸 on 16/9/20.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <cmath>
#include <iostream>

#include "MathUtil.h"

class Vector3
{
public:
    float x, y, z;
    
    Vector3 () {}
    Vector3 (const Vector3 &a) : x (a.x), y (a.y), z (a.z) {}
    Vector3 (float nx, float ny, float nz) : x (nx), y (ny), z (nz) {}
    
    void zero () { x = y = z = 0.0f; }
    
    Vector3 operator - () const;
    
    Vector3 operator * (float a) const;
    
    Vector3 operator *= (float a);
    
    Vector3 operator / (float a) const;
    
    Vector3 operator /= (float a);
    
    Vector3 operator + (Vector3 v) const;
    
    Vector3 operator += (Vector3 v);
    
    Vector3 operator - (Vector3 v) const;
    
    Vector3 operator -= (Vector3 v);
    
    float operator * (const Vector3 &a) const;
    
    void normalize ();
    
    void print ();
};

inline float vectorMag (const Vector3 &a)
{
    return sqrt (a.x * a.x + a.y * a.y + a.z * a.z);
}

// Must define a non-member function to do left *
inline Vector3 operator * (float k, const Vector3 v)
{
    return Vector3 (k * v.x, k * v.y, k * v.z);
}

inline float distance (const Vector3 v1, const Vector3 v2)
{
    return vectorMag(v1 - v2);
}

inline double calcAngle (const Vector3 v1, const Vector3 v2)
{
    double dp = v1 * v2;
    
    return acos(dp / (vectorMag(v1) * vectorMag(v2))) * 180.0 / 3.14;
}

inline Vector3 crossProduct (const Vector3 &v1, const Vector3 &v2)
{
    return Vector3 (
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

#endif /* Vector3_hpp */
