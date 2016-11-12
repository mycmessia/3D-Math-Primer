//
//  EulerAngle.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/18.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "EulerAngle.hpp"

void EulerAngle::canonize ()
{
    pitch = wrapPi (pitch);
    if (pitch < -kPiOver2)
    {
        pitch = -kPi - pitch;
        heading += kPi;
        bank += kPi;
    }
    else if (pitch > kPiOver2)
    {
        pitch = kPi - pitch;
        heading += kPi;
        bank += kPi;
    }
    
    // handle Gimbal lock
    if (fabs (pitch) > kPiOver2 - 1e-4)
    {
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        bank = wrapPi(bank);
    }
    
    heading = wrapPi(heading);
}

EulerAngle::EulerAngle (const RotationMatrix &m)
{
    float sp = -m.m23;
    
    // check Gimbal lock
    if (fabs(sp) > 0.999f)
    {
        pitch = kPiOver2 * sp;
        bank = 0.0f;
        heading = atan2(-m.m31, m.m11);
    }
    else
    {
        pitch = asin (sp);
        bank = atan2(m.m21, m.m22);
        heading = atan2(m.m13, m.m33);
    }
}

EulerAngle::EulerAngle (const Matrix4x3 &m, TransType mt)
{
    if (mt == object2world)
    {
        float sp = -m.m32;
        
        // check Gimbal lock
        if (fabs(sp) > 0.999f)
        {
            pitch = kPiOver2 * sp;
            bank = 0.0f;
            heading = atan2(-m.m23, m.m11);
        }
        else
        {
            pitch = asin (sp);
            bank = atan2(m.m12, m.m22);
            heading = atan2(m.m31, m.m33);
        }
    }
    else if (mt == world2object)
    {
        float sp = -m.m23;
        
        // check Gimbal lock
        if (fabs(sp) > 0.999f)
        {
            pitch = kPiOver2 * sp;
            bank = 0.0f;
            heading = atan2(-m.m31, m.m11);
        }
        else
        {
            pitch = asin (sp);
            bank = atan2(m.m21, m.m22);
            heading = atan2(m.m13, m.m33);
        }
    }
}

EulerAngle::EulerAngle (const Quaternion& q, TransType t)
{
    if (t == object2inertial)
    {
        float sp = -2.0f * (q.y * q.z - q.w * q.x);
        // check gimbal lock
        if (fabs(sp) > 0.999f)
        {
            pitch = kPiOver2 * sp;
            heading = atan2 (-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
            bank = 0.0f;
        }
        else
        {
            pitch  = asin (sp);
            heading = atan2 (q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
            bank = atan2 (q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
        }
    }
    else if (t == inertial2object)
    {
        float sp = -2.0f * (q.y * q.z + q.w * q.x);
        // check gimbal lock
        if (fabs(sp) > 0.999f)
        {
            pitch = kPiOver2 * sp;
            heading = atan2 (-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
            bank = 0.0f;
        } 
        else
        {
            pitch  = asin (sp);
            heading = atan2 (q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
            bank = atan2 (q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
        }
    }
    else
    {
        std::cout << "Invalid TransType!" << std::endl;
    }
}
