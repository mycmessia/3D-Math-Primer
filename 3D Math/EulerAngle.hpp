//
//  EulerAngle.hpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/18.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef EulerAngle_hpp
#define EulerAngle_hpp

#include "3DMath.h"

class EulerAngle
{
public:
    // all in radian
    float heading;  // y axis
    float pitch;    // x axis
    float bank;     // z axis
    
    EulerAngle () {}
    EulerAngle (float h, float p, float b) : heading (angle2radian(h)), pitch (angle2radian(p)), bank (angle2radian(b)) {}
    EulerAngle (const Matrix4x3& m, TransType mt);
    EulerAngle (const RotationMatrix &m);
    EulerAngle (const Quaternion& q, TransType mt);
    
    void canonize ();
};

#endif /* EulerAngle_hpp */
