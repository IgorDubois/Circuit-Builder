//
//  Vec2f.hpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 08/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#pragma once
#include "mathVector.hpp"

class Vec2f: MathVector{
public:
    float x, y;
    
    Vec2f();
    Vec2f(float, float);
    Vec2f(Vec2f const &);
    
    void normalize();
    float length();
};
