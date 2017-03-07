//
//  button.hpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 15/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#pragma once
#include "Vec3f.hpp"
#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif

enum BUTTON_TYPE { B_LINK, B_DELETE, B_PRINT, B_REMOVELINKS, B_SAVE};

class Button{
private:
    float xCoord;       /*!< x coordinate of the bottom left of the button */
    float yCoord;       /*!< y coordinate of the bottom left of the button */
    float xLength;      /*!< width of the button */
    float yLength;      /*!< height of the button */
    std::string text;   /*!< text to display in the button */
    Vec3f colour;       /*!< button rgb colour */
    BUTTON_TYPE type;   /*!< the type of button */
    
public:
    Button(float x, float y, float w, float h, Vec3f c, std::string s, BUTTON_TYPE t);
    Button(float x, float y, float w, float h, std::string s, BUTTON_TYPE t);
    
    //! \fn bool intersects(int x, int y)
    //! \brief check either a point is contained in the button bounding box.
    //! \param [in] x : the point x coordinate
    //! \param [in] y : the point y coordinate
    bool intersects(int x, int y);
    
    //! \fn BUTTON_TYPE getType()
    //! \brief returns the type of the button
    BUTTON_TYPE getType();
    
    //! \fn void draw()
    //! \brief draws the button and its text
    void draw();
};
