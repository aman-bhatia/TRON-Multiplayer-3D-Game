/**
 * \class Co-ordinates
 */



#ifndef CO_ORDINATES_H
#define CO_ORDINATES_H

#define sqr(x) ((x) * (x))
#include <math.h>

///Class used for specifying the 3-D coordinates
class cord{
	public:
		double x,y,z;				///<x , y  , z co-ordinates in three dimensions
		///Constructor which initialises the three coordinates
		cord() {x=y=z=0;}
		///Function used to set the co-ordinates to a specifies value
		cord(float a , float b , float c) : x(a) , y(b) , z(c) {}
		///Magnitude of the vector represented in three dimensions
		double magnitude() {return sqrt(sqr(x)+sqr(y)+sqr(z));}
		///Gives the dot product of two vectors
		void dot(cord a, cord b){
			x=a.x*b.x;
			y=a.y*b.y;
			z=a.z*b.z;
		}
		///Add two vectors in three dimensions
		void add(cord a, cord b){
			x=a.x+b.x;
			y=a.y+b.y;
			z=a.z+b.z;
		}
		///Subtract two vectors in three dimensions
		void sub(cord a, cord b){
			x=a.x-b.x;
			y=a.y-b.y;
			z=a.z-b.z;
		}
		///Get the cross product of two vectors
		void cross(cord a, cord b){
			x=a.y*b.z-a.z*b.y;
			y=a.z*b.x-a.x*b.z;
			z=a.x*b.y-a.y*b.x;
		}
		///Multiply a vector with a constant
		void cons(double a, cord b){
			x=a*b.x;
			y=a*b.y;
			z=a*b.z;
		}
		///Get the sum of the three coordinates
		double sum(){ return (x+y+z);}
};

#endif
