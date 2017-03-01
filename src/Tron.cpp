#include "Bike.h"
#include "Tron.h"
#include "Join.h"
using namespace std;

int bid = 1;
int port = 2123;

Tron::Tron(int n, bool single){
	B = new Bike [n];
	nop = n;
	sp = single;
	if(sp) for(int i=1;i<nop;i++) B[i].artificial = true;
	for(int i=0;i<n;i++){
		B[i].bikenum = i;
		B[i].vel.x = c;
		B[i].vel.y = 0;
		B[i].pos.x = p[2*B[i].bikenum];
		B[i].pos.y = p[2*B[i].bikenum+1];
		B[i].pos.y = p[2*B[i].bikenum+1];
		B[i].ppos.x = B[i].pos.x;
		B[i].ppos.y = B[i].pos.y;
		B[i].ptpos.x = B[i].pos.x;
		B[i].ptpos.y = B[i].pos.y;
		B[i].hwall = new vector<line> [1];
				line temp;
				temp.end1.x = B[i].ppos.x;
				temp.end1.y = B[i].ppos.y;
				temp.end2.x = B[i].pos.x;
				temp.end2.y = B[i].pos.y;
				B[i].hwall->push_back(temp);
		B[i].vwall = new vector <line> [1];
		B[i].dir = "horizontal";
		if (B[i].bikenum == 0) B[i].clr = new color(1.0, 0.0, 0.0);
		else if (B[i].bikenum == 1) B[i].clr = new color(1.0, 0.0, 0.0);
		else if (B[i].bikenum == 2) B[i].clr = new color(0.0, 1.0, 0.0);
		else if (B[i].bikenum == 3) B[i].clr = new color(1.0, 1.0, 0.0);
		else if (B[i].bikenum == 4) B[i].clr = new color(1.0, 0.0, 1.0);
		else if (B[i].bikenum == 5) B[i].clr = new color(0.0, 1.0, 1.0);
	}
//	AI art(n,B,sp);
	ai = new AI(n,B,sp);
	if(!sp) initnet();
}

void Tron::initnet(){
	tnetwork = new network(bid , nop , atoi(port_num.c_str()) + 1);
	cnetwork = new network(bid , nop , atoi(port_num.c_str()) + 1 + 2000);
}

void Tron::update(int a){
	//fill the function equating B[a] with B[nop-1]; 
	nop--;
	B[a].equate(B[nop]);
}

int Tron::handletron(){
	int i,j;
	if(sp){					//single player
		for(i=0; i<nop; i++){
			if(B[i].artificial) B[i].turn = ai->update(B[i].pos,B[i].vel,B[i].dir,nop,B[i].ptpos,B[i].bikenum);
		}
		for(i=0;i<nop;i++){
			for(j=0;j<nop;j++){
			if(B[i].alive && B[j].alive){
					if(B[i].collide(B[j].ppos, B[j].pos, B[j].dir, B[j].bikenum)){
						B[j].alive = false;
						B[j].morealive = false;

						if (B[j].dir == "horizontal" && B[j].vel.x>0){
							B[j].vel.x = 0.0001;
						} else if (B[j].dir == "horizontal" && B[j].vel.x<0){
							B[j].vel.x = -0.0001;
						} else if (B[j].dir == "vertical" && B[j].vel.y>0){
							B[j].vel.y = 0.0001;
						} else if (B[j].dir == "vertical" && B[j].vel.y<0){
							B[j].vel.y = -0.0001;
						}
						#ifdef DEBUG
							cout<<"Tron.cpp : *******collide*********   "<<B[j].bikenum<<" withwall of "<<B[i].bikenum<<endl;
						#endif
						//update(j);
						return (j+1);
					}	
					else{
						if(B[j].dir == "vertical"){
							if((B[j].pos.y >= breadth) || (B[j].pos.y <= -breadth)){
								if (B[j].dir == "horizontal" && B[j].vel.x>0){
									B[j].vel.x = 0.0001;
								} else if (B[j].dir == "horizontal" && B[j].vel.x<0){
									B[j].vel.x = -0.0001;
								} else if (B[j].dir == "vertical" && B[j].vel.y>0){
									B[j].vel.y = 0.0001;
								} else if (B[j].dir == "vertical" && B[j].vel.y<0){
									B[j].vel.y = -0.0001;
								}
								#ifdef DEBUG
									cout<<"Tron.cpp : ********arena collide**********"<<endl;
								#endif
								//update(j);
								B[j].alive = false;
								B[j].morealive = false;
							return (j+1);
							}
						}
						else{
							if((B[j].pos.x >= length) || (B[j].pos.x <= -length)){
								if (B[j].dir == "horizontal" && B[j].vel.x>0){
									B[j].vel.x = 0.0001;
								} else if (B[j].dir == "horizontal" && B[j].vel.x<0){
									B[j].vel.x = -0.0001;
								} else if (B[j].dir == "vertical" && B[j].vel.y>0){
									B[j].vel.y = 0.0001;
								} else if (B[j].dir == "vertical" && B[j].vel.y<0){
									B[j].vel.y = -0.0001;
								}
								#ifdef DEBUG
									cout<<"Tron.cpp : ********arena collide**********"<<endl;
								#endif
								B[j].alive = false;
								B[j].morealive = false;
						//		update(j);
								return (j+1);
							}
						}
					}
				}
			}
		}
		for(i=0;i<nop;i++) B[i].move();
	}
	else {		//multiplayer
		stack<fourints> mess = (tnetwork)->receive();
		fourints temp(0 , 0 , 0 , 0);
		int collidedid = -1;
		while(mess.size()){
			temp = mess.top();
			mess.pop();
			if (temp.c != 3) (B[temp.d-1]).message(temp.a, temp.b, temp.c);
			//cout<<temp.a<<"  "<<temp.b<<"  "<<temp.c<<"  "<<temp.d<<endl;
			if(temp.c == 3){
				B[temp.d -1].alive = false;
				B[temp.d -1].morealive = false;
				collidedid = temp.d;
			}
		}
		if (collidedid >= 0) return collidedid;
		j = bid - 1;
		for(i=0;i<nop;i++){
			if(B[i].alive && B[j].alive){
				if(B[i].collide(B[j].ppos, B[j].pos, B[j].dir, B[j].bikenum)){
					B[j].alive = false;
					B[j].morealive = false;
					if (B[j].dir == "horizontal" && B[j].vel.x>0){
							B[j].vel.x = 0.0001;
						} else if (B[j].dir == "horizontal" && B[j].vel.x<0){
							B[j].vel.x = -0.0001;
						} else if (B[j].dir == "vertical" && B[j].vel.y>0){
							B[j].vel.y = 0.0001;
						} else if (B[j].dir == "vertical" && B[j].vel.y<0){
							B[j].vel.y = -0.0001;
						}
					#ifdef DEBUG
						cout<<"Tron.cpp : *******collide*********   "<<B[j].bikenum<<" withwall of "<<B[i].bikenum<<endl;
					#endif
					(tnetwork)->send(fourints(B[bid-1].pos.x, B[bid-1].pos.y, 3, bid));
					return (j+1);
				}	
				else{
					if(B[j].dir == "vertical"){
						if((B[j].pos.y >= breadth) || (B[j].pos.y <= -breadth)){
							#ifdef DEBUG
								cout<<"Tron.cpp : ********arena collide**********"<<endl;
							#endif
							if (B[j].dir == "horizontal" && B[j].vel.x>0){
								B[j].vel.x = 0.0001;
							} else if (B[j].dir == "horizontal" && B[j].vel.x<0){
								B[j].vel.x = -0.0001;
							} else if (B[j].dir == "vertical" && B[j].vel.y>0){
								B[j].vel.y = 0.0001;
							} else if (B[j].dir == "vertical" && B[j].vel.y<0){
								B[j].vel.y = -0.0001;
							}	
							B[j].alive = false;
							B[j].morealive = false;
							(tnetwork)->send(fourints(B[bid-1].pos.x, B[bid-1].pos.y, 3, bid));
							return (j+1);
						}
					}
					else{
						if((B[j].pos.x >= length) || (B[j].pos.x <= -length)){
							#ifdef DEBUG
								cout<<"Tron.cpp : ********arena collide**********"<<endl;
							#endif
							if (B[j].dir == "horizontal" && B[j].vel.x>0){
								B[j].vel.x = 0.0001;
							} else if (B[j].dir == "horizontal" && B[j].vel.x<0){
								B[j].vel.x = -0.0001;
							} else if (B[j].dir == "vertical" && B[j].vel.y>0){
								B[j].vel.y = 0.0001;
							} else if (B[j].dir == "vertical" && B[j].vel.y<0){
								B[j].vel.y = -0.0001;
							}
							B[j].alive = false;
							B[j].morealive = false;
							(tnetwork)->send(fourints(B[bid-1].pos.x, B[bid-1].pos.y, 3, bid));
							return (j+1);
						}
					}
				}
			}
		}
		for(i=0;i<nop;i++) B[i].move();
	}
	return -1;
}

