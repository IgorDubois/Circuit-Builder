//
//  Vec3f.hpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 15/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#pragma once
#include "mathVector.hpp"

class Vec3f: MathVector{
public:
    float x,y,z;
    
    Vec3f();
    Vec3f(float, float, float);
    Vec3f(Vec3f const &);
    
    void normalize();
    float length();
    
};
