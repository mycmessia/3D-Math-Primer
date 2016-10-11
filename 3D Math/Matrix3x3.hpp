//
//  Matrix3x3.hpp
//  3D Math
//
//  Created by 梅宇宸 on 16/9/30.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef Matrix3x3_hpp
#define Matrix3x3_hpp

#include <iostream>
class Vector3;

class Matrix3x3
{
public:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    
    // axis 1->x 2->y 3->z
    void setRotate (int axis, float theta);
    
    void setScale (const float kx, const float ky, const float kz);
    void setScale (const Vector3 &v);
    void setProject (const Vector3 &v);
    void setReflect (int axis);
    void setReflect (const Vector3 &n);
    void setShear (int axis, float s, float t); // s and t decide the range of shear
    
    void print ();
};

Matrix3x3 operator * (const Matrix3x3 &a, const Matrix3x3 &b);
Vector3 operator * (const Vector3 &v, const Matrix3x3 &m);

Matrix3x3 &operator *= (Matrix3x3 &a, const Matrix3x3 &b);
Vector3 &operator *= (Vector3 &v, const Matrix3x3 &m);

float determinant (const Matrix3x3 &m);
Matrix3x3 inverse (const Matrix3x3 &m);

#endif /* Matrix3x3_hpp */
