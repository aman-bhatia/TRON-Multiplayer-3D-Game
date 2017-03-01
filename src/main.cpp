#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Graphics.h"
#include "Tron.h"
#include "Host.h"
#include "Join.h"
using namespace std;

bool sin_pl = false;

enum screen {SPLASH_SCREEN, CONTROL, SP_NOP, HJ, GC, AB, HOST, JOIN, HOST_NOP, IP, GO};
screen scr;

string ip_add = "";
string port_no = "";

int main(int argc , char **argv){
	/*
	int nop;
	cout<<"Number of players : ";
	cin>>nop;
	sin_pl = true;
	start_game(argc,argv,1,nop,sin_pl);

	*/
	sf::RenderWindow window;

	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("sound/got_new.ogg")) return EXIT_FAILURE;
	
	// Play the music
	music.play();
	music.setLoop(true);

	sf::Music go_music;
	if (!go_music.openFromFile("sound/go.ogg")) return EXIT_FAILURE;
	

	sf::SoundBuffer hover_buffer;
	if (!hover_buffer.loadFromFile("sound/hover.ogg")) return -1;
	
	sf::Sound hover_sound;
	hover_sound.setBuffer(hover_buffer);
	
	sf::SoundBuffer click_buffer;
	if (!click_buffer.loadFromFile("sound/click.ogg")) return -1;
	
	sf::Sound click_sound;
	click_sound.setBuffer(click_buffer);

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("fonts/ip-font.ttf")) return EXIT_FAILURE;
	sf::Text text_ip_add(ip_add, font, 30);
	sf::Text text_port_no(port_no, font, 30);
	text_ip_add.setPosition(820,380);
	text_port_no.setPosition(930,600);
	text_ip_add.setStyle(sf::Text::Italic);
	text_port_no.setStyle(sf::Text::Italic);

	// get the video mode (which tells you the size and BPP information of the current display
	std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();

	// then create (or automatically recreate) the RenderWindow
	window.create(VModes.at(0), "TRON - The Legacy", sf::Style::Default || sf::Style::Fullscreen);
	
	//Load Images
	sf::Image splash;
	if (!splash.loadFromFile("images/splash.png")) return EXIT_FAILURE;
	sf::Image controls;
	if (!controls.loadFromFile("images/controls.png")) return EXIT_FAILURE;
	sf::Image controls_sp;
	if (!controls_sp.loadFromFile("images/controls_sp.png")) return EXIT_FAILURE;
	sf::Image controls_mp;
	if (!controls_mp.loadFromFile("images/controls_mp.png")) return EXIT_FAILURE;
	sf::Image controls_gc;
	if (!controls_gc.loadFromFile("images/controls_gc.png")) return EXIT_FAILURE;
	sf::Image controls_ab;
	if (!controls_ab.loadFromFile("images/controls_ab.png")) return EXIT_FAILURE;
	sf::Image controls_exit;
	if (!controls_exit.loadFromFile("images/controls_exit.png")) return EXIT_FAILURE;
	sf::Image nop;
	if (!nop.loadFromFile("images/nop.png")) return EXIT_FAILURE;
	sf::Image nop2;
	if (!nop2.loadFromFile("images/nop2.png")) return EXIT_FAILURE;
	sf::Image nop3;
	if (!nop3.loadFromFile("images/nop3.png")) return EXIT_FAILURE;
	sf::Image nop4;
	if (!nop4.loadFromFile("images/nop4.png")) return EXIT_FAILURE;
	sf::Image nop5;
	if (!nop5.loadFromFile("images/nop5.png")) return EXIT_FAILURE;
	sf::Image nop6;
	if (!nop6.loadFromFile("images/nop6.png")) return EXIT_FAILURE;
	sf::Image hj;
	if (!hj.loadFromFile("images/hj.png")) return EXIT_FAILURE;
	sf::Image hst;
	if (!hst.loadFromFile("images/host.png")) return EXIT_FAILURE;
	sf::Image jon;
	if (!jon.loadFromFile("images/join.png")) return EXIT_FAILURE;
	sf::Image ip;
	if (!ip.loadFromFile("images/ip.png")) return EXIT_FAILURE;
	sf::Image verify_ip;
	if (!verify_ip.loadFromFile("images/verify_ip.png")) return EXIT_FAILURE;
	sf::Image gc;
	if (!gc.loadFromFile("images/gc.png")) return EXIT_FAILURE;
	sf::Image ab;
	if (!ab.loadFromFile("images/ab.png")) return EXIT_FAILURE;
	sf::Image go;
	if (!go.loadFromFile("images/go.png")) return EXIT_FAILURE;

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromImage(splash)) return EXIT_FAILURE;
	texture.setSmooth(true);
	sf::Sprite sprite(texture);
	sprite.setScale(1400 / sprite.getLocalBounds().width, 800 / sprite.getLocalBounds().height);
	scr = SPLASH_SCREEN;

	while (window.isOpen()){
		sf::Event Event;
		while (window.pollEvent(Event)){
			switch (Event.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (scr == IP && Event.text.unicode>=46 && Event.text.unicode<=57 && Event.text.unicode!=47 && ip_add.length()<15){
					ip_add += Event.text.unicode;
					text_ip_add.setString(ip_add);
				} else if (scr == IP && Event.text.unicode == 8){
					ip_add = ip_add.substr(0,ip_add.length()-1);
					text_ip_add.setString(ip_add);
				}

				if (scr == HJ && Event.text.unicode>=48 && Event.text.unicode<=57 && port_no.length()<=4){
					port_no += Event.text.unicode;
					text_port_no.setString(port_no);
				} else if (scr == HJ && Event.text.unicode == 8){
					port_no = port_no.substr(0,port_no.length()-1);
					text_port_no.setString(port_no);
				}
				break;
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (scr == SPLASH_SCREEN && Event.key.code == sf::Keyboard::Space){
					if (!texture.loadFromImage(controls)) return EXIT_FAILURE;
					texture.setSmooth(true);
					sprite.setTexture(texture);
					sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					scr = CONTROL;
				}
				break;
			case sf::Event::MouseMoved:
				if (scr == CONTROL){
					if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 450) && (Event.mouseMove.y < 295) && (Event.mouseMove.y > 240)){
						hover_sound.play();
						if (!texture.loadFromImage(controls_sp)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 450) && (Event.mouseMove.y < 390) && (Event.mouseMove.y > 335)) {
						hover_sound.play();
						if (!texture.loadFromImage(controls_mp)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 450) && (Event.mouseMove.y < 480) && (Event.mouseMove.y > 430)){
						hover_sound.play();
						if (!texture.loadFromImage(controls_gc)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 450) && (Event.mouseMove.y < 580) && (Event.mouseMove.y > 520)){
						hover_sound.play();
						if (!texture.loadFromImage(controls_ab)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					}else if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 450) && (Event.mouseMove.y < 680) && (Event.mouseMove.y > 625)) {
						hover_sound.play();
						if (!texture.loadFromImage(controls_exit)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					}
				} else if (scr == SP_NOP | scr ==  HOST_NOP){
					if ((Event.mouseMove.x < 730) && (Event.mouseMove.x > 605) && (Event.mouseMove.y < 355) && (Event.mouseMove.y > 310)) {
						hover_sound.play();
						if (!texture.loadFromImage(nop2)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 730) && (Event.mouseMove.x > 605) && (Event.mouseMove.y < 435) && (Event.mouseMove.y > 390)) {
						hover_sound.play();
						if (!texture.loadFromImage(nop3)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 730) && (Event.mouseMove.x > 605) && (Event.mouseMove.y < 515) && (Event.mouseMove.y > 465)) {
						hover_sound.play();
						if (!texture.loadFromImage(nop4)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 730) && (Event.mouseMove.x > 605) && (Event.mouseMove.y < 590) && (Event.mouseMove.y > 545)) {
						hover_sound.play();
						if (!texture.loadFromImage(nop5)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 730) && (Event.mouseMove.x > 605) && (Event.mouseMove.y < 670) && (Event.mouseMove.y > 620)) {
						hover_sound.play();
						if (!texture.loadFromImage(nop6)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
					}
				} else if (scr == HJ){
					if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 455) && (Event.mouseMove.y < 390) && (Event.mouseMove.y > 330)) {
						hover_sound.play();
						if (!texture.loadFromImage(hst)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					} else if ((Event.mouseMove.x < 965) && (Event.mouseMove.x > 455) && (Event.mouseMove.y < 485) && (Event.mouseMove.y > 430)) {
						hover_sound.play();
						if (!texture.loadFromImage(jon)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					}
				} else if (scr == IP){
					if ((Event.mouseMove.x < 980) && (Event.mouseMove.x > 467) && (Event.mouseMove.y < 605) && (Event.mouseMove.y > 555)) {
						hover_sound.play();
						if (!texture.loadFromImage(verify_ip)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (scr == CONTROL){
					if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 450) && (Event.mouseButton.y < 295) && (Event.mouseButton.y > 240)){
						cout << "Single player pressed\n";
						sin_pl = true;
						click_sound.play();
						if (!texture.loadFromImage(nop)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
						scr = SP_NOP;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 450) && (Event.mouseButton.y < 390) && (Event.mouseButton.y > 335)) {
						cout << "Multi player pressed\n";
						click_sound.play();
						if (!texture.loadFromImage(hj)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
						scr = HJ;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 450) && (Event.mouseButton.y < 480) && (Event.mouseButton.y > 430)) {
						cout << "Game Credits Pressed\n";
						click_sound.play();
						if (!texture.loadFromImage(gc)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
						scr = GC;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 450) && (Event.mouseButton.y < 580) && (Event.mouseButton.y > 520)) {
						cout << "About Pressed\n";
						click_sound.play();
						if (!texture.loadFromImage(ab)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
						scr = AB;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 450) && (Event.mouseButton.y < 680) && (Event.mouseButton.y > 625)) {
						click_sound.play();
						cout << "Exit pressed\n";
						window.close();
					}
				} else if (scr == GC | scr == AB){
					if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 1220) && (Event.mouseButton.x > 940) && (Event.mouseButton.y < 125) && (Event.mouseButton.y > 80)) {
						cout << "Back Pressed\n";
						click_sound.play();
						if (!texture.loadFromImage(controls)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
						scr = CONTROL;
					}
				}else if (scr == SP_NOP | scr == HOST_NOP){
					int num_pl = 0;
					if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 730) && (Event.mouseButton.x > 605) && (Event.mouseButton.y < 355) && (Event.mouseButton.y > 310)) {
						click_sound.play();
						cout<< "Number of players selected : 2 \n";
						num_pl = 2;
						window.setVisible(false);
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 730) && (Event.mouseButton.x > 605) && (Event.mouseButton.y < 435) && (Event.mouseButton.y > 390)) {
						click_sound.play();
						cout<< "Number of players selected : 3 \n";
						window.setVisible(false);
						num_pl = 3;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 730) && (Event.mouseButton.x > 605) && (Event.mouseButton.y < 515) && (Event.mouseButton.y > 465)) {
						click_sound.play();
						cout<< "Number of players selected : 4 \n";
						window.setVisible(false);
						num_pl = 4;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 730) && (Event.mouseButton.x > 605) && (Event.mouseButton.y < 590) && (Event.mouseButton.y > 545)) {
						click_sound.play();
						cout<< "Number of players selected : 5 \n";
						window.setVisible(false);
						num_pl = 5;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 730) && (Event.mouseButton.x > 605) && (Event.mouseButton.y < 670) && (Event.mouseButton.y > 620)) {
						click_sound.play();
						cout<< "Number of players selected : 6 \n";
						window.setVisible(false);
						num_pl = 6;
					}
					if (!sin_pl && num_pl){
						host H;
						bid = num_pl;
						H.gettotal(num_pl);
					}
					if(num_pl != 0)	start_game(argc,argv,num_pl,sin_pl);
					screenend(argc,argv);
				} else if (scr == HJ){
					if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 455) && (Event.mouseButton.y < 390) && (Event.mouseButton.y > 330)) {
						click_sound.play();
						port_num = port_no;
						cout<< "User pressed Host with port number : "<<port_num<<"\n";
						if (!texture.loadFromImage(nop)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2500 / sprite.getLocalBounds().width, 1000 / sprite.getLocalBounds().height);
						scr = HOST_NOP;
					} else if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 965) && (Event.mouseButton.x > 455) && (Event.mouseButton.y < 485) && (Event.mouseButton.y > 430)) {
						click_sound.play();
						port_num = port_no;
						cout<< "User pressed Join with port num : "<<port_num<<"\n";
						if (!texture.loadFromImage(ip)) return EXIT_FAILURE;
						texture.setSmooth(true);
						sprite.setTexture(texture);
						sprite.setScale(2700 / sprite.getLocalBounds().width, 1100 / sprite.getLocalBounds().height);
						scr = IP;
					}
				} else if (scr == IP){
					if (Event.mouseButton.button == sf::Mouse::Left && (Event.mouseButton.x < 980) && (Event.mouseButton.x > 467) && (Event.mouseButton.y < 605) && (Event.mouseButton.y > 555)) {
						click_sound.play();
						ip_address = ip_add;
						cout<< "User pressed Join Game with IP Address : "<< ip_address << endl;
						int total;
						join J;
						bid = J.getindex(&total);  //change this with the message given from the player starting the service
					 	start_game(argc,argv,total,sin_pl);
					 	screenend(argc,argv);
					} else cout<< "X : "<<Event.mouseButton.x<<" Y : "<<Event.mouseButton.y<<endl;
				}
				break;
			}
		}

		// Clear screen
		window.clear();
		
		// Draw the sprite
		window.draw(sprite);
		
		// Draw the string
		if (scr == IP) window.draw(text_ip_add);
		if (scr == HJ) window.draw(text_port_no);
		
		// Update the window
		window.display();
	}
}
