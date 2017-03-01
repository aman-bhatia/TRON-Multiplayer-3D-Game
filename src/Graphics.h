/**
 * \class Graphics
 */


#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <GL/glut.h>
#include "Bike.h"
#include "Tron.h"
#include "imageloader.h"


/** 
 * \defgroup BIKE_VARIABLES Bike variables 
 * @{
 */

extern Tron* a;
extern bool loss;
extern bool win;
extern bool disconn;
extern int width, height, pl, mi;
extern float anglex , angley , anglez;
extern bool onPause, onMouse;
extern float offset, cam_height;
extern float zoom;
extern bool isfull;
extern int oldwidth , oldheight;
extern GLuint *texid;
/** @} */

///Use to load the texture from an image
GLuint loadTexture(Image *image);
///Initialise some of the variables required for graphics
void init(void);
///Initialise different variables required for graphics
void initialise(void);
///Used to draw the floor of the room
void drawtable(void);
///Used to draw the walls and the ceiling of the room
void drawroom(void);
///Use to disable the textures
void disabletexture(void);
///Switch on the lights in the room
void enablelights(void);
///Switch off the lights in the room
void disablelights(void);
///Draw a bike described by the integer bnum
void drawbike(int bnum);
///Camera will always follow behind the bike it belongs to
void handlecamera();
///Main display function which uses all the other functions and finally creates the animation
void display(void);
///Handle the key presses inputted by the user
void handlearrows(int key , int x , int y);
///Used to handle different set of key presses by the user
void handlekeypress(unsigned char key , int x , int y);
///Handle the change in the size of the window
void changesize(int w , int h);
///Main function which handles the game and controls all the 3-D graphics
void start_game(int argc , char **argv, int num_player, bool sin_pl);

void drawend();
void displayend();
void screenend(int,char**);

#endif
