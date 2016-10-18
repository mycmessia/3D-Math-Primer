//
//  EulerAngle.hpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/18.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef EulerAngle_hpp
#define EulerAngle_hpp

#include <stdio.h>
#include "3DMath.h"

enum MatrixType {
    object2world,
    world2object
};

class EulerAngle
{
public:
    // all in radian
    float heading;  // y axis
    float pitch;    // x axis
    float bank;     // z axis
    
    EulerAngle () {}
    
    EulerAngle (float h, float p, float b) :
    heading (angle2radian(h)), pitch (angle2radian(p)), bank (angle2radian(b)) {}
    
    EulerAngle (const Matrix4x3 &m, MatrixType mt);
    EulerAngle (const RotationMatrix &m);
    
    void canonize ();
};

#endif /* EulerAngle_hpp */
