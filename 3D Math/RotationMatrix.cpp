//
//  RotationMatrix.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/17.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "3DMath.h"

void RotationMatrix::identity ()
{
    m11 = 1.0f; m11 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

void RotationMatrix::setup(const EulerAngle &e)
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