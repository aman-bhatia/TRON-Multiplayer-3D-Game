/**
 * \class Bike
 */

#ifndef BIKE_H
#define BIKE_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "Co-ordinates.h"
#include "objloader.h"


/** 
 * \defgroup BIKE_VARIABLES Bike variables 
 * @{
 */
extern int lol;
extern float c;
extern float p[12];
extern float wall_height;
/** @} */

struct color{
	float r,g,b;
	color(float a,float b,float c);
};
 

struct line{
	cord end1,end2;
};

///Simple class for defining bike objects.
class Bike{
	public:
		int lifetime;					///<time for explosion after death
		color* clr;						///<color of bike
		cord vel;						///<velocity of bike
		cord prev_vel;					///<previous velocity of bike
		objloader* obj;					///<pointer to wavefront .obj file
		int bike_mesh;					///<pointer to glGenList containing 3D bike mesh
		std::string dir;				///<direction of bike
		std::string prev_dir;			///<previous direction of bike
		std::vector<line> *hwall;		///<vector containing coordinates of horizontal walls
		std::vector<line> *vwall;		///<vector containing coordinates of vertical walls
		int bikenum;					///<unique identifier of bike
		cord pos;						///<position of bike
		cord ppos;						///<previous position of bike
		cord ptpos;						///<previous turn position of bike
		bool alive;						///<boolean containing if the bike is alive or not
		bool artificial;				///<true if this bike is computer player
		bool morealive;
        	int turn;					///< Right turn if turn is one else left turn

		///Draw the walls at the back of the bike
        	void drawwalls();
		///Constructor of bike
		Bike();
		///Tell if a bike collides with a wall
		bool collide(cord ppos1, cord pos1, std::string s, int bikid);
		///Updates the position of the bike
		void move();
		///Equate the properties of two bikes
		void equate(Bike B);
		///Analyse the message received
		void message(float x, float y, int z);
};

#endif
