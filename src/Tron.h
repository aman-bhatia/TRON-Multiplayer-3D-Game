/**
 * \class Tron
 */


#ifndef TRON_H
#define TRON_H
#include "Network.h"
#include "AI.h"


/** 
 * \defgroup AI_VARIABLES AI variables 
 * @{
 */

extern int bid;
extern int port;
/** @} */

///Class which handles all the bikes present in the game
class Tron{
	public:
		int nop; ///< no. of players
		///Constructor to initialise all the bikes
		Tron(int n, bool single);
		///Every cycle it will maintain the bikes
		int handletron();
		Bike* B; ///< This is the array of bikes
		bool sp; ///< This tells whether the game is single player or not
		network* tnetwork; ///< This is the network object with which all the communication takes place
		network* cnetwork; ///< This is the network object with which all the communication takes place
		///Initialise the network
		void initnet();
	private:
		void update(int a);
		AI* ai;
};

#endif
