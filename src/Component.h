#pragma once
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif
#include <vector>
#include "util.hpp"

enum eType { BATTERY, BULB, AMMETER, CAPACITOR, RESISTOR, COIL, CONNECTOR };

class Component
{
	private:
		eType cType;
        int index;

		// The next component will have index = nextIndex
		// This is information that applies to the class as a whole
		// so we make it static
		static int nextIndex;
		double cValue;
		double cX;
		double cY;
		double cSize;
    
			
	public:

		Component( void );
		eType getType( void );
		double getValue( void );
		double getX( void );
		double getY( void );
		double getSize( void );
		int getIndex( void );
		void setIndex( int n );
		void incIndex( void );

		void setType( eType type );
		void setValue( double value );
		void setX( double x);
		void setY( double y );
		void setSize( double size );
    
        bool operator==(const Component& c) const;

		std::vector< Component * > connections;
    
        void draw();
};

//bool operator==(Component& rhs, Component& lhs){
//    return rhs.getIndex() == lhs.getIndex();
//};
