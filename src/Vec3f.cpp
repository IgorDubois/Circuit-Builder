//
//  Vec3f.cpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 15/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#include "Vec3f.hpp"

Vec3f::Vec3f(){
    x = 0.F;
    y = 0.F;
    z = 0.F;
    
}

Vec3f::Vec3f(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

Vec3f::Vec3f(Vec3f const &v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    
}

void Vec3f::normalize(){
    x /= this->length();
    y /= this->length();
    z /= this->length();
}

float Vec3f::length(){
    return std::sqrt(x*x + y*y + z*z);
}
