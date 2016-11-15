//
//  AABB.h
//  3D Math
//
//  Created by 梅宇宸 on 11/15/16.
//  Copyright © 2016 梅宇宸. All rights reserved.
//

#ifndef AABB_h
#define AABB_h

#include "Vector3.hpp"

// Axis-aligned minimum bounding box
class AABB
{
public:
    Vector3 max;
    Vector3 min;
    
    Vector3 size () const { return max - min; }
    float xSize () { return max.x - min.x; }
    float ySize () { return max.y - min.y; }
    float zSize () { return max.z - min.z; }
    
    Vector3 center () { return (min + max) * 0.5f; }
};

#endif /* AABB_h */
