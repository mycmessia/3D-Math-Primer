//
//  RotationMatrix.hpp
//  3D Math
//
//  Created by 梅宇宸 on 16/10/17.
//  Copyright © 2016年 梅宇宸. All rights reserved.
//

#ifndef RotationMatrix_hpp
#define RotationMatrix_hpp

class Vector3;
class EulerAngle;
class Quaternion;

class RotationMatrix {
public:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    
    RotationMatrix (const EulerAngle &e);
    
    void identity ();
    
    Vector3 inertial2Object (const Vector3 &v) const;
    Vector3 object2Inertial (const Vector3 &v) const;
    
    void inertial2ObjectQuaternion (const Quaternion& q);
    void object2InertialQuaternion (const Quaternion& q);
};

#endif /* RotationMatrix_hpp */
