#include "Component.h"


using namespace std;
// nextIndex is the index of the next component to be created
int Component::nextIndex = 1;

Component::Component( void )
{
	setType( RESISTOR );
	setValue( 0.0 );
	setX( 0.0 );
	setY( 0.0 );
	setSize( 2.0 );
	setIndex( nextIndex );
	// Increase nextIndex
	incIndex();

	
}

eType Component::getType( void )
{
	return cType;
}


double Component::getValue( void )
{
	return cValue;
}
double Component::getX( void )
{
	return cX;
}
double Component::getY( void )
{
	return cY;
}

double Component::getSize( void )
{
	return cSize;
}

void Component::setType( eType type )
{
	cType = type;
    if(type == CONNECTOR)
        setSize(0.5);
}

void Component::setValue( double value )
{
	cValue = value;
}
void Component::setX( double x)
{
	cX = x;
}

void Component::setY( double y )
{
	cY = y;
}


void Component::setSize( double size )
{
	cSize = size;
}

int Component::getIndex( void )
{
	return index;
}
		

void Component::setIndex( int n )
{
	index = n;

}
void Component::incIndex( void )
{
	nextIndex += 1;
}

void Component::draw(){
    
    glColor3f(0.F, 0.F, 0.F);
    drawCircle(cX, cY, cSize/2, true);
    
    float x;
    
    switch(cType){
        case BATTERY:
            glBegin(GL_LINES);
            glVertex2f(cX - cSize / 2, cY);
            glVertex2f(cX - cSize / 10, cY);
            glVertex2f(cX - cSize / 10, cY - cSize / 2);
            glVertex2f(cX - cSize / 10, cY + cSize / 2);
            glVertex2f(cX + cSize / 10, cY - cSize / 4);
            glVertex2f(cX + cSize / 10, cY + cSize / 4);
            glVertex2f(cX + cSize / 10, cY);
            glVertex2f(cX + cSize / 2, cY);
            glEnd();
            
            break;
        case BULB:
            glBegin(GL_LINE);
            glVertex2f(cX - cSize / 2, cY);
            glVertex2f(cX + cSize / 2, cY);
            glEnd();
            drawCircle(cX, cY, cSize/3,true);
            
            break;
        case AMMETER:
            glBegin(GL_LINE_STRIP);
            glVertex2f(cX - cSize/4, cY - cSize/4);
            glVertex2f(cX, cY + cSize/4);
            glVertex2f(cX + cSize/4, cY - cSize/4);
            glEnd();
            break;
        case RESISTOR:
            glBegin(GL_LINE_STRIP);
            glVertex2f(cX - cSize / 2, cY);
            glVertex2f(cX - cSize / 4, cY + cSize / 3);
            glVertex2f(cX - cSize / 4, cY - cSize / 3);
            glVertex2f(cX, cY + cSize / 3);
            glVertex2f(cX, cY - cSize / 3);
            glVertex2f(cX + cSize / 4, cY + cSize / 3);
            glVertex2f(cX + cSize / 4, cY - cSize / 3);
            glVertex2f(cX + cSize / 2, cY);
            glEnd();
            
            break;
        case CAPACITOR:
            glBegin(GL_LINES);
            glVertex2f(cX - cSize / 2, cY);
            glVertex2f(cX - cSize / 10, cY);
            glVertex2f(cX - cSize / 10, cY - cSize / 3);
            glVertex2f(cX - cSize / 10, cY + cSize / 3);
            glVertex2f(cX + cSize / 10, cY - cSize / 3);
            glVertex2f(cX + cSize / 10, cY + cSize / 3);
            glVertex2f(cX + cSize / 10, cY);
            glVertex2f(cX + cSize / 2, cY);
            glEnd();
            
            break;
        case COIL:
            x = cX - cSize/4;
            glBegin(GL_LINE_STRIP);
            glVertex2f(cX - cSize/2, cY);
            for (int i=0; i <= 360 * 4.5; i++)
            {
                float degInRad = i*DEG2RAD;
                glVertex2f(x - cos(degInRad)* cSize/8,
                           cY + sin(degInRad)* cSize/4);
                x += 0.0003 * cSize;
            }
            glVertex2f(cX + cSize/2, cY);
            glEnd();
            
            break;
        case CONNECTOR:
            glBegin(GL_LINES);
            glVertex2f(cX - cSize/2, cY - cSize/2);
            glVertex2f(cX + cSize/2, cY + cSize/2);
            glVertex2f(cX + cSize/2, cY - cSize/2);
            glVertex2f(cX - cSize/2, cY + cSize/2);
            glEnd();
            break;
            
    }
    glEnable(GL_DEPTH_TEST);
}

bool Component::operator==(const Component& c) const{
    return this->index == c.index;
}
