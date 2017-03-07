//
//  button.cpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 15/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#include "button.hpp"

Button::Button(float x, float y, float w, float h, Vec3f c, std::string s, BUTTON_TYPE t){
    this->xCoord = x;
    this->yCoord = y;
    this->xLength = w;
    this->yLength = h;
    this->colour = c;
    this->text = s;
    this->type = t;
}
Button::Button(float x, float y, float w, float h, std::string s, BUTTON_TYPE t){
    this->xCoord = x;
    this->yCoord = y;
    this->xLength = w;
    this->yLength = h;
    this->colour = Vec3f();
    this->text = s;
    this->type = t;
}

bool Button::intersects(int x, int y){
    
    float ax = xCoord;
    float ay = yCoord;
    float bx = xCoord;
    float by = yCoord + yLength;
    float dx = xCoord + xLength;
    float dy = yCoord;
    
    
    float bax = bx - ax;
    float bay = by - ay;
    float dax = dx - ax;
    float day = dy - ay;
    
    if ((x - ax) * bax + (y - ay) * bay < 0.0)
        return false;
    if ((x - bx) * bax + (y - by) * bay > 0.0)
        return false;
    if ((x - ax) * dax + (y - ay) * day < 0.0)
        return false;
    if ((x - dx) * dax + (y - dy) * day > 0.0)
        return false;
    return true;
}

void Button::draw(){
    glColor3f(colour.x, colour.y, colour.z);
    glBegin(GL_POLYGON);
    glVertex3f(xCoord, yCoord, -.05F);
    glVertex3f(xCoord + xLength, yCoord, -.05F);
    glVertex3f(xCoord + xLength, yCoord + yLength, -.05F);
    glVertex3f(xCoord, yCoord + yLength, -.05F);
    glEnd();
    glColor3f(1.F, 1.F, 1.F);
    //glWindowPos2f(xCoord + 5,glutGet(GLUT_WINDOW_HEIGHT) - yCoord - yLength * 0.75);
	glRasterPos2f(xCoord + 5 , yCoord + yLength / 4);
    for(std::string::iterator it = text.begin(); it != text.end(); it++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *it);
    }
}

BUTTON_TYPE Button::getType(){
    return this->type;
}



