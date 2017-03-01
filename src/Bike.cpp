#include "Bike.h"
#include "Graphics.h"
using namespace std;

int lol = 0;
float c = 0.45;
float p[12] = {0.5*90, -0.5*90, 0.5*90, 0.5*90, -0.4*90, 0.7*90, 0.1*90, -0.5*90, 0.2*90, 0, -0.8*90 ,0};
float wall_height = 1.2;

color::color(float a,float b,float c)
{
	r=a;
	g=b;
	b=c;
}

Bike::Bike(){
	lifetime = 100;
	alive = true;
	morealive = true;
	artificial = false;
	turn = 0;
	prev_vel.y = 0;
	obj = new objloader;
	bike_mesh = obj->load("wavefront_obj/bike.obj");
}

//right is positive, up is positive, left is negative, down is negative, 1 is turn right, 2 is turn left

bool Bike::collide(cord ppos1, cord pos1, string s, int bikid){
	if(s == "vertical"){
//	cout<<hwall->size()<<endl;
		for(int i=0; i < hwall->size(); i++){
			if(((pos1.y >= hwall->at(i).end1.y) && (ppos1.y < hwall->at(i).end1.y)) || ((pos1.y <= hwall->at(i).end1.y) && (ppos1.y > hwall->at(i).end1.y))){
				if(((hwall->at(i).end1.x >= pos1.x) && (hwall->at(i).end2.x <= ppos1.x)) || ((hwall->at(i).end1.x <= pos1.x) && (hwall->at(i).end2.x >= ppos1.x))){
					return true;
				}
			}
		}
		for(int i=0; i < vwall->size(); i++){
			if(pos1.x == vwall->at(i).end1.x){
//				if((bikenum != bikid) || (i != (vwall->size()-1))){
					if((pos1.y > vwall->at(i).end1.y && ppos1.y < vwall->at(i).end1.y) || (pos1.y < vwall->at(i).end1.y && ppos1.y > vwall->at(i).end1.y)){
						return true;
					}
					if((pos1.y > vwall->at(i).end2.y && ppos1.y < vwall->at(i).end2.y) || (pos1.y < vwall->at(i).end2.y && ppos1.y > vwall->at(i).end2.y)){
						return true;
					}
//					cout<<pos1.y<<" "<<vwall->at(i).end2.y<<" "<<vwall->at(i).end1.y<<endl;
					if((pos1.y > vwall->at(i).end2.y && pos1.y < vwall->at(i).end1.y) || (pos1.y < vwall->at(i).end2.y && pos1.y > vwall->at(i).end1.y)){
						return true;
					}
//				}
			}
		}
	}
	else{
//		cout<<vwall->size()<<endl;
		for(int i=0; i < vwall->size(); i++){
			if(((pos1.x >= vwall->at(i).end1.x) && (ppos1.x < vwall->at(i).end1.x)) || ((pos1.x <= vwall->at(i).end1.x) && (ppos1.x > vwall->at(i).end1.x))){
				if(((vwall->at(i).end1.y >= pos1.y) && (vwall->at(i).end2.y <= ppos1.y)) || ((vwall->at(i).end1.y <= pos1.y) && (vwall->at(i).end2.y >= ppos1.y))){
					return true;
				}
			}
		}
		for(int i=0; i < hwall->size(); i++){
			if(pos1.y == hwall->at(i).end1.y){
//				cout<<"y cordinates are equal\n";
//				if((bikenum != bikid) || (i != (hwall->size()-1))){
					if((pos1.x > hwall->at(i).end1.x && ppos1.x < hwall->at(i).end1.x) || (pos1.x < hwall->at(i).end1.x && ppos1.x > hwall->at(i).end1.x)){
						return true;
					}
					if((pos1.x > hwall->at(i).end2.x && ppos1.x < hwall->at(i).end2.x) || (pos1.x < hwall->at(i).end2.x && ppos1.x > hwall->at(i).end2.x)){
						return true;
					}
					if((pos1.x > hwall->at(i).end2.x && pos1.x < hwall->at(i).end1.x) || (pos1.x < hwall->at(i).end2.x && pos1.x > hwall->at(i).end1.x)){
						return true;
					}
//				}
			}
		}
	}
}


void Bike::move(){
	if(turn == 0){
		if(dir == "horizontal"){
			ppos.x = pos.x;
			pos.x += vel.x;
			hwall->at(hwall->size() - 1).end2.x = pos.x;
		}
		else{	//vertical
			ppos.y = pos.y;
			pos.y += vel.y;
			vwall->at(vwall->size() - 1).end2.y = pos.y;
		}
		return;
	}
	else{
		if(turn == 1){	//turn right
			ptpos.x = pos.x;
			ptpos.y = pos.y;
			turn = 0;
			if(dir == "horizontal"){
				dir = "vertical";
				vel.y = -vel.x;
				vel.x = 0;
				hwall->at(hwall->size() - 1).end2.x = pos.x;
				ppos.x = pos.x;
				ppos.y = pos.y;
				pos.y += vel.y;
				line temp;
				temp.end1.x = ppos.x;
				temp.end1.y = ppos.y;
				temp.end2.x = pos.x;
				temp.end2.y = pos.y;
				vwall->push_back(temp);
			}
			else{
				dir = "horizontal";
				vel.x = vel.y;
				vel.y = 0;
				vwall->at(vwall->size() - 1).end2.y = pos.y;
				ppos.x = pos.x;
				ppos.y = pos.y;
				pos.x += vel.x;
				line temp;
				temp.end1.x = ppos.x;
				temp.end1.y = ppos.y;
				temp.end2.x = pos.x;
				temp.end2.y = pos.y;
				hwall->push_back(temp);
			}
				#ifdef DEBUG
					cout<<dir<<endl;
					cout<<hwall->size()<<endl;
				#endif
			turn = 0;
			return;
		}
		else{
			if(turn == 2){
				ptpos.x = pos.x;
				ptpos.y = pos.y;
				turn = 0;
				if(dir == "horizontal"){
					dir = "vertical";
					vel.y = vel.x;
					vel.x = 0;
					hwall->at(hwall->size() - 1).end2.x = pos.x;
					ppos.x = pos.x;
					ppos.y = pos.y;
					pos.y += vel.y;
					line temp;
					temp.end1.x = ppos.x;
					temp.end1.y = ppos.y;
					temp.end2.x = pos.x;
					temp.end2.y = pos.y;
					vwall->push_back(temp);
				}
				else{
					dir = "horizontal";
					vel.x = -vel.y;
					vel.y = 0;
					vwall->at(vwall->size() - 1).end2.y = pos.y;
					ppos.x = pos.x;
					ppos.y = pos.y;
					pos.x += vel.x;
					line temp;
					temp.end1.x = ppos.x;
					temp.end1.y = ppos.y;
					temp.end2.x = pos.x;
					temp.end2.y = pos.y;
					hwall->push_back(temp);
				}
				#ifdef DEBUG
					cout<<dir<<endl;
					cout<<vwall->size()<<endl;
				#endif
				turn = 0;
				return;
			}
		}
	}
}

void Bike::equate(Bike B){
	//write equate function for alive, vectors
	vwall = B.vwall;
	hwall = B.hwall;
	alive = B.alive;//B[nop].alive can be replaced by true
	pos.x = B.pos.x;
	pos.y = B.pos.y;
	ppos.x = B.ppos.x;
	ppos.y = B.ppos.y;
	vel.x = B.vel.x;
	vel.y = B.vel.y;
	dir = B.dir;
	artificial = B.artificial;
}


void Bike::drawwalls(){
	GLfloat black1[] = {3.0/255.0 , 1.0 , 1.0 , 0.5};
	GLfloat whitish[] = {0.1 , 0.1 , 0.1 , 0.15};
	GLfloat white1[] = {1.0 , 1.0 , 1.0 , 0.15};
	glMaterialfv(GL_FRONT , GL_AMBIENT , whitish);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , black1);
	glMaterialfv(GL_FRONT , GL_SPECULAR , white1);
	glMaterialf(GL_FRONT , GL_SHININESS , 75.0);

    for(int i = 0 ; i < vwall->size(); i++){
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);glVertex3f(vwall->at(i).end1.x , -0.77 + wall_height , vwall->at(i).end1.y);
			glTexCoord2f(1,0);glVertex3f(vwall->at(i).end1.x , -0.77 + wall_height , vwall->at(i).end2.y);
			glTexCoord2f(1,1);glVertex3f(vwall->at(i).end1.x , -0.77 , vwall->at(i).end2.y);
			glTexCoord2f(0,1);glVertex3f(vwall->at(i).end1.x , -0.77 , vwall->at(i).end1.y);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);glVertex3f(vwall->at(i).end1.x , -0.77 + wall_height , vwall->at(i).end2.y);
			glTexCoord2f(1,0);glVertex3f(vwall->at(i).end1.x , -0.77 + wall_height , vwall->at(i).end1.y);
			glTexCoord2f(1,1);glVertex3f(vwall->at(i).end1.x , -0.77 , vwall->at(i).end1.y);
			glTexCoord2f(0,1);glVertex3f(vwall->at(i).end1.x , -0.77 , vwall->at(i).end2.y);
		glEnd();
	}
	for(int i = 0 ; i < hwall->size(); i++){
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);glVertex3f(hwall->at(i).end1.x , -0.77 + wall_height , hwall->at(i).end1.y);
			glTexCoord2f(1,0);glVertex3f(hwall->at(i).end2.x , -0.77 + wall_height , hwall->at(i).end1.y);
			glTexCoord2f(1,1);glVertex3f(hwall->at(i).end2.x , -0.77 , hwall->at(i).end1.y);
			glTexCoord2f(0,1);glVertex3f(hwall->at(i).end1.x , -0.77 , hwall->at(i).end1.y);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);glVertex3f(hwall->at(i).end2.x , -0.77 + wall_height , hwall->at(i).end1.y);
			glTexCoord2f(1,0);glVertex3f(hwall->at(i).end1.x , -0.77 + wall_height , hwall->at(i).end1.y);
			glTexCoord2f(1,1);glVertex3f(hwall->at(i).end1.x , -0.77 , hwall->at(i).end1.y);
			glTexCoord2f(0,1);glVertex3f(hwall->at(i).end2.x , -0.77 , hwall->at(i).end1.y);
		glEnd();
	}
}

void Bike::message(float x, float y, int z){
	if(dir == "horizontal"){
		hwall->at(hwall->size() - 1).end2.y = y;
		hwall->at(hwall->size() - 1).end2.x = x;
		dir = "vertical";
		if(z == 1){
			vel.y = -vel.x;
			vel.x = 0;
		}
		else{
			vel.y = vel.x;
			vel.x = 0;
		}
		pos.x = x;
		pos.y = y;
		ppos.x = pos.x;
		ppos.y = pos.y;
		pos.y += vel.y;
		line temp;
		temp.end1.x = ppos.x;
		temp.end1.y = ppos.y;
		temp.end2.x = pos.x;
		temp.end2.y = pos.y;
		vwall->push_back(temp);
	}
	else{
		vwall->at(vwall->size() - 1).end2.y = y;
		vwall->at(vwall->size() - 1).end2.x = x;
		dir = "horizontal";
		if(z == 1){
			vel.x = vel.y;
			vel.y = 0;
		}
		else{
			vel.x = -vel.y;
			vel.y = 0;
		}
		pos.x = x;
		pos.y = y;
		ppos.x = pos.x;
		ppos.y = pos.y;
		pos.x += vel.x;
		line temp;
		temp.end1.x = ppos.x;
		temp.end1.y = ppos.y;
		temp.end2.x = pos.x;
		temp.end2.y = pos.y;
		hwall->push_back(temp);
	}
}
