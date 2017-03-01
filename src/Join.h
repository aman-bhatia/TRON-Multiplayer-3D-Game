/**
 * \class Join
 */


#ifndef JOIN_H
#define JOIN_H

#include <string>
using namespace std;


/** 
 * \defgroup AI_VARIABLES AI variables 
 * @{
 */

extern string ip_address, port_num;
/** @} */
///Class used to create a client which connects to a server created on a different machine
class join{
public:
	///Get the id of self which is decided by the server it connects to
	int getindex(int *total);
};

extern void cli();

#endif
