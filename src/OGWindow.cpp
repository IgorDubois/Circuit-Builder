
#include "OGWindow.h"
#include <vector>
#include <algorithm>


using namespace std;



void OGWindow::initGL(void) {
	
	initComponents();
    initButtons();
	glClearColor(1.0, 1.0, 1.0, 1.0);

	panelHeight = 40;  // Height of button panel

	/*
	squareX = 1.0;
	squareY = 1.0;

	squareWidth = 4.0;
	squareHeight = 4.0;
	squareColour = RED;  */

	squareDraggingP = false;

	LINK = false;
	linkNo = 1;
}

//  Use for animations if required
void OGWindow::myIdle(void) { 
	
	
}


void OGWindow::myMouseClick(int button, int state, int x, int y) 
{

	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){

		// Check if one of the three buttons in the upper viewport has been clicked
		checkButtonClick( x, y );  


		if (LINK){
			if ( onSquare(x, y) ) { //onSquare sets currentSquarePtr to point to the square just clicked on
				if (linkNo == 1) {
					linkSquPtr1 = currentSquarePtr;
					linkNo += 1;
					return;
				}
				if (linkNo == 2) {
					linkSquPtr2 = currentSquarePtr;
					linkNo = 1;

					linkSquPtr1->connections.push_back( linkSquPtr2 );
					//linkSquPtr2->connections.push_back( linkSquPtr1 );

					LINK = false;
					cout << "Leaving LINK mode" << endl;

					glutPostRedisplay();
				}
			}
		} // End if LINK

		if (DELETE){
			if ( onSquare(x, y) ) {

				deleteSquare( currentSquarePtr );
				DELETE = false;

				cout << "Leaving DELETE mode" << endl;
                glutPostRedisplay();
				return;
			}
		}
        
        if (REMOVELINK){
            if ( onSquare(x, y) ) {
                
                currentSquarePtr->connections.clear();
                REMOVELINK = false;
                
                cout << "Leaving REMOVELINK mode" << endl;
                glutPostRedisplay();
                return;
            }
        }
        
        
        
        if (! LINK) {
			if ( onSquare(x, y) ) {
				squareDraggingP = true;
				squareXOld = x;
				squareYOld = y;
	
				screen2World(x, y, squareXStart, squareYStart);
			}
		} // End if ! LINK
	} // End if left button down


	if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP ){
		squareDraggingP = false;
	}
}

void OGWindow::myMouseMotion(int x, int y)
{

	int screenXDiff, screenYDiff;
	double worldXDiff, worldYDiff;

	// cout << "Motion ( " << x << ", " << y << " )  " << endl;

	// Can move cursor off square during dragging
	// if square stops at edge of window
	if ( ! onSquare(x, y) ) {
			squareDraggingP = false;
			return;
	}

	if ( squareDraggingP ) {
		 screenXDiff = x - squareXOld; // Mouse movement in screen coords
		 screenYDiff = y - squareYOld;

		 worldXDiff = screenXDiff * ( Xmax - Xmin ) / (double) wWidth;
		 // ScreenY is upside-down, so need to reverse direction
		 worldYDiff = screenYDiff * ( Ymin - Ymax ) / (double) wHeight;

		 squareX = currentSquarePtr->getX();
		 squareY = currentSquarePtr->getY();

		 if ( squareOnScreenP(squareX + worldXDiff, squareY + worldYDiff) ) {
			 currentSquarePtr->setX(  squareX + worldXDiff );
			 currentSquarePtr->setY(  squareY + worldYDiff );
		 }
			
		squareXOld = x;
		squareYOld = y;

		 glutPostRedisplay();
	}

}

void OGWindow::myMousePassiveMotion(int x, int y)
{

}

void OGWindow::MyReSizeGLScene(int fwidth, int fheight) 
{

	// Store size of display viewport in class variables so it can be accessed in myDrawGLScene() if necessary
	wWidth = fwidth;
	wHeight = fheight-panelHeight;  // Heigh of display area is height of window - height of button panel

	// Calculate aspect ration of the display viewport
	aspect_ratio = (float) wWidth / wHeight;

	// Set camera so it can see a square area of space running from 0 to 10 
	// in both X and Y directions, plus a bit of space around it.
	Ymin = -1;
	Ymax = 12;
	Xmin = -1;

	// Choose Xmax so that the aspect ration of the projection
	// = the aspect ratio of the viewport
	Xmax = (aspect_ratio * (Ymax -Ymin)) + Xmin;

	

	

}	

void OGWindow::myDrawGLScene(GLvoid)		// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear the drawing area


	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();
	glOrtho(Xmin, Xmax, Ymin, Ymax, -1.0, 1.0);
	glViewport(0, 0, wWidth, wHeight);		// Display area

	myDrawModel();


	/* In button panel
		world coords are same as screen coords (apart from top/bottom reversal)
		to simplify checking what button user has clicked on
	*/
	
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();
	glOrtho(0, wWidth, 0, panelHeight, -1.0, 1.0);
	glViewport(0, wHeight, wWidth, panelHeight);		// Button area

	drawButtonArea();

	

	glutSwapBuffers(); // Needed if we're running an animation
	glFlush();
}



void OGWindow::myDrawModel(GLvoid)
{
	
	vector<Component>::iterator iterator;
	vector< Component *>::iterator iterator2;
	for ( iterator = compVector.begin(); iterator != compVector.end(); ++ iterator){
		double x = iterator->getX();
		double y = iterator->getY();
		double size = iterator->getSize();

		glColor3f(0.0, 0.0, 0.0);
		vector<Component *> c = iterator->connections;
		for ( iterator2 = c.begin(); iterator2 != c.end(); ++ iterator2){
			double x2 = (*iterator2)->getX();
			double y2 = (*iterator2)->getY();
            double size2 = (*iterator2)->getSize();

			// set z to -0.1 to put lines behind squares
			glBegin(GL_LINE_STRIP);
				glVertex3f(x, y, -0.1);  // Centre of square selected by outer iterator
                glVertex3f(x2, y, -0.1);
                glVertex3f(x2, y2, -0.1); // Center of square connected to, selected by inner iterator
            glEnd();
            drawCircle(x2, y, 0.05, true);

		}
        
	}
    
    for(Component c : compVector){
        c.draw();
    }
}


// Convert from screen coords returned by mouse
// to world coordinates.
// Return result in worldX, worldY
void OGWindow::screen2World(int screenX, int screenY, double & worldX, double & worldY)
{
	// Dimensions of rectangle viewed by camera projection
	double projWidth = Xmax -Xmin;
	double projHeight = Ymax - Ymin;

	// Screen coords with origin at bottom left
	int screenLeft = screenX;
	int screenUp = wHeight - (screenY - panelHeight); 

	worldX = Xmin + screenLeft * projWidth / wWidth ;
	worldY = Ymin + screenUp *  projHeight / wHeight ;
}

// Determine whether user has clicked on a square
// If so set currentSquarePtr to point to the associated component
bool OGWindow::onSquare(int screenX, int screenY)
{
	double xWorld, yWorld;
	int index = 0;
	screen2World( screenX, screenY, xWorld, yWorld);

	vector<Component>::iterator constIterator;
	for ( constIterator = compVector.begin(); constIterator != compVector.end(); ++ constIterator){
			double sqX = constIterator->getX();
			double sqY = constIterator->getY();
			double hSize = constIterator->getSize() / 2;
			int index = constIterator->getIndex();
		
			// sqX, sqY are at the centre of the square, so a distance of hSize from each edge
		if (	xWorld >= sqX - hSize &&
				xWorld <= sqX + hSize &&
				yWorld >= sqY- hSize &&
				yWorld <= sqY + hSize ){
					// Because constIterator isn't ACTUALY a pointer to a Component
				currentSquarePtr = & (*constIterator);
				return true;
		}
	}
	return false;
}

void OGWindow::toggleSquare( void )
{
	if (squareColour == RED)
		squareColour = BLUE;
	else 
		squareColour = RED;
}

bool OGWindow::squareOnScreenP(double sqX, double sqY ) 
{
	
	// Here the '1's occur because the width and height of the square is 2
	// so it sticks out by a distance of 1 in all directions from the centre
	// Really shouldn't hard-wire numbers like this
	return( 
			(sqX - 1) >= Xmin &&
			(sqX + 1) <= Xmax &&
			(sqY - 1) >= Ymin &&
			(sqY + 1) <= Ymax );
}

double OGWindow::pointArcDistance(double px, double py, double vx, double vy, double wx, double wy)
{
	// Length of arc squared
	double lsq = (vx-wx)*(vx-wx) + (vy-wy)*(vy-wy);
	
	// Project point p onto vw
	double t = ((px-vx)*(wx-vx) + (py-vy)*(wy-vy)) /lsq;

	if (t < 0)
        return std::sqrt( (px-vx)*(px-vx) + (py-vy)*(py-vy) );
	else if (t > 1)
        return std::sqrt( (px-wx)*(px-wx) + (py-wy)*(py-wy) );
	else {
		double projx, projy;
		projx = vx + t * (wx - vx);
		projy = vy + t * (wy - vy);

        return std::sqrt( (px-projx)*(px-projx) + (py-projy)*(py-projy) );
	}
}


void OGWindow::drawButtonArea(GLvoid)
{

	// Line along bottom of button area
	glColor3f(0.0, 0.0, 0.0);
	glBegin( GL_LINES );
		glVertex3f( 0, 0, 0); 
		glVertex3f( wWidth, 0, 0); 
	glEnd();

    for(std::vector<Button>::iterator it = buttonsVector.begin(); it != buttonsVector.end(); it++){
        it->draw();
    }
}

void OGWindow::enterLinkMode(){
    cout << "Clicked LINK button" << endl;
    cout << "Entering LINK mode" << endl;
    LINK = true;
}

void OGWindow::enterRemoveLinksMode(){
    cout << "Clicked REMOVE LINK button" << endl;
    cout << "Entering REMOVELINK mode" << endl;
    REMOVELINK = true;
}

void OGWindow::enterDeleteMode(){
    cout << "Clicked DELETE button" << endl;
    cout << "Entering DELETE mode" << endl;
    DELETE = true;
}

void OGWindow::checkButtonClick( int x, int y)
{
    for(std::vector<Button>::iterator it = buttonsVector.begin(); it != buttonsVector.end(); it++){
        if(it->intersects(x, y)){
            //it->triggerEvent();
            switch(it->getType()){
                case B_LINK:
                    enterLinkMode();
                    break;
                    
                case B_DELETE:
                    enterDeleteMode();
                    break;
                    
                case B_PRINT:
                    printComponents();
                    break;
                    
                case B_REMOVELINKS:
                    enterRemoveLinksMode();
                    break;
				case B_SAVE:
					saveCircuit();
					break;
            }
        }
    }
}

void OGWindow::initComponents( void )
{
	Component *compPtr = new Component;

	compPtr->setX( 4.0 );
	compPtr->setY( 4.0 );
    compPtr->setType(BULB);

	compVector.push_back( *compPtr );

    
    printComponents();

}

void OGWindow::initButtons(){
    Button *buttPtr = new Button(10, 10, 60, 20, Vec3f(.8F, .1F, .1F), "LINK", B_LINK);
    buttonsVector.push_back(*buttPtr);
    buttPtr = new Button(80, 10, 60, 20, Vec3f(.2F, .1F, .8F), "DELETE", B_DELETE);
    buttonsVector.push_back(*buttPtr);
    buttPtr = new Button(150, 10, 60, 20, Vec3f(.8F, .8F, 0.F), "PRINT", B_PRINT);
    buttonsVector.push_back(*buttPtr);
    buttPtr = new Button(220, 10, 100, 20, Vec3f(0.F, .8F, 0.F), "REMOVE LINKS", B_REMOVELINKS);
    buttonsVector.push_back(*buttPtr);
	buttPtr = new Button(330, 10, 100, 20, Vec3f(0.F, .1F, 0.F), "SAVE CIRCUIT", B_SAVE);
	buttonsVector.push_back(*buttPtr);
    buttPtr = nullptr;
    delete buttPtr;
}

void OGWindow::menuRightClic( int Option )
{
    switch (Option) {
        case 1:
            cout << "Option 1 selected\n";
            break;
        case 2:
            cout << "Option 2 selected\n";
            break;
        case 3:
            cout << "Option 3 selected\n";
            exit( 0 );
    }
}

void OGWindow::menuAdd(int Option){
    eType t;
    //BATTERY, BULB, AMMETER, CAPACITOR, RESISTOR, COIL, CONNECTOR
    switch(Option){
        case 1:
            t = AMMETER;
            break;
        case 2:
            t = BATTERY;
            break;
        case 3:
            t = BULB;
            break;
        case 4:
            t = CAPACITOR;
            break;
        case 5:
            t = COIL;
            break;
        case 6:
            t = CONNECTOR;
            break;
        case 7:
            t = RESISTOR;
            break;
    }
    
    Component *compPtr = new Component;
    std::cout << wWidth << " " << wHeight << std::endl;
    compPtr->setX( rand()% (wWidth / 50) );
    compPtr->setY( rand()% (wHeight / 50) );
    compPtr->setType(t);
    
    compVector.push_back( *compPtr );
    glutPostRedisplay();
}

void OGWindow::deleteSquare( Component *squPtr )
{
	cout << "Deleting component " << squPtr->getIndex() << endl;
    compVector.erase(std::remove(compVector.begin(), compVector.end(), *squPtr), compVector.end());
}

void OGWindow::printComponents( void )
{
		vector<Component>::iterator constIterator;

		for ( constIterator = compVector.begin(); constIterator != compVector.end(); ++ constIterator){
			cout << setprecision( 2 );
			cout << "Num: " << constIterator->getIndex();
			cout << " ( " << constIterator->getX();
			cout << ", " << constIterator->getY() << " ) ";

			vector<Component *> links = constIterator->connections;
			vector<Component *>::iterator linkIterator;

			cout << "Links ";
			for ( linkIterator = links.begin(); linkIterator != links.end(); ++ linkIterator){
				cout << (*linkIterator)->getIndex() << " ";
			}
			cout << endl;

		}


}

void OGWindow::saveCircuit() {
	bool xml = true;
	if (xml) {
		using namespace tinyxml2;

		XMLDocument doc;

		XMLElement * circuit = doc.NewElement("Circuit");
		doc.InsertFirstChild(circuit);
		for (Component c : compVector) {
			XMLElement * compXml = doc.NewElement("Component");
            compXml->SetAttribute("Id", std::to_string(c.getIndex()).c_str());
			compXml->SetAttribute("Type", std::to_string(c.getType()).c_str());
			compXml->SetAttribute("Value", c.getValue());
			compXml->SetAttribute("Size", c.getSize());
			compXml->SetAttribute("posX", c.getX());
			compXml->SetAttribute("posY", c.getY());

			bool links = false;
			if (links) {
				XMLElement * linksXml = doc.NewElement("Links");
				vector<Component *> links = c.connections;
				vector<Component *>::iterator linkIterator;

				for (linkIterator = links.begin(); linkIterator != links.end(); ++linkIterator) {
					cout << (*linkIterator)->getIndex() << " ";
					XMLElement * linkXml = doc.NewElement("Link");
					linkXml->SetAttribute("Target", (*linkIterator)->getIndex());
					linksXml->InsertEndChild(linksXml);
				}
				compXml->InsertEndChild(linksXml);
			}
			
			circuit->InsertEndChild(compXml);


		}
        doc.Print();
		XMLError eResult = doc.SaveFile("circuit.xml");
	}
	


}

