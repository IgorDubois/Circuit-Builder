//
//  mathVector.hpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 15/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#pragma once
#include <cmath>

class MathVector{
public:
    virtual void normalize() =0;
    virtual float length() =0;
    
};
