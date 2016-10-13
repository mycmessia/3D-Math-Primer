//
//  main.cpp
//  3D Math
//
//  Created by 梅宇宸 on 16/9/20.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#include "3DMath.h"

int main(int argc, const char * argv[])
{
    Matrix4x3 m;
    
    m.m11 = -4; m.m12 = -3; m.m13 = 3;
    m.m21 = 0;  m.m22 = 2;  m.m23 = -2;
    m.m31 = 1;  m.m32 = 4;  m.m33 = -1;
    
    Matrix4x3 r = inverse(m);
    
    r.print();
    
    Matrix4x3 a = r * m;
    
    a.print();
    
    return 0;
}
