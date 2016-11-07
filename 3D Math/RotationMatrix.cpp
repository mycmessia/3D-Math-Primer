//
//  RotationMatrix.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/17.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "3DMath.h"

RotationMatrix::RotationMatrix(const EulerAngle &e)
{
    float sh, ch, sp, cp, sb, cb;
    
    sinCos (&sh, &ch, e.heading);
    sinCos (&sp, &cp, e.pitch);
    sinCos (&sb, &cb, e.bank);
    
    m11 = ch * cb + sh * sp * sb;
    m12 = -ch * sb + sh * sp * cb;
    m13 = sh * cp;
    
    m21 = sb * cp;
    m22 = cb * cp;
    m23 = -sp;
    
    m31 = -sh * cb + ch * sp * sb;
    m32 = sb * sh + ch * sp * cb;
    m33 = ch * cp;
}

void RotationMatrix::identity ()
{
    m11 = 1.0f; m11 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

Vector3 RotationMatrix::inertial2Object (const Vector3 &v) const
{
    return Vector3 (
        m11 * v.x + m21 * v.y + m31 * v.z,
        m12 * v.x + m22 * v.y + m32 * v.z,
        m13 * v.x + m23 * v.y + m33 * v.z
    );
}

Vector3 RotationMatrix::object2Inertial (const Vector3 &v) const
{
    return Vector3 (
        m11 * v.x + m12 * v.y + m13 * v.z,
        m21 * v.x + m22 * v.y + m23 * v.z,
        m31 * v.x + m32 * v.y + m33 * v.z
    );
}

void RotationMatrix::inertial2ObjectQuaternion (const Quaternion &q)
{
    m11 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    m12 = 2.0f * (q.x * q.y + q.w * q.z);
    m13 = 2.0f * (q.x * q.z + q.w * q.y);
    
    m21 = 2.0f * (q.x * q.y - q.w * q.z);
    m22 = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
    m23 = 2.0f * (q.y * q.z + q.w * q.x);
    
    m31 = 2.0f * (q.x * q.z + q.w * q.y);
    m32 = 2.0f * (q.y * q.z - q.w * q.x);
    m33 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
}

void RotationMatrix::object2InertialQuaternion (const Quaternion &q)
{
    m11 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    m12 = 2.0f * (q.x * q.y - q.w * q.z);
    m13 = 2.0f * (q.x * q.z + q.w * q.y);
    
    m21 = 2.0f * (q.x * q.y + q.w * q.z);
    m22 = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
    m23 = 2.0f * (q.y * q.z - q.w * q.x);
    
    m31 = 2.0f * (q.x * q.z + q.w * q.y);
    m32 = 2.0f * (q.y * q.z + q.w * q.x);
    m33 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
}
