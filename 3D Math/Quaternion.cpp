//
//  Quaternion.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/19.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "3DMath.h"


const Quaternion kQuaternionIdentity = Quaternion (1.0F, 0.0F, 0.0F, 0.0F);

Quaternion::Quaternion (float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion (const EulerAngle& orientation, TransType transType)
{
    float sp, sb, sh;
    float cp, cb, ch;
    sinCos (&sp, &cp, orientation.pitch * 0.5f);
    sinCos (&sb, &cb, orientation.bank * 0.5f);
    sinCos (&sh, &ch, orientation.heading * 0.5f);
    
    if (transType == object2inertial)
    {
        w = ch * cp * cb + sh * sp * sb;
        x = ch * sp * cb + sh * cp * sb;
        y = -ch * sp * sb + sh * cp * cb;
        z = -sh * sp * cb + ch * cp * sb;
    }
    else if (transType == inertial2object)
    {
        w = ch * cp * cb + sh * sp * sb;
        x = -ch * sp * cb - sh * cp * sb;
        y = ch * sp * sb - sh * cp * cb;
        z = sh * sp * cb - ch * cp * sb;
    }
    else
    {
        std::cout << "Invalid transType!" << std::endl;
    }
}

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

Quaternion Quaternion::operator * (const Quaternion& a) const
{
    Quaternion result;
    
    result.w = w * a.w - x * a.x - y * a.y - z * a.z;
    result.x = w * a.x + x * a.w + z * a.y + y * a.z;
    result.y = w * a.y + y * a.w + x * a.z + z * a.x;
    result.z = w * a.z + z * a.w + y * a.x + x * a.y;
    
    return result;
}


Quaternion& Quaternion::operator *= (const Quaternion& a)
{
    *this = *this * a;
    
    return *this;
}

void Quaternion::normalize ()
{
    float mag = (float)sqrt (w * w + x * x + y * y + z * z);
    
    if (mag > 0.0f)
    {
        float oneOverMag = 1.0f / mag;
        
        w *= oneOverMag;
        x *= oneOverMag;
        y *= oneOverMag;
        z *= oneOverMag;
    }
    else
    {
        assert (false);
        identity();
    }
}

float dotProduct (Quaternion& a, Quaternion& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.z * a.z;
}

Quaternion conjugate (Quaternion& q)
{
    Quaternion result;
    
    result.w = q.w;
    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;
    
    return result;
}

Quaternion pow (const Quaternion &q, float exponent)
{
    // sin cos will get 0 and something over 0 will happen
    if (fabs (q.w) > 0.9999f)
    {
        return q;
    }
    
    float alpha = acos (q.w);
    
    float newAlpha = exponent * alpha;
    
    Quaternion result;
    result.w = cos (newAlpha);
    
    float mult = sin (newAlpha) / sin (alpha);
    result.x = q.x * mult;
    result.y = q.y * mult;
    result.z = q.z * mult;
    
    return result;
}

Quaternion::Quaternion (const RotationMatrix& rm)
{
    float m11 = rm.m11;
    float m12 = rm.m12;
    float m13 = rm.m13;
    
    float m21 = rm.m21;
    float m22 = rm.m22;
    float m23 = rm.m23;
    
    float m31 = rm.m31;
    float m32 = rm.m32;
    float m33 = rm.m33;
    
    float fourWSquareMinus1 = m11 + m22 + m33;
    float fourXSquareMinus1 = m11 - m22 - m33;
    float fourYSquareMinus1 = m22 - m11 - m33;
    float fourZSquareMinus1 = m33 - m11 - m22;
    
    int maxIndex = 0;
    float max = fourWSquareMinus1;
    
    if (fourXSquareMinus1 > max)
    {
        max = fourXSquareMinus1;
        maxIndex = 1;
    }
    
    if (fourYSquareMinus1 > max)
    {
        max = fourYSquareMinus1;
        maxIndex = 2;
    }
    
    if (fourZSquareMinus1 > max)
    {
        max = fourZSquareMinus1;
        maxIndex = 3;
    }
    
    max = sqrt (max + 1.0f) * 0.5f;
    float mult = 0.25f / max;
    
    switch (maxIndex)
    {
        case 0:
            w = max;
            x = (m23 - m32) * mult;
            y = (m31 - m13) * mult;
            z = (m12 - m21) * mult;
            break;
        case 1:
            x = max;
            w = (m23 - m32) * mult;
            y = (m12 + m21) * mult;
            z = (m31 + m13) * mult;
            break;
        case 2:
            y = max;
            w = (m31 - m13) * mult;
            x = (m12 + m21) * mult;
            z = (m23 + m32) * mult;
            break;
        case 3:
            z = max;
            w = (m12 - m21) * mult;
            x = (m31 + m13) * mult;
            y = (m23 + m32) * mult;
            z = (m23 + m32) * mult;
            break;
        default:
            break;
    }
}

// most important advantage of Quaternion is fluent slerp operation
Quaternion slerp (const Quaternion& q0, const Quaternion& q1, float t)
{
    if (t <= 0) return q0;
    if (t >= 1) return q1;

    float cosOmega = dotProduct(q0, q1);
    
    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;
    
    // avoid geeting different results
    if (cosOmega < 0.0f)
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }
    
    float k0, k1;
    // avoid sth over 0 happenning
    if (cosOmega > 0.999f)
    {
        k0 = 1.0f - t;
        k1 = t;
    }
    else
    {
        float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
        
        float omega = atan2 (sinOmega, cosOmega);
        
        float oneOverSinOmega = 1.0f / sinOmega;
        
        k0 = sin ((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin (t * omega) * oneOverSinOmega;
    }
    
    Quaternion result;
    
    result.x = k0 * q0.x + k1 * q1x;
    result.y = k0 * q0.y + k1 * q1y;
    result.z = k0 * q0.z + k1 * q1z;
    result.w = k0 * q0.w + k1 * q1w;
    
    return result;
}