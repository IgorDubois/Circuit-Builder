//
//  util.cpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 08/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#include "util.hpp"

void drawCircle(float x, float y, float radius, bool fill)
{
    if(fill){
        glBegin(GL_POLYGON);
        glColor3f(1.F, 1.F, 1.F);
        
        for (int i=0; i < 360; i++)
        {
            float degInRad = i*DEG2RAD;
            glVertex2f(x + cos(degInRad)*radius,y + sin(degInRad)*radius);
        }
        
        glEnd();
        glDisable(GL_DEPTH_TEST);
    
    }
    glBegin(GL_LINE_LOOP);
    glColor3f(0.F, 0.F, 0.F);
    
    for (int i=0; i < 360; i++)
    {
        float degInRad = i*DEG2RAD;
        glVertex2f(x + cos(degInRad)*radius,y + sin(degInRad)*radius);
    }
    
    glEnd();
}
