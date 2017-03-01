#include "Network.h"
#define loop(a , b) for(int i = a ; i < b ; ++i)
using namespace std;

string ipads[6] = {"","","","","",""};

network::network(int i , int j , int startport) : myid(i) , total(j) // Use this function to add a computer to the peer network (i is the personal id and j is the total number of computers in the network , startport is the portnumber around which communication takes place)
{
	clienttome = new sf::TcpSocket[myid];
	clientiam = new sf::TcpSocket[total - myid];
	#ifdef DEBUG
		cout<<"myid ="<<myid<<endl;
	#endif
	if(listener.listen(startport + myid) == sf::Socket::Done){
		#ifdef DEBUG
			cout << "waiting for clients" << endl;
		#endif
	}
	loop(1 , myid){
		if(listener.accept(clienttome[i - 1]) == sf::Socket::Done){
		#ifdef DEBUG
				cout << "client connected" << endl;
		#endif
		}
	}
	loop(1 , total - myid + 1)
	{
	#ifdef DEBUG
		cout<<" i'mm here yo "<<myid<<endl;
		cout<<ipads[myid]<<"\n";
	#endif
		sf::Socket::Status status = clientiam[i - 1].connect(ipads[(myid+i)%total] , startport + myid + i);
		if(status == sf::Socket::Done){
			#ifdef DEBUG
				cout << "Done! - Connected to a server" << endl;
			#endif
		}
		else
			--i;
	}	
	loop(0 , myid - 1)
		(clienttome[i]).setBlocking(false);
	loop(0 , total - myid)
		(clientiam[i]).setBlocking(false);
}

stack<fourints> network::receive(void)
{
	/*char data[256];
	std::size_t received;
	stack<int> messages;
	loop(0 , myid - 1)
		if((clienttome[i]).receive(data , 256 , received) == sf::Socket::Done)
			messages.push(atoi(data));
	loop(0 , total - myid)
		if((clientiam[i]).receive(data , 256 , received) == sf::Socket::Done)
			messages.push(atoi(data));
	return messages;*/
	sf::Packet packet;
	double x , y , z , w;
	stack<fourints> messages;
	#ifdef DEBUG
		cout<<"receiving messages"<<endl;
	#endif
	loop(0 , myid - 1)
		if((clienttome[i]).receive(packet) == sf::Socket::Done)
		{
			packet >> x >> y >> z >> w;
			messages.push(fourints(float(x) , float(y) , int(z) , int(w)));
			#ifdef DEBUG
					cout<<"client to me"<<endl;
			#endif
		}
	loop(0 , total - myid)
		if((clientiam[i]).receive(packet) == sf::Socket::Done)
		{
			packet >> x >> y >> z >> w;
			messages.push(fourints(float(x) , float(y) , int(z) , int(w)));
			#ifdef DEBUG
					cout<<"client i am"<<endl;
			#endif
		}
	return messages;
}

void network::send(fourints k)
{
	/*char data[256];
	loop(0 , myid - 1) // This loop sends messages sequentially to each of the other computers. If the message sending fails for some computer, it will try sending the message continuously until it is successful.
		if (!((clienttome[i]).send(data , 256) == sf::Socket::Done))
		{
			char *messag = const_char<char*>(string(messages.top()).c_str());
			for(int k = 0 ; k < string(messages.top()).length() ; ++k)
				data[k] = messag[k];
			--i;
		}
		else
	loop(0 , total - myid)
		if (!((clientiam[i]).send(data , 256) == sf::Socket::Done))
		{
			--i;
		}*/
	sf::Packet packet;
	double x = k.a;
	double y = k.b;
	double z = k.c;
	double w = k.d;
	packet << x << y << z << w;
	loop(0 , myid - 1)
		if(!((clienttome[i]).send(packet) == sf::Socket::Done))
			--i;
	loop(0 , total - myid)
		if(!((clientiam[i]).send(packet) == sf::Socket::Done))
			--i;
			
}
