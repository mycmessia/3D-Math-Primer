//
//  Quaternion.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/19.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "Quaternion.hpp"
#include "MathUtil.h"
#include <assert.h>


const Quaternion kQuaternionIdentity = { 1.0F, 0.0F, 0.0F, 0.0F };

void Quaternion::setRotationX (float theta)
{
    float thetaOver2 = theta * 0.5f;
    
    w = cos (thetaOver2);
    x = sin (thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

void Quaternion::setRotationY (float theta)
{
    float thetaOver2 = theta * 0.5f;
    
    w = cos (thetaOver2);
    x = 0.0f;
    y = sin (thetaOver2);
    z = 0.0f;
}

void Quaternion::setRotationZ (float theta)
{
    float thetaOver2 = theta * 0.5f;
    
    w = cos (thetaOver2);
    x = 0.0f;
    y = 0.0f;
    z = sin (thetaOver2);
}

void Quaternion::setRotationAxis (const Vector3 &axis, float theta)
{
    assert((vectorMag(axis) - 1.0f) < 0.01f);
    
    float thetaOver2 = theta * 0.5f;
    float sinThetaOver2 = sin (thetaOver2);
    
    w = cos (thetaOver2);
    x = axis.x * sinThetaOver2;
    y = axis.y * sinThetaOver2;
    z = axis.z * sinThetaOver2;
}

float Quaternion::getRotationAngle () const
{
    float thetaOver2 = safeAcos (w);
    
    return thetaOver2 * 2.0f;
}

Vector3 Quaternion::getRotationAxis() const
{
    float sinThetaOver2Sq = 1.0f - w * w;
    
    float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
    
    float nx = x * oneOverSinThetaOver2;
    float ny = y * oneOverSinThetaOver2;
    float nz = z * oneOverSinThetaOver2;
    
    return Vector3 (nx, ny, nz);
}
