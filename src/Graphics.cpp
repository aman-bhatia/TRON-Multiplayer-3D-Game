#include "Graphics.h"
#include "GL/freeglut.h"

#define WIN 4
#define LOSS 5
#define DISCON 6

bool loss = false;
bool win = false;
bool disconn = false;


/*-------------------------------------- EXPLOSION ------------------------------------------*/
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>
using namespace std;

#define NUM_PARTICLES    2000          /* Number of particles  */
#define NUM_DEBRIS       700            /* Number of debris     */

struct particleData
{
	float   position[3];
	float   speed[3];
	float   color[3];
};
typedef struct particleData particleData;


struct debrisData
{
	float   position[3];
	float   speed[3];
	float   orientation[3];        /* Rotation angles around x, y, and z axes */
	float   orientationSpeed[3];
	float   color[3];
	float   scale[3];
};
typedef struct debrisData    debrisData;

particleData     particles[NUM_PARTICLES];
debrisData       debris[NUM_DEBRIS];   

void newSpeed (float dest[3]) {
	float    x;
	float    y;
	float    z;
	float    len;

	x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
	y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
	z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;


	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}

void newExplosion (int bik_id) {

	for (int i=0; i < NUM_PARTICLES; i++) {
		particles[i].position[0] = a->B[bik_id-1].pos.x;
		particles[i].position[1] = -0.75;
		particles[i].position[2] = a->B[bik_id-1].pos.y;

		particles[i].color[0] = 1.0;
		particles[i].color[1] = 1.0;
		particles[i].color[2] = 0.5;

		newSpeed (particles[i].speed);
	}

	for (int i=0; i < NUM_DEBRIS; i++) {
		debris[i].position[0] = a->B[bik_id-1].pos.x;
		debris[i].position[1] = -0.75;
		debris[i].position[2] = a->B[bik_id-1].pos.y;

		debris[i].orientation[0] = 0.0;
		debris[i].orientation[1] = 0.0;
		debris[i].orientation[2] = 0.0;

		debris[i].color[0] = 0.7;
		debris[i].color[1] = 0.7;
		debris[i].color[2] = 0.7;

		debris[i].scale[0] = (2.0 * 
				((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
		debris[i].scale[1] = (2.0 * 
				((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
		debris[i].scale[2] = (2.0 * 
				((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

		newSpeed (debris[i].speed);
		newSpeed (debris[i].orientationSpeed);
	}
}

/*-------------------------------------- EXPLOSION ------------------------------------------*/


int count23 = 0, lost = -1;
int lol23[6] = {0,0,0,0,0,0};

int bid_collided = -1;
Tron* a;
int width = 700 , height = 700,pl=0,mi=0;
float anglex , angley , anglez;
bool onPause = 0 , onMouse = 0;
float offset = 6.0, cam_height = 1.2;
int explosion_counter = 0;

float zoom = 0.5f;

GLuint *texid;
GLuint loadTexture(Image *image)
{
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLuint textureid;
	glGenTextures(1 , &textureid);
	glBindTexture(GL_TEXTURE_2D , textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width,
		image->height , 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureid;
}

void init(void)
{
	Image *image = loadBMP("images/tabler.bmp");
	texid[0] = loadTexture(image);
	image = loadBMP("images/walls.bmp");
	texid[1] = loadTexture(image);
	image = loadBMP("images/floor.bmp");
	texid[2] = loadTexture(image);
	image = loadBMP("images/ceiling.bmp");
	texid[3] = loadTexture(image);
	image = loadBMP("images/win.bmp");
	texid[4] = loadTexture(image);
	image = loadBMP("images/loss.bmp");
	texid[5] = loadTexture(image);
	image = loadBMP("images/disconnected.bmp");
	texid[6] = loadTexture(image);
	delete image;
}
void initialise(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_DECAL);
	glEnable(GL_CULL_FACE);
}
void drawtable(void)
{
	glBindTexture(GL_TEXTURE_2D, texid[0]);
	//Start of table top
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(90.0 , -0.77 , 90.0);
		glTexCoord2f(1,0);glVertex3f(90.0 , -0.77 , -90.0);
		glTexCoord2f(1,1);glVertex3f(-90.0 , -0.77 , -90.0);
		glTexCoord2f(0,1);glVertex3f(-90.0 , -0.77 , 90.0);
	glEnd();
	//End of table top
}

void drawroom(void)
{
	glBindTexture(GL_TEXTURE_2D, texid[1]);
	//Start of walls
	glBegin(GL_QUADS);
		glTexCoord2f(0.0 , 0.0);glVertex3f(-90.0 , -3.0 , -90.0);
		glTexCoord2f(1.0 , 0.0);glVertex3f(90.0 , -3.0 , -90.0);
		glTexCoord2f(1.0 , 1.0);glVertex3f(90.0 , 40.0 , -90.0);
		glTexCoord2f(0.0 , 1.0);glVertex3f(-90.0 , 40.0 , -90.0);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0 , 0.0);glVertex3f(-90.0 , -3.0 , 90.0);
		glTexCoord2f(1.0 , 0.0);glVertex3f(-90.0 , -3.0 , -90.0);
		glTexCoord2f(1.0 , 1.0);glVertex3f(-90.0 , 40.0 , -90.0);
		glTexCoord2f(0.0 , 1.0);glVertex3f(-90.0 , 40.0 , 90.0);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0 , 0.0);glVertex3f(90.0 , -3.0 , 90.0);
		glTexCoord2f(1.0 , 0.0);glVertex3f(-90.0 , -3.0 , 90.0);
		glTexCoord2f(1.0 , 1.0);glVertex3f(-90.0 , 40.0 , 90.0);
		glTexCoord2f(0.0 , 1.0);glVertex3f(90.0 , 40.0 , 90.0);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0 , 0.0);glVertex3f(90.0 , -3.0 , -90.0);
		glTexCoord2f(1.0 , 0.0);glVertex3f(90.0 , -3.0 , 90.0);
		glTexCoord2f(1.0 , 1.0);glVertex3f(90.0 , 40.0 , 90.0);
		glTexCoord2f(0.0 , 1.0);glVertex3f(90.0 , 40.0 , -90.0);
	glEnd();
	//End of walls
	//Start of ceiling
	glBindTexture(GL_TEXTURE_2D, texid[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0 , 0.0);glVertex3f(90.0 , 40.0 , -90.0);
		glTexCoord2f(1.0 , 0.0);glVertex3f(90.0 , 40.0 , 90.0);
		glTexCoord2f(1.0 , 1.0);glVertex3f(-90.0 , 40.0 , 90.0);
		glTexCoord2f(0.0 , 1.0);glVertex3f(-90.0 , 40.0 , -90.0);
	glEnd();
	//End of ceiling
}

void disabletexture(void)
{
	glDisable(GL_TEXTURE_2D);
}

void enablelights(void)
{
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER , GL_TRUE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	GLfloat amblight[] = {0.3 , 0.3 , 0.3 , 1.0};
	GLfloat diflight[] = {0.7 , 0.7 , 0.7 , 1.0};
	GLfloat speclight[] = {1.0 , 1.0 , 1.0 , 1.0};
	glLightfv(GL_LIGHT0 , GL_AMBIENT , amblight);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , diflight);
	glLightfv(GL_LIGHT0 , GL_SPECULAR , speclight);
	glLightfv(GL_LIGHT1 , GL_AMBIENT , amblight);
	glLightfv(GL_LIGHT1 , GL_DIFFUSE , diflight);
	glLightfv(GL_LIGHT1 , GL_SPECULAR , speclight);
	glLightfv(GL_LIGHT2 , GL_AMBIENT , amblight);
	glLightfv(GL_LIGHT2 , GL_DIFFUSE , diflight);
	glLightfv(GL_LIGHT2 , GL_SPECULAR , speclight);
	glLightfv(GL_LIGHT3 , GL_AMBIENT , amblight);
	glLightfv(GL_LIGHT3 , GL_DIFFUSE , diflight);
	glLightfv(GL_LIGHT3 , GL_SPECULAR , speclight);
	GLfloat lightposition1[] = {75.0f , 15.0f , -75.0f , 1.0};
	GLfloat lightposition2[] = {-75.0f , 15.0f , -75.0f , 1.0};
	GLfloat lightposition3[] = {75.0f , 15.0f , 75.0f , 1.0};
	GLfloat lightposition4[] = {-75.0f , 15.0f , 75.0f , 1.0};
	glLightfv(GL_LIGHT0 , GL_POSITION , lightposition1);
	glLightfv(GL_LIGHT1 , GL_POSITION , lightposition2);
	glLightfv(GL_LIGHT2 , GL_POSITION , lightposition3);
	glLightfv(GL_LIGHT3 , GL_POSITION , lightposition4);
}

void disablelights(void)
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHTING);
}

void drawbike(int bnum){
	float factor = (log(1 + (offset))/log(7));
	glPushMatrix();
		glColor3f(0,1,1);
		if(a->B[bnum].dir == "horizontal" && a->B[bnum].vel.x<0){
			glTranslatef(a->B[bnum].pos.x+1,-0.75,a->B[bnum].pos.y);
		} else if(a->B[bnum].dir == "horizontal" && a->B[bnum].vel.x>0){
			glTranslatef(a->B[bnum].pos.x-1,-0.75,a->B[bnum].pos.y);
		} else if(a->B[bnum].dir == "vertical" && a->B[bnum].vel.y>0) {
			glTranslatef(a->B[bnum].pos.x,-0.75,a->B[bnum].pos.y-1);
		} else if(a->B[bnum].dir == "vertical" && a->B[bnum].vel.y<0) {
			glTranslatef(a->B[bnum].pos.x,-0.75,a->B[bnum].pos.y+1);
		}
		glRotatef(-90.0, 1.0,0.0,0.0);
		if(a->B[bnum].dir == "horizontal" && a->B[bnum].vel.x<0){
			if (a->B[bnum].prev_vel.y>0){
				glRotatef(-90.0, 0.0,0.0,1.0);
				glRotatef(-90.0 * (factor), 0.0,0.0,1.0);
			} else{
				glRotatef(90.0, 0.0,0.0,1.0);
				glRotatef(90.0 * (factor), 0.0,0.0,1.0);
			}
		} else if(a->B[bnum].dir == "horizontal" && a->B[bnum].vel.x>0){
			if (a->B[bnum].prev_vel.y>0){
				glRotatef(-90.0, 0.0,0.0,1.0);
				glRotatef(90.0 * (factor), 0.0,0.0,1.0);
			} else if (a->B[bnum].prev_vel.y < 0){
				glRotatef(90.0, 0.0,0.0,1.0);
				glRotatef(-90.0 * (factor), 0.0,0.0,1.0);
			}
		} else if(a->B[bnum].dir == "vertical" && a->B[bnum].vel.y>0) {
			if (a->B[bnum].prev_vel.x>0) glRotatef(-90.0 * (factor), 0.0,0.0,1.0);
			else {
				glRotatef(180,0,0,1);
				glRotatef(90.0 * (factor), 0.0,0.0,1.0);
			}
		} else if(a->B[bnum].dir == "vertical" && a->B[bnum].vel.y<0) {
			if (a->B[bnum].prev_vel.x<0){
				glRotatef(180,0,0,1);
				glRotatef(-90.0 * (factor), 0.0,0.0,1.0);
			} else glRotatef(90.0 * (factor), 0.0,0.0,1.0);
		}

		glCallList(a->B[bnum].bike_mesh);       //draw the 3D mesh
	glPopMatrix();
}

void handlecamera(){
	if (offset<6.0) offset += c;

	// main cases
	if (a->B[bid-1].dir == "horizontal" && a->B[bid-1].vel.x>0 && offset>=6.0){
		gluLookAt(a->B[bid-1].hwall->back().end2.x - offset , cam_height , a->B[bid-1].hwall->back().end2.y - 0.05 ,
			  	  a->B[bid-1].hwall->back().end2.x , 0 , a->B[bid-1].hwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "horizontal" && a->B[bid-1].vel.x<0 && offset>=6.0){
		gluLookAt(a->B[bid-1].hwall->back().end2.x + offset , cam_height , a->B[bid-1].hwall->back().end2.y - 0.05 ,
			  	  a->B[bid-1].hwall->back().end2.x , 0 , a->B[bid-1].hwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "vertical" && a->B[bid-1].vel.y>0 && offset>=6.0){
		gluLookAt(a->B[bid-1].vwall->back().end2.x - 0.05 , cam_height , a->B[bid-1].vwall->back().end2.y - offset ,
			  	  a->B[bid-1].vwall->back().end2.x , 0 , a->B[bid-1].vwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "vertical" && a->B[bid-1].vel.y<0 && offset>=6.0){
		gluLookAt(a->B[bid-1].vwall->back().end2.x - 0.05 , cam_height , a->B[bid-1].vwall->back().end2.y + offset ,
			  	  a->B[bid-1].vwall->back().end2.x , 0 , a->B[bid-1].vwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	}
	// rotating animation
	else if (a->B[bid-1].dir == "vertical" && a->B[bid-1].vel.y>0 && a->B[bid-1].prev_dir=="horizontal" && a->B[bid-1].prev_vel.x>0){
		gluLookAt(a->B[bid-1].hwall->back().end2.x + offset  - 6.0 , cam_height , a->B[bid-1].hwall->back().end2.y - 0.05 ,
			  	  a->B[bid-1].vwall->back().end2.x , 0 , a->B[bid-1].vwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "vertical" && a->B[bid-1].vel.y>0 && a->B[bid-1].prev_dir=="horizontal" && a->B[bid-1].prev_vel.x<0){
		gluLookAt(a->B[bid-1].hwall->back().end2.x - offset + 6.0 , cam_height , a->B[bid-1].hwall->back().end2.y - 0.05 ,
			  	  a->B[bid-1].vwall->back().end2.x , 0 , a->B[bid-1].vwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "vertical" && a->B[bid-1].vel.y<0 && a->B[bid-1].prev_dir=="horizontal" && a->B[bid-1].prev_vel.x>0){
		gluLookAt(a->B[bid-1].hwall->back().end2.x + offset  - 6.0 , cam_height , a->B[bid-1].hwall->back().end2.y - 0.05 ,
			  	  a->B[bid-1].vwall->back().end2.x , 0 , a->B[bid-1].vwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "vertical" && a->B[bid-1].vel.y<0 && a->B[bid-1].prev_dir=="horizontal" && a->B[bid-1].prev_vel.x<0){
		gluLookAt(a->B[bid-1].hwall->back().end2.x - offset + 6.0 , cam_height , a->B[bid-1].hwall->back().end2.y - 0.05 ,
			  	  a->B[bid-1].vwall->back().end2.x , 0 , a->B[bid-1].vwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "horizontal" && a->B[bid-1].vel.x<0 && a->B[bid-1].prev_dir=="vertical" && a->B[bid-1].prev_vel.y>0){
		gluLookAt(a->B[bid-1].vwall->back().end2.x - 0.05 , cam_height , a->B[bid-1].vwall->back().end2.y + offset - 6.0 ,
			  	  a->B[bid-1].hwall->back().end2.x , 0 , a->B[bid-1].hwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "horizontal" && a->B[bid-1].vel.x>0 && a->B[bid-1].prev_dir=="vertical" && a->B[bid-1].prev_vel.y>0){
		gluLookAt(a->B[bid-1].vwall->back().end2.x - 0.05 , cam_height , a->B[bid-1].vwall->back().end2.y + offset - 6.0 ,
			  	  a->B[bid-1].hwall->back().end2.x , 0 , a->B[bid-1].hwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "horizontal" && a->B[bid-1].vel.x<0 && a->B[bid-1].prev_dir=="vertical" && a->B[bid-1].prev_vel.y<0){
		gluLookAt(a->B[bid-1].vwall->back().end2.x - 0.05 , cam_height , a->B[bid-1].vwall->back().end2.y - offset + 6.0 ,
			  	  a->B[bid-1].hwall->back().end2.x , 0 , a->B[bid-1].hwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	} else if (a->B[bid-1].dir == "horizontal" && a->B[bid-1].vel.x>0 && a->B[bid-1].prev_dir=="vertical" && a->B[bid-1].prev_vel.y<0){
		gluLookAt(a->B[bid-1].vwall->back().end2.x - 0.05 , cam_height , a->B[bid-1].vwall->back().end2.y - offset + 6.0 ,
			  	  a->B[bid-1].hwall->back().end2.x , 0 , a->B[bid-1].hwall->back().end2.y ,
				  0.0 , 1.0 , 0.0);
	}
}

void updateparticles (int bik_id) {
	if (a->B[bik_id-1].lifetime > 0) {
		for (int i=0; i < NUM_PARTICLES; i++) {
			particles[i].position[0] += particles[i].speed[0] * 0.2;
			particles[i].position[1] += particles[i].speed[1] * 0.2;
			particles[i].position[2] += particles[i].speed[2] * 0.2;

			particles[i].color[0] -= 1.0 / 500.0;
			if (particles[i].color[0] < 0.0) particles[i].color[0] = 0.0;
			
			particles[i].color[1] -= 1.0 / 100.0;
			if (particles[i].color[1] < 0.0) particles[i].color[1] = 0.0;

			particles[i].color[2] -= 1.0 / 50.0;
			if (particles[i].color[2] < 0.0) particles[i].color[2] = 0.0;
		}

		for (int i=0; i < NUM_DEBRIS; i++) {
			debris[i].position[0] += debris[i].speed[0] * 0.1;
			debris[i].position[1] += debris[i].speed[1] * 0.1;
			debris[i].position[2] += debris[i].speed[2] * 0.1;

			debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
			debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
			debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
		}
		--(a->B[bik_id-1].lifetime);
	}
}

void display(void)
{
	if(!a->sp){
//		if(clocker1.getElapsedTime() >= sf::seconds(1)){
//			cout<<"hi i'm here \n";
			a->cnetwork->send(fourints(0 , 0 , 0 , bid));
//			clocker1.restart();
//		}
//		if(clocker2.getElapsedTime() >= sf::seconds(1.1))
//		{
//			cout<<" I'm ehre"<<endl;
			std::stack<fourints> S = a->cnetwork->receive();
			/*if((a->B[bid - 1].morealive == false) && (a->B[bid - 1].alive) && !S.empty()){
				a->B[bid - 1].alive = true;
				a->B[bid - 1].morealive = true;
				a->B[bid - 1].pos.x = c;
				a->B[bid - 1].pos.y = 0;
				a->B[bid - 1].ppos.x = 0;
				a->B[bid - 1].ppos.y = 0;
				a->B[bid - 1].ptpos.x = 0;
				a->B[bid - 1].ptpos.y = 0;
				a->B[bid - 1].vel.x = c;
				a->B[bid - 1].vel.y = 0;
				a->B[bid - 1].dir = "horizontal";
				a->B[bid - 1].hwall = new vector<line> [1];
				line temp;
				temp.end1.x = a->B[bid- 1].ppos.x;
				temp.end1.y = a->B[bid - 1].ppos.y;
				temp.end2.x = a->B[bid - 1].pos.x;
				temp.end2.y = a->B[bid - 1].pos.y;
				a->B[bid - 1].hwall->push_back(temp);
				a->B[bid - 1].vwall = new vector <line> [1];
			}*/
			if(S.empty())
			{
				count23++;
				if(count23 == 800){
					//onPause = true;
					disconn = true;
					glutLeaveMainLoop();
					a->cnetwork->send(fourints(0, 0, 0, bid));
				}
			}
			else
			{
				count23 = 0;
				int lol[6] = {0 , 0 , 0 , 0 , 0 , 0};
				for(int i=0;i<S.size();i++){
					fourints temp = S.top();
					S.pop();
					lol[temp.d - 1] = 1;
				}
	/*			if((lost >= 0) && (lol[lost] >= 1)){
					a->B[lost].alive = true;
					a->B[lost].morealive = true;
					a->B[lost].pos.x = c;
					a->B[lost].pos.y = 0;
					a->B[lost].ppos.x = 0;
					a->B[lost].ppos.y = 0;
					a->B[lost].ptpos.x = 0;
					a->B[lost].ptpos.y = 0;
					a->B[lost].vel.x = c;
					a->B[lost].vel.y = 0;
					a->B[lost].dir = "horizontal";
					a->B[lost].hwall = new vector<line> [1];
					line temp;
					temp.end1.x = a->B[lost].ppos.x;
					temp.end1.y = a->B[lost].ppos.y;
					temp.end2.x = a->B[lost].pos.x;
					temp.end2.y = a->B[lost].pos.y;
					a->B[lost].hwall->push_back(temp);
					a->B[lost].vwall = new vector <line> [1];
				}*/
				for(int i=0;i<a->nop;i++){
					if(a->B[i].alive && a->B[i].morealive){
						if(bid != (i+1) && lol[i] == 0){
							lol23[i]++;
							if(lol23[i] == 800){
								cout<<i<<" has been not sending messages\n";
								a->B[i].morealive = false;
								a->B[i].alive = false;
								lost = i;
								lol23[i] = 0;
							}
						}
						if(lol[i] !=0){
							lol23[i] = 0;
						}
					}
				}
			}			
//			clocker2.restart();
//		}
	}

	if (!onPause){
		initialise();
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60,1.0 * width / height, 0.1, 100 );
		handlecamera();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glRotatef(anglex , 1 , 0 , 0);
		glRotatef(angley , 0 , 1 , 0);
		drawroom();
		drawtable();
		disabletexture();
		enablelights();
		
		int temp = a->handletron();
		if (temp>=0){
			bid_collided = temp;
			newExplosion(bid_collided);
		}
		if (bid_collided>=0 && a->B[bid_collided-1].lifetime > 0){
	    	glPushMatrix ();
				disablelights();
				glDisable (GL_DEPTH_TEST);
				glBegin (GL_POINTS);
					for (int i = 0; i < NUM_PARTICLES; i++) {
						glColor3fv (particles[i].color);
						glVertex3fv (particles[i].position);
					}
				glEnd ();
			glPopMatrix ();

			enablelights();
			glEnable (GL_DEPTH_TEST);

			glNormal3f (0.0, 0.0, 1.0);

			for (int i=0; i < NUM_DEBRIS; i++) {
				glColor3fv (debris[i].color);

				glPushMatrix ();
					glTranslatef (debris[i].position[0], debris[i].position[1], debris[i].position[2]);
					glRotatef (debris[i].orientation[0], 1.0, 0.0, 0.0);
					glRotatef (debris[i].orientation[1], 0.0, 1.0, 0.0);
					glRotatef (debris[i].orientation[2], 0.0, 0.0, 1.0);
					glScalef (debris[i].scale[0], debris[i].scale[1], debris[i].scale[2]);
					glBegin (GL_TRIANGLES);
						glVertex3f (0.0, 0.5, 0.0);
						glVertex3f (-0.25, 0.0, 0.0);
						glVertex3f (0.25, 0.0, 0.0);
					glEnd ();	  
				glPopMatrix ();
			}
			updateparticles(bid_collided);
    	}
	
		for(int i=0;i<a->nop;i++){
			if(a->B[i].alive && a->B[i].morealive){
			drawbike(i);
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
			a->B[i].drawwalls();
			glDisable(GL_BLEND);
			}
		}

		glutSwapBuffers();
		disablelights();
	}

	// check if loss
	if(!a->B[bid-1].alive){
		usleep(100);
		if (explosion_counter >= 150){
			loss = true;
			glutLeaveMainLoop();
		}
		explosion_counter++;
	}

	//check if win
	bool all_other_dead = false;
	for (int i=0;i<a->nop;i++){
		if(i!=(bid-1) && a->B[i].alive) break;
		if (i==a->nop-1) all_other_dead = true;
	}
	if (all_other_dead && a->B[bid-1].alive){
		win = true;
		sleep(0.7);
		glutLeaveMainLoop();
	}
}

bool isfull = false;
int oldwidth , oldheight;


void handlearrows(int key , int x , int y)
{
	cord dummy , temp;
	switch(key)
	{
		case GLUT_KEY_LEFT :
			a->B[bid-1].prev_dir = a->B[bid-1].dir;
			a->B[bid-1].prev_vel = a->B[bid-1].vel;
			a->B[bid-1].turn = 1;
			offset = 0;
			if(!a->sp) (a->tnetwork)->send(fourints(a->B[bid-1].pos.x, a->B[bid-1].pos.y, a->B[bid-1].turn, bid));
			break;
		case GLUT_KEY_RIGHT :
			a->B[bid-1].prev_dir = a->B[bid-1].dir;
			a->B[bid-1].prev_vel = a->B[bid-1].vel;
			a->B[bid-1].turn = 2;
			offset = 0;
			if(!a->sp) (a->tnetwork)->send(fourints(a->B[bid-1].pos.x, a->B[bid-1].pos.y, a->B[bid-1].turn, bid));
			break;
	}
}


void handlekeypress(unsigned char key , int x , int y)
{
	cord dummy;
	switch(key)
	{
		case 32 :		// Spacebar
			onPause=1-onPause;
			break;
		case 27 :		// Escape
			exit(0);
			break;
	}
}


void changesize(int w , int h)
{

	oldwidth = width , oldheight = height;
	width = w , height = h;
	if(w < h) glutReshapeWindow(h , h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0 , 0 , width , height);
	gluPerspective(60.0 , 1.0 * width / height , 0.1 , 100.0);
	glutPostRedisplay();
}

void start_game(int argc , char **argv, int num_player, bool sin_pl)
{
	texid = new GLuint[7];
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100 , 100);
	glutInitWindowSize(1000 , 700);
	glutCreateWindow("Tron - The Legacy");
	glutKeyboardFunc(handlekeypress);
	glutSpecialFunc(handlearrows);

	a = new Tron(num_player,sin_pl);

	init();
	glutIdleFunc(display);
	glutReshapeFunc(changesize);
	glutFullScreen();
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();
	return;
}



void drawend(void)
{
	if(loss) glBindTexture(GL_TEXTURE_2D, texid[LOSS]);
	else if(win) glBindTexture(GL_TEXTURE_2D, texid[WIN]);
	else if(disconn) glBindTexture(GL_TEXTURE_2D, texid[DISCON]);
	//Start of walls
	glBegin(GL_QUADS);
		glTexCoord2f(0.0 , 0.0);glVertex3f(20.0 , -10.0 , 10.0);
		glTexCoord2f(1.0 , 0.0);glVertex3f(-20.0 , -10.0 , 10.0);
		glTexCoord2f(1.0 , 1.0);glVertex3f(-20.0 , 10.0 , 10.0);
		glTexCoord2f(0.0 , 1.0);glVertex3f(20.0 , 10.0 , 10.0);
	glEnd();
}

void displayend(void)
{
	initialise();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1.0 * width / height, 0.1, 100 );
	gluLookAt( 0,0,-10,
			   0,0,0,
			   0.0 , 1.0 , 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(anglex , 1 , 0 , 0);
	glRotatef(angley , 0 , 1 , 0);
	drawend();
	disabletexture();
	enablelights();

	glutSwapBuffers();
	disablelights();
}


void screenend(int argc , char **argv)
{
	texid = new GLuint[7];
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100 , 100);
	glutInitWindowSize(1000 , 700);
	glutCreateWindow("Game Over");
	glutKeyboardFunc(handlekeypress);
	glutSpecialFunc(handlearrows);

	init();
	glutIdleFunc(displayend);
	glutReshapeFunc(changesize);
	glutFullScreen();
	glutMainLoop();
	return;
}

