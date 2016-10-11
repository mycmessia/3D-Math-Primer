//
//  MathUtil.h
//  3D Math
//
//  Created by 梅宇宸 on 16/10/1.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef MathUtil_h
#define MathUtil_h

#include <cmath>

const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi * 0.5f;

inline float to_zero (float f)
{
    if (std::abs (f) < 0.00001f)
    {
        return 0.0f;
    }
    
    return f;
}

inline void sinCos (float *returnSin, float *returnCos, float theta)
{
    *returnSin = sin (theta);
    *returnCos = cos (theta);
}


#endif /* MathUtil_h */
