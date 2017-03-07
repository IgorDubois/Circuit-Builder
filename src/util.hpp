//
//  util.hpp
//  CourseWork
//
//  Created by Hippolyte Dubois on 08/02/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#pragma once

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif
#include <cmath>
#include "Vec3f.hpp"

//! \def DEG2RAD : ratio radian/degree
const float DEG2RAD = 3.14159/180;

//! \fn void drawCircle(float x, float y, float r, bool fill)
//! \brief draws a circle with [x;y] coordinates and r radius
//! \param[in] x : the x coordinate
//! \param[in] y : the y coordinate
//! \param[in] r : the radius
//! \param[in] fill : shoud the circle be filled ?
void drawCircle(float x, float y, float r, bool fill);
