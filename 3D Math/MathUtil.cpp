//
//  MathUtil.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/18.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "MathUtil.h"

float wrapPi (float theta)
{
    theta += kPi;
    theta -= floor (theta * k1Over2Pi) * k2Pi;
    theta -= kPi;
    return theta;
}

float safeAcos (float x)
{
    if (x < -1.0f)
    {
        return kPi;
    }
    else if (x > 1.0f)
    {
        return 0.0f;
    }
    
    return acos (x);
}
