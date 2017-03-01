/**
 * \class AI
 */

#ifndef AI_H
#define AI_H
#include "Bike.h"

/** 
 * \defgroup AI_VARIABLES AI variables 
 * @{
 */

extern float d, min, length, breadth; 
/** @} */

/// Artificial Intelligence class for controling all the computer players. It uses both deterministic and probabilistic AI's
class AI{
	public:
		/// It coordinates all the functions used by the AI. It returns the turn to be taken.
		int update(cord position, cord velocity, std::string direction, int nofp, cord prvturnpos, int bikid);
		
		/// This function is called whenever someone dies and values are updated
		void changes(int n);

		///Constructor
		///It initializes all the variables used by the class
		AI(int nofp, Bike* bik, bool t);
	private:
		bool tough;				///<degree of toughness
		cord pos;				///<position of computer player
		cord vel;				///<velocity of computer player
		cord ppos;				///<previous position of computer player
		cord pvel;				///<previous velocity of computer player
		std::string dir;		///<direction of computer player
		int nop;				///<total number of players in the game
		int counter;			///<update every time someone dies
		Bike* B;				///<pointer to bike object
		
		///Deterministic function to take turn
		int validturn();
		
		///Probabilistic function to take turn
		int taketurn();

		///Returns distance from the obstacles(other player walls or arena wall) if it is within a certain limit
		float closeness(int bikid);

		///Attack a player if it was following
		int attackcloseplayer();
		
		///Traps a bike from the fourth side if it is surrounded by walls from three sides
		int trapabike();
};

#endif
