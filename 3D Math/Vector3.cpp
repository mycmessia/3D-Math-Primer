//
//  Vector3.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/9/20.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef __VECTOR3_H_INCLUDED__
#define __VECTOR3_H_INCLUDED__

#include "3DMath.h"

void Vector3::print ()
{
    std::cout << "x:\t" << to_zero (x) << "\ty:\t" << to_zero (y) << "\tz:\t" << to_zero (z) << std::endl;
}

Vector3 Vector3::operator - () const
{
    return Vector3 (-x, -y, -z);
}

Vector3 Vector3::operator * (float a) const
{
    return Vector3 (a * x, a * y, a * z);
}

Vector3 Vector3::operator *= (float a)
{
    x *= a; y *= a; z *= a;
    return *this;
}

Vector3 Vector3::operator / (float a) const
{
    float n = 1.0f / a;
    
    return Vector3 (n * x, n * y, n * z);
}

Vector3 Vector3::operator /= (float a)
{
    float n = 1.0f / a;
    x *= n; y *= n; z *= n;
    return *this;
}

void Vector3::normalize ()
{
    float magSq = x*x + y*y + z*z;
    if (magSq > 0.0f)
    {
        float n = 1.0f / sqrt (magSq);
        x *= n;
        y *= n;
        z *= n;
    }
}

Vector3 Vector3::operator + (Vector3 v) const
{
    return Vector3 (x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator += (Vector3 v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    
    return *this;
}

Vector3 Vector3::operator - (Vector3 v) const
{
    return Vector3 (x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator -= (Vector3 v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

float Vector3::operator * (const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

#endif
