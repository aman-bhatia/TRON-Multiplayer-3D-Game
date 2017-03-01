#include "Network.h"
#include "NetFun.h"
using namespace std;

int f1()
{
	network a(1 , 3 , 2000);
	a.send(fourints(2345 , 63 , 73 , 345));
	sleep(1);
	return 0;
}

int f2()
{
	network a(2 , 3 , 2000);
	sleep(2);
	std::stack<fourints> st = a.receive();
	#ifdef DEBUG
		cout << ((st.top()).a) << " " << ((st.top()).b) << " " << ((st.top()).c) << endl;
	#endif
	st.pop();
	#ifdef DEBUG
		cout << ((st.top()).a) << " " << ((st.top()).b) << " " << ((st.top()).c) << endl;
	#endif
	return 0;
}

int f3()
{
	network a(3 , 3 , 2000);
	sleep(1);
	a.send(fourints(9870 , 62 , 5462 , 345));
	std::stack<fourints> st = a.receive();
	#ifdef DEBUG
		cout << ((st.top()).a) << " " << ((st.top()).b) << " " << ((st.top()).c) << endl;
	#endif
	return 0;
}
