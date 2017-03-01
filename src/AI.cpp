#include "AI.h"
#include "Bike.h"
#include<cmath>
using namespace std;
#define infinity 5000
float length = 90, breadth = 90;//distance constant that needs to be decided finally
float dturn[10];

//for doing more than one player, you have to store an array of ppos of turn
//tough variable is present, see whether to keep it or not
AI::AI(int nofp, Bike* bik, bool t){
	pos.x = 0;
	pos.y = 0;
	ppos.x = 0;
	ppos.y = 0;
	pvel.x = 0;
	pvel.y = 0;
	vel.x = 0;
	vel.y = 0;
	nop = nofp;
	B = bik;
	counter = 0;
	tough = t;
	dir = "horizontal";
	dturn[0] = 0.05*90;
	dturn[1] = 0.35*90;
	dturn[2] = 0.55*90;
	dturn[3] = 0.15*90;
	dturn[4] = 0.85*90;
	dturn[5] = 1.15*90;
	dturn[6] = 0.65*90;
	dturn[7] = 0.75*90;
	dturn[8] = 1.55*90;
	dturn[9] = 0.85*90;
}

int AI::update(cord position, cord velocity, std::string direction, int nofp, cord prvturnpos, int bikid){
	pos.x = position.x;
	pos.y = position.y;
	ppos.x = prvturnpos.x;
	ppos.y = prvturnpos.y;
	vel.x = velocity.x;
	vel.y = velocity.y;
	dir = direction;
	nop = nofp;
	float max = 0.2*90,min = 0.05*90, lol = 0,max1[6] = {0.12*90, 0.18*90, 0.22*90, 0.26*90, 0.30*90, 0.35*90};
	lol = closeness(bikid);
	#ifdef DEBUG
		if(lol != 0) cout<<"AI.cpp : lol = "<<lol<<endl;
	#endif
	if((abs(lol) < max1[bikid]) && (abs(lol) >= min)){
		if((abs(pos.x - ppos.x) >= min) || (abs(pos.y - ppos.y) >= min)){
			return validturn();
		}
	}
	if((abs(pos.x - ppos.x) >= dturn[counter]) || (abs(pos.y - ppos.y) >= dturn[counter])){
		if(abs(lol) >= min){
			if((abs(pos.x - ppos.x) >= dturn[counter]) || (abs(pos.y - ppos.y) >= dturn[counter])){
				#ifdef DEBUG
					cout<<"AI.cpp : counter = "<<counter<<endl;
				#endif
				counter = (counter+1)%10;
				lol = taketurn();
				return lol;
			}
		}
	}
//	counter++;
	return 0;
}

void AI::changes(int n){		//, Bike* bik){no need of bike*
	nop = n;
}

int AI::validturn(){			//see return types
	float c = infinity, d = infinity;
	if(dir == "horizontal"){
		for(int k=0;k<nop;k++){
			for(int i=0;i<B[k].hwall->size();i++){
				if(((B[k].hwall->at(i).end1.x <= pos.x) && (B[k].hwall->at(i).end2.x >= pos.x)) || ((B[k].hwall->at(i).end1.x >= pos.x) && (B[k].hwall->at(i).end2.x <= pos.x))){
					if(((B[k].hwall->at(i).end1.y - pos.y) > 0) && ((B[k].hwall->at(i).end1.y - pos.y) < c)){
						c = (B[k].hwall->at(i).end1.y - pos.y);
					}
					if(((pos.y - B[k].hwall->at(i).end1.y) > 0) && ((pos.y - B[k].hwall->at(i).end1.y) < d)){
						d = (pos.y - B[k].hwall->at(i).end1.y);
					}
				}
			}
		}
		if((breadth - pos.y) < c) c = (breadth - pos.y);
		if((pos.y + breadth) < d) d = (pos.y + breadth);
		#ifdef DEBUG
			cout<<"AI.cpp : c="<<c<<" "<<"d="<<d<<endl;
		#endif
		if(c >= d){//move up
			if(vel.x > 0) return 2;
			else return 1;
		}
		else{//move down
			if(vel.x > 0) return 1;
			else return 2;
		}
	}
	else{
		for(int k=0;k<nop;k++){
			for(int i=0;i<B[k].vwall->size();i++){
				if(((B[k].vwall->at(i).end1.y <= pos.y) && (B[k].vwall->at(i).end2.y >= pos.y)) || ((B[k].vwall->at(i).end1.y >= pos.y) && (B[k].vwall->at(i).end2.y <= pos.y))){
					#ifdef DEBUG
						cout<<"AI.cpp : yoho "<<B[k].vwall->at(i).end1.y<<" "<<B[k].vwall->at(i).end2.y<<" "<<pos.y<<endl;
					#endif
					if(((B[k].vwall->at(i).end1.x - pos.x) > 0) && ((B[k].vwall->at(i).end1.x - pos.x) < c)){
						c = (B[k].vwall->at(i).end1.x - pos.x);
					}
					if(((pos.x - B[k].vwall->at(i).end1.x) > 0) && ((pos.x - B[k].vwall->at(i).end1.x) < d)){
						d = (pos.x - B[k].vwall->at(i).end1.x);
					}
				}
			}
		}
		#ifdef DEBUG
			cout<<"AI.cpp : c="<<c<<" "<<"d="<<d<<" length="<<length<<endl;
		#endif
		if((length - pos.x) < c) c = (length - pos.x);
		if((pos.x + length) < d) d = (pos.x + length);
		#ifdef DEBUG
			cout<<"AI.cpp : c="<<c<<" "<<"d="<<d<<endl;
		#endif
		if(c > d){//move east
			if(vel.y > 0) return 1;
			else return 2;
		}
		else {//move west
			if(vel.y > 0) return 2;
			else return 1;
		}
	}
	return 0;
}

int AI::taketurn(){		//see probability of random turn
	int q = rand()%2;
	if(q) return validturn();
	return 0;
}

float AI::closeness(int bikid){//see return types
	float max = 0.2*90, max1[6] = {0.12*90, 0.18*90, 0.22*90, 0.26*90, 0.30*90, 0.35*90};
	if(dir == "horizontal"){
		if(abs(abs(pos.x) - length) < max1[bikid]){
			#ifdef DEBUG
				cout<<"AI.cpp : "<<1<<" "<<abs(abs(pos.x) - length)<<endl;
			#endif
			return abs(abs(pos.x) - length);//take valid turn
		}
		for(int k=0;k<nop;k++){
			for(int i=0;i<B[k].vwall->size();i++){
				if((abs(B[k].vwall->at(i).end1.x - pos.x) < max1[bikid]) && ((vel.x * (B[k].vwall->at(i).end1.x - pos.x)) > 0)){
					if((B[k].vwall->at(i).end1.y <= pos.y && B[k].vwall->at(i).end2.y >= pos.y) || (B[k].vwall->at(i).end1.y >= pos.y && B[k].vwall->at(i).end2.y <= pos.y)){
					#ifdef DEBUG
						cout<<"AI.cpp : "<<2<<" "<<abs(B[k].vwall->at(i).end1.x - pos.x)<<endl;
					#endif
					return abs(B[k].vwall->at(i).end1.x - pos.x);//take valid turn
					}
				}
			}
			for(int i=0;i<B[k].hwall->size();i++){
				if(pos.y == B[k].hwall->at(i).end1.y){
					if((bikid != B[k].bikenum) || ( i != (B[k].hwall->size()-1) )){
						if(abs(pos.x - B[k].hwall->at(i).end1.x) < max){
							return abs(pos.x - B[k].hwall->at(i).end1.x);
						}
						if(abs(pos.x - B[k].hwall->at(i).end2.x) < max){
							return abs(pos.x - B[k].hwall->at(i).end2.x);
						}
					}
				}
			}
		}
	}
	else{
		if(abs((abs(pos.y) - breadth)) < max1[bikid]){
			#ifdef DEBUG
				cout<<"AI.cpp : "<<3<<" "<<abs(abs(pos.y) - breadth)<<endl;
			#endif
			return abs(abs(pos.y) - breadth);//take valid turn
		}
		for(int k=0;k<nop;k++){
			for(int i=0;i<B[k].hwall->size();i++){
				if((abs(B[k].hwall->at(i).end1.y - pos.y) < max1[bikid]) && ((vel.y * (B[k].hwall->at(i).end1.y - pos.y)) > 0)){
					if((B[k].hwall->at(i).end1.x <= pos.x && B[k].hwall->at(i).end2.x >= pos.x) || (B[k].hwall->at(i).end1.x >= pos.x && B[k].hwall->at(i).end2.x <= pos.x)){
						#ifdef DEBUG
							cout<<"AI.cpp : "<<4<<" "<<abs(B[k].hwall->at(i).end1.y - pos.y)<<endl;
						#endif
						return abs(B[k].hwall->at(i).end1.y - pos.y);//take valid turn
					}
				}
			}
			for(int i=0;i<B[k].vwall->size();i++){
				if(pos.x == B[k].vwall->at(i).end1.x){
					if((bikid != B[k].bikenum) || ( i != (B[k].vwall->size()-1) )){
						if(abs(pos.y - B[k].vwall->at(i).end1.y) < max){
							return abs(pos.y - B[k].vwall->at(i).end1.y);
						}
						if(abs(pos.y - B[k].vwall->at(i).end2.y) < max){
							return abs(pos.y - B[k].vwall->at(i).end2.y);
						}
					}
				}
			}
		}
	}
	return infinity;
}

int AI::attackcloseplayer(){
	//If a player follows very closely then take a 'U' turn by which the player will obviously get trapped
}

int AI::trapabike(){
	//traps a bike which enters a 'U' shaped wall by closing the fourth side
}
