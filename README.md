|=============================================================================================================|
|------------------------------------------------| TRON GAME |------------------------------------------------|
|=============================================================================================================|


Introduction :
------------
	This application "TRON" is a bike trapping game which supports both single and multi player. For single player, AI is there to drive the remaining players, and in multi player, p2p networking is used to exchange all data among users. This project is the replica of the game played in the TRON LEGACY movie.

|=============================================================================================================|	
	
Software Requirements :
---------------------

- Operating System : Linux
- Compiler : g++
- Libraries : 
	SFML
	OpenGl


|==============================================================================================================|

Usage :

- Execute :	make (produces an executable binary file of the TRON game)

			make doc (produces documentation pdf of the TRON game)

			make clean (cleans all object and documentation files)

			make doc_clean (cleans all document files)

			make execute (executes binary and game starts)

			make debug (produces a debug version of the game)


|==============================================================================================================|

Configuration :

- The user interface of the game is very simple and user friendly.

- The Single Player Option just needs number of players that will play the game

- The Multi Player Option requires whether a player wants to become a hoster or joiner for starting the game. Ip address of host and port number are required to start the game.

|==============================================================================================================|

Files used in Application :
Client : 
    Headers :
		- Tron.h
		- Bike.h
		- Host.h
		- Join.h
		- Network.h
		- Graphics.h
    C++ source files :
		- main.cpp
		- Tron.cpp
		- Bike.cpp
		- Host.cpp
		- Join.cpp
		- Network.cpp
		- Graphics.cpp

|===============================================================================================================|

Other Source Files and documents :

- Make files
- README.txt
- Design Document


|===============================================================================================================|

Frequently asked Questions (FAQ) :


- How to install the application?
	The user or client can install the downloaded Game sources by just running make in his terminal or command prompt. This compiles the source files downloaded and then runs the executable to generate the Game's start screen where everything can be selected appropriately.

- How to use the features?
	All the features are available as options on start screens. GUI is user friendly and is very simple. In Join game, the user needs to know the ip address and port number which are to be entered like <ip address>:<port number>. For hosting only port number is required.

- Can you please tell all the features available in this application?
	Single Player
		* Number of Players
		* Artificial Intelligence
	Multi Player
		* Number of Players
		* Hosting and Joining
		* Feasibility of changing port numbers
		* Network Connection breakage is handled. So don't worry if connection breaks, the user can join again and continue his game.

- Where can I find sources for this software?
	This software has been uploaded and shared in github community using doxygen. The users can download these source files from the github and follow appropriate instructions for the usage.
	
	
|================================================================================================================|

Maintainers :

- Ch Y N S Avinash Karthik		:	avinash.karthik2@gmail.com
- Aman Bhatia				:	amanbhatia2510@gmail.com
- N N Chaitanya				:	nnnchaitanya@gmail.com


|================================================================================================================|

Professors and Phds involved :

- Professor Huzur Saran (IIT Delhi)
- Professor Kolin Paul (IIT Delhi)
- Mr. Prathmesh Kallurkar (Phd IIT Delhi)


|================================================================================================================|

Complaints/Suggestions or Bug reporting :

	User can complaint/report any bug, issues, improvement suggestions to us by mailing on any of the mails given above.
	
	
|================================================================================================================|

Link to github(other material) : http://www.bitbucket.org/aman-bhatia {It is a private repository, so only we can share it with you when needed}