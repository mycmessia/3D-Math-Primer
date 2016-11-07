//
//  Quaternion.hpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/19.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "Vector3.hpp"

class Quaternion
{
public:
    
    float w, x, y, z;
    
    void identity () { w = 1.0f; x = y = z = 0.0f; }
    
    // rotate around x axis
    void setRotationX (float theta);
    void setRotationY (float theta);
    void setRotationZ (float theta);
    void setRotationAxis (const Vector3& axis, float theta);
    
    float getRotationAngle () const;
    Vector3 getRotationAxis () const;
    
    Quaternion operator * (const Quaternion& a) const;
    Quaternion& operator *= (const Quaternion& a);
    
    void normalize ();
};

extern const Quaternion kQuaternionIdentity;
extern float dotProduct (const Quaternion& a, const Quaternion& b);
extern Quaternion conjugate (const Quaternion& q);
extern Quaternion pow (const Quaternion &q, float exponent);

#endif /* Quaternion_hpp */
