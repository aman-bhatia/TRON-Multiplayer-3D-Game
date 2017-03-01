/**
 * \class Network
 */



#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>
#include <iostream>
#include <unistd.h>
#include <stack>
#include <iostream>

extern std::string ipads[6];

struct fourints{
	float a , b;
	int c , d;
	fourints(float q , float w , int e , int r) : a(q) , b(w) , c(e) , d(r) {};
};

///The main class which handles all the peer to peer network connections.
class network{
	private:
		int myid , total; ///<The personal id's and the total number of computers in the network
		sf::TcpListener listener; ///< Listens for any incoming connections
		sf::TcpSocket *clienttome;///< The array which consists of all the clients to current computer
		sf::TcpSocket *clientiam; ///< The array which contains all the computers to which the current computer is a client
	public:
		///The constructor which takes in the self id and total number of computers in the peer to peer network and the port around which messages are exchanged
		network(int i , int j , int startport);
		///Receives all the messages from all the other computers in the peer to peer network and returns them as a stack
		std::stack<fourints> receive(void);
		///Send the information about self to all the other computers in the peer to peer network
		void send(fourints k);
};

#endif
