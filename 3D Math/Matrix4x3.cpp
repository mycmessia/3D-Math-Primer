//
//  Matrix4x3.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/9/30.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "3DMath.h"

Matrix4x3::Matrix4x3 ()
{
    m11 = 0,  m12 = 0,   m13 = 0;
    m21 = 0,  m22 = 0,   m23 = 0;
    m31 = 0,  m32 = 0,   m33 = 0;
}

void Matrix4x3::zeroTranslation ()
{
    tx = ty = tz = 0;
}

void Matrix4x3::setTranslation (const Vector3 &d)
{
    tx = d.x;   ty = d.y;   tz = d.y;
}

void Matrix4x3::setupTranslation (const Vector3 &d)
{
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m21 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = d.x;   ty = d.y;   tz = d.z;
}

Matrix4x3 operator * (const Matrix4x3 &a, const Matrix4x3 &b)
{
    Matrix4x3 r;
    
    r.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
    r.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
    r.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
    
    r.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
    r.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
    r.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
    
    r.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
    r.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
    r.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
    
    r.tx = a.tx * b.m11 + a.ty * b.m21 + a.tz * b.m31 + b.tx;
    r.ty = a.tx * b.m12 + a.ty * b.m22 + a.tz * b.m32 + b.ty;
    r.tz = a.tx * b.m13 + a.ty * b.m23 + a.tz * b.m33 + b.tz;
    
    return r;
}


Vector3 operator * (const Vector3 &v, const Matrix4x3 &m)
{
    return Vector3 (
        v.x * m.m11 + v.y * m.m21 + v.z * m.m31,
        v.x * m.m12 + v.y * m.m22 + v.z * m.m32,
        v.x * m.m13 + v.y * m.m23 + v.z * m.m33
    );
}

Matrix4x3 &operator *= (Matrix4x3 &a, const Matrix4x3 &b)
{
    a = a * b;
    
    return a;
}

Vector3 &operator *= (Vector3 &v, const Matrix4x3 &m)
{
    v = v * m;
    
    return v;
}

void Matrix4x3::setRotate(int axis, float theta)
{
    float sin, cos;
    
    sinCos(&sin, &cos, theta);
    
    switch (axis) {
        case 1:
            m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
            m21 = 0.0f; m22 = cos;  m23 = sin;
            m31 = 0.0f; m32 = -sin; m33 = cos;
            break;
        case 2:
            m11 = cos;  m12 = 0.0f; m13 = -sin;
            m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
            m31 = sin;  m32 = 0.0f; m33 = cos;
            break;
        case 3:
            m11 = cos;  m12 = sin;  m13 = 0.0f;
            m21 = -sin; m22 = cos;  m23 = 0.0f;
            m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
            break;
        default:
            std::cout << "Wrong type of axis! func: " << __FUNCTION__ << std::endl;
            assert(false);
            break;
    }
    
    tx = ty = tz = 0.0f;
}

void Matrix4x3::setScale (const float kx, const float ky, const float kz)
{
    m11 = kx;   m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = ky;   m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = kz;
    
    tx = ty = tz = 0.0f;
}

void Matrix4x3::setScale (const Vector3 &v)
{
    m11 = v.x;  m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = v.y;  m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = v.z;
    
    tx = ty = tz = 0.0f;
}


void Matrix4x3::setProject (const Vector3 &v)
{
    // make sure v is an unit vector
    assert (fabs(v * v - 1.0f) < 0.001f);
    
    m11 = 1.0f - v.x * v.x;
    m22 = 1.0f - v.y * v.y;
    m33 = 1.0f - v.z * v.z;
    
    m12 = m21 = -v.x * v.y;
    m13 = m31 = -v.x * v.z;
    m23 = m32 = -v.y * v.z;
    
    tz = ty = tz = 0.0f;
}

void Matrix4x3::setReflect (int axis, float k)
{
    switch (axis)
    {
        case 1: // x = k surface
            m11 = -1.0f;    m12 = 0.0f;     m13 = 0.0f;
            m21 = 0.0f;     m22 = 1.0f;     m23 = 0.0f;
            m31 = 0.0f;     m32 = 0.0f;     m33 = 1.0f;
            
            tx = 2.0f * k;  ty = 0.0f;      tz = 0.0f;
            break;
            
        case 2: // y = k surface
            m11 = 1.0f;     m12 = 0.0f;     m13 = 0.0f;
            m21 = 0.0f;     m22 = -1.0f;    m23 = 0.0f;
            m31 = 0.0f;     m32 = 0.0f;     m33 = 1.0f;
            
            tx = 0.0f;      ty = 2.0f * k;  tz = 0.0f;
            break;
            
        case 3: // z = k surface
            m11 = 1.0f;     m12 = 0.0f;     m13 = 0.0f;
            m21 = 0.0f;     m22 = 1.0f;     m23 = 0.0f;
            m31 = 0.0f;     m32 = 0.0f;     m33 = -1.0f;
            
            tx = 0.0f;      ty = 0.0f;      tz = 2.0f * k;
            break;
            
        default:
            assert(false);
            break;
    }
}

void Matrix4x3::setReflect (const Vector3 &n)
{
    assert(fabs(n * n - 1.0f) < 0.01f);
    
    float ax = -2.0f * n.x;
    float ay = -2.0f * n.y;
    float az = -2.0f * n.z;
    
    m11 = 1.0f + ax * n.x;
    m22 = 1.0f + ay * n.y;
    m33 = 1.0f + az * n.z;
    
    m12 = m21 = ax * n.y;
    m13 = m31 = ax * n.z;
    m23 = m32 = ay * n.z;
    
    tx = ty = tz = 0.0f;
}

void Matrix4x3::setShear (int axis, float s, float t)
{
    switch (axis)
    {
        case 1:     // use x shear y and z
            m11 = 1.0f;     m12 = s;        m13 = t;
            m21 = 0.0f;     m22 = 1.0f;     m23 = 0.0f;
            m31 = 0.0f;     m32 = 0.0f;     m33 = 1.0f;
            break;
        case 2:
            m11 = 1.0f;     m12 = 0.0f;     m13 = 0.0f;
            m21 = s;        m22 = 1.0f;     m23 = t;
            m31 = 0.0f;     m32 = 0.0f;     m33 = 1.0f;
            break;
        case 3:
            m11 = 1.0f;     m12 = 0.0f;     m13 = 0.0f;
            m21 = 0.0f;     m22 = 1.0f;     m23 = 0.0f;
            m31 = s;        m32 = t;        m33 = 1.0f;
            break;
        default:
            assert(false);
            break;
    }
    
    tx = ty = tz = 0.0f;
}

float determinant (const Matrix3x3 &m)
{
    return m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) +
           m.m12 * (m.m23 * m.m31 - m.m21 * m.m33) +
           m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
}

Matrix3x3 inverse (const Matrix3x3 &m)
{
    float det = determinant (m);
    
    assert(fabs (det) > 0.00001f);
    
    float oneOverDet = 1.0f / det;
    
    Matrix3x3 r;
    
    r.m11 = (m.m22 * m.m33 - m.m23 * m.m32) * oneOverDet;
    r.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * oneOverDet;
    r.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * oneOverDet;
    
    r.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * oneOverDet;
    r.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * oneOverDet;
    r.m23 = (m.m13 * m.m21 - m.m11 * m.m23) * oneOverDet;
    
    r.m31 = (m.m21 * m.m32 - m.m22 * m.m31) * oneOverDet;
    r.m32 = (m.m12 * m.m31 - m.m11 * m.m32) * oneOverDet;
    r.m33 = (m.m11 * m.m22 - m.m12 * m.m21) * oneOverDet;
    
    return r;
}

Vector3 getTranslation (const Matrix4x3 &m)
{
    return Vector3 (m.tx, m.ty, m.tz);
}

void Matrix3x3::print ()
{
    std::cout << m11 << "\t" << m12 << "\t" << m13 << std::endl;
    std::cout << m21 << "\t" << m22 << "\t" << m23 << std::endl;
    std::cout << m31 << "\t" << m32 << "\t" << m33 << std::endl;
}

void Matrix4x3::print ()
{
    std::cout << m11 << "\t" << m12 << "\t" << m13 << "\t" << tx << std::endl;
    std::cout << m21 << "\t" << m22 << "\t" << m23 << "\t" << ty << std::endl;
    std::cout << m31 << "\t" << m32 << "\t" << m33 << "\t" << tz << std::endl;
}
