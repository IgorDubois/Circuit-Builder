#pragma once

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Component.h"
#include "util.hpp"
#include "button.hpp"

#include "tinyxml2.h"


enum Colour { RED, BLUE };

class OGWindow
{
	private:
		
		int wWidth, wHeight;        /*!< Width and Height of OpenGL window in screen units */
		double aspect_ratio;		/*!< aspect ratio of viewport */
		int Xmin, Xmax, Ymin, Ymax; /*!< Paramaters of orthographic projection */
		int panelHeight;            /*!< Button panel height */

		bool LINK, DELETE, REMOVELINK;          /*!< Current clicking mode */
		int linkNo;

		double squareX, squareY;    /*!< Coords of bottom-left corner of shape */
		double squareWidth, squareHeight;
		void screen2World(int screenX, int screenY, double & worldX, double & worldY);
		bool onSquare(int screenX, int screenY);
        bool onButton(int screenX, int screenY);
		bool squareOnScreenP(double X, double Y);
		void toggleSquare( void );
		Colour squareColour;
		bool squareDraggingP;
		int squareXOld, squareYOld;
		Component currentSquare;
		Component *currentSquarePtr, *linkSquPtr1, *linkSquPtr2;
		double squareXStart, squareYStart, squareXEnd, squareYEnd;
		std::vector< Component > compVector;
        std::vector< Button > buttonsVector;

	public:
		void initComponents( void );
        void initButtons( void );
		void initGL(void);
    
        void menuRightClic(int option);
        void menuAdd(int option);
    
		void MyReSizeGLScene(int fwidth, int fheight);
		void myDrawGLScene(GLvoid);
		void myDrawModel(GLvoid);
		void myIdle(GLvoid);
		void myMouseClick(int button, int state, int x, int y);
		void myMouseMotion(int x, int y);
		void myMousePassiveMotion(int x, int y);
		double pointArcDistance(double x, double y, double vx, double vy, double wx, double wy);

		void drawButtonArea(GLvoid);
		void checkButtonClick( int x, int y);

		void deleteSquare( Component *squPtr );

		void printComponents( void );

		//! \fn void saveCircuit()
		//! \brief writes the circuit details to a XML file, links not supported yet
		void saveCircuit();
    
        void enterLinkMode();
        void enterDeleteMode();
        void enterRemoveLinksMode();

	
};

