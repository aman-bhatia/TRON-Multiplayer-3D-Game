#include "Join.h"
#include "Network.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;

string ip_address, port_num;

int join::getindex(int *total){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ip_address , atoi(port_num.c_str()));
	if(status = sf::Socket::Done)
		cout << "Done!" << endl;
	/*char data[256];
	cout << "Enter message" << endl;
	scanf("%s" , data);
	if(socket.send(data , 256) == sf::Socket::Done)
		cout << "message sent" << endl;*/
	cout << "Waiting for more players to join" << endl;
	sf::Packet packet;
	if(!(socket.receive(packet) == sf::Socket::Done))
		cout << "1 : There is some problem with the connection, try again" << endl;
	double number;
	packet >> number;
	cout << (int(number)) << endl;
	sf::IpAddress address[int(number)];
	if(!(socket.receive(packet) == sf::Socket::Done))
		cout << "2 : There is some problem with the connection, try again" << endl;
	string s;
	cout << "The server is " << (address[0] = socket.getRemoteAddress()) << endl;
	ipads[0] = (address[0]).toString();
	for(int i = 1 ; i < number ; ++i)
	{
		packet >> s;
		address[i] = sf::IpAddress(s);
		ipads[i] = (sf::IpAddress(s)).toString();
		cout<<ipads[i]<<endl;
		cout << "the address is " << (address[i]) << endl;
	}
	if(!(socket.receive(packet) == sf::Socket::Done))
		cout << "3 : There is some problem with the connection, try again" << endl;
	double index;
	packet >> index;
	cout << (int(index)) << endl;
	*total = int(number);
	return int(index);
}


void cli()
{
	int aq;
	join C;
	cout<<"index="<<C.getindex(&aq)<<endl;
	cout<<"total="<<aq<<endl;
}
