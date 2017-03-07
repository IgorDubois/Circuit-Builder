#include	<iostream>
#include	<algorithm>
#include	<vector>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif

#include	"OGWindow.h"

void DrawGLScene(GLvoid);
void Idle(GLvoid);
void ReSizeGLScene(GLsizei fwidth, GLsizei fheight);
void mouseClick(int button, int state, int x, int y);
void mouseMotion( int x, int y);
void mousePassiveMotion( int x, int y);

void constructMenus(void);
void menuFunction1( int Option );
void constructNestedMenus( void );
void menuFunction2( int Option );
void menuAddFunction( int Option );
void menuSub2Function( int Option );



using namespace std;

OGWindow	theWindow;

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize( 750, 620 );
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Circuit Builder");
	glEnable(GL_DEPTH_TEST);	// enable the depth buffer test
	
	glutDisplayFunc(DrawGLScene);
	glutReshapeFunc(ReSizeGLScene);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
    
    constructNestedMenus();
	glutIdleFunc(Idle);
	theWindow.initGL(); 
	
	glutMainLoop();
}

void DrawGLScene(void) {
	theWindow.myDrawGLScene();
}


void Idle(void) {
	theWindow.myIdle();
}

GLvoid ReSizeGLScene(GLsizei fwidth, GLsizei fheight) {
	theWindow.MyReSizeGLScene(fwidth, fheight);
}

void mouseClick(int button, int state, int x, int y) {
	theWindow.myMouseClick(button, state, x, y);
}

void mouseMotion( int x, int y) {
	theWindow.myMouseMotion( x, y);
}

void mousePassiveMotion( int x, int y) {
	theWindow.myMousePassiveMotion( x, y);
}

void constructNestedMenus(void){
    int topMenu, subMenu1;
    topMenu = glutCreateMenu( menuFunction1);
    subMenu1 = glutCreateMenu( menuAddFunction);
    glutAddMenuEntry("AMMETER", 1);
    glutAddMenuEntry("BATTERY", 2);
    glutAddMenuEntry("BULB", 3);
    glutAddMenuEntry("CAPACITOR", 4);
    glutAddMenuEntry("COIL", 5);
    glutAddMenuEntry("CONNECTOR", 6);
    glutAddMenuEntry("RESISTOR", 7);
    
    
    // Set current menu to topMenu
    glutSetMenu( topMenu );
    // Add submenus to the current menu (which is topMenu)
    glutAddSubMenu("Add Component", subMenu1);
    glutAttachMenu( GLUT_RIGHT_BUTTON );
}

void menuFunction1( int Option ){
    theWindow.menuRightClic( Option );
}

void menuAddFunction(int Option){
    theWindow.menuAdd(Option);
}
