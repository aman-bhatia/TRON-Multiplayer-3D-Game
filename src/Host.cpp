#include "Host.h"
#include "Join.h"
#include "Network.h"
#include "Graphics.h"
#include <SFML/Network.hpp>
#include <iostream>
using namespace std;


void host::gettotal(int numberallowed)
{

	sf::TcpListener listener;
	listener.listen(atoi(port_num.c_str()));
	bool running = true;
	int numberconnected = 0;
	sf::SocketSelector selector;
	selector.add(listener);
	sf::TcpSocket client[numberallowed - 1];
	sf::IpAddress clientaddress[numberallowed - 1];
//ifdef DEBUG
		cout << "Init " << (sf::IpAddress::getLocalAddress()) << endl;
//	#endif
	while(numberconnected < numberallowed - 1)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				if(listener.accept(client[numberconnected++]) == sf::Socket::Done)
//					#ifdef DEBUG
						cout << "Client connected : " << (clientaddress[numberconnected - 1] = (client[numberconnected - 1]).getRemoteAddress()) << endl;
//					#endif
					ipads[numberconnected] = (clientaddress[numberconnected - 1]).toString();
//					#ifdef DEBUG
						cout<<numberconnected<<" "<<ipads[numberconnected]<<endl;
//					#endif
			}
		}
	}
	sf::Packet packet;
	packet << double(numberallowed);
	for(int i = 0 ; i < numberallowed - 1 ; ++i)
		if(!((client[i].send(packet)) == sf::Socket::Done))
			--i;
	packet.clear();
	for(int i = 0 ; i < numberallowed - 1 ; ++i)
		packet << ((clientaddress[i]).toString());
	for(int i = 0 ; i < numberallowed - 1 ; ++i)
		(client[i]).send(packet);
	for(int i = 0 ; i < numberallowed - 1 ; ++i)
	{
		packet.clear();
		packet << double(i + 1);
		client[i].send(packet);
	}
}