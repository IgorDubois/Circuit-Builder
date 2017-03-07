//
//  Vec2f.cpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 08/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#include "Vec2f.hpp"


Vec2f::Vec2f(){
    this->x = .0F;
    this->y = .0F;
}
Vec2f::Vec2f(float x, float y){
    this->x = x;
    this->y = y;
}
Vec2f::Vec2f(Vec2f const &v){
    this->x = v.x;
    this->y = v.y;
}

void Vec2f::normalize(){
    x /= this->length();
    y /= this->length();
}

float Vec2f::length(){
    return std::sqrt(x * x + y * y);
}
