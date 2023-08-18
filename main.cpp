#include <SFML/Graphics.hpp>
#include "complex.h"
#include "Button.h"
#include "Mandelbrot.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <thread>

#define MAX_ITER 100				//The maximum of iterations

int main()
{
	std::cout << "Would you like to store the images generated during the process?" << std::endl;
	string reply;
	cin >> reply;
	
	bool store = false;
	
	if (reply == "Yes") {
		store = true;
	}
	/*Dimensions of the image*/
	int width = 1024;
	int height = 1024;
	
	/*Choices for the coordinates of the center of the image*/
	
	/*Some special centers*/
	//double centerx = -0.16;
	//double centery = 1.04;
	//double centerx = 0.42875;
	//double centery = -0.231345;
	double centerx = -1.62917;
	double centery = -0.0203968;
	
	/*Extent in each direction*/
	double xwidth = 4;
	double ywidth = 4;
	
	/*The main window*/
	sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Zoom");
	sf::Texture texture;
	
	int numButtons = 4;
	int buttonHeight = 40;
	
	/*Loading the font to display text*/
	sf::Font font;
	if (!font.loadFromFile("roboto.thin.ttf")) {
    		std::cout << "Error loading font" << std::endl;
	}
	
	Button instr(width/4, height/2, width/2, buttonHeight, "Choose the type of coloring scheme", &font, sf::Color::Green, sf::Color::Blue);
	Button green(width/8, height/2 + 100, width/4, buttonHeight, "Green", &font, sf::Color::Green, sf::Color::Blue);
	Button red(3*width/8, height/2 + 100, width/4, buttonHeight, "Blue", &font, sf::Color::Green, sf::Color::Blue);
	Button mixed(5*width/8, height/2 + 100, width/4, buttonHeight, "Mixed", &font, sf::Color::Green, sf::Color::Blue);
	
	/*Buttons to implement additional features*/
	Button stop(0, height - buttonHeight, width/4, buttonHeight, "Stop and reset", &font, sf::Color::Green, sf::Color::Blue);
	Button pause(width/4, height - buttonHeight, width/4, buttonHeight, "Pause", &font, sf::Color::Green, sf::Color::Blue);
	Button save(2*width/4, height - buttonHeight, width/4, buttonHeight, "Save Image", &font, sf::Color::Green, sf::Color::Blue);
	Button exit(3*width/4, height - buttonHeight, width/4, buttonHeight, "Exit", &font, sf::Color::Green, sf::Color::Blue);
	
	if (!texture.create(width, height)) {
		std::cout<<"Error"<<std::endl;
	}
	
	/*Pixels array. The most important
	Stores the data related to every pixel such 
	as the three rgb components and saturation value*/
	sf::Uint8* pixels = new sf::Uint8[width * height * 4];
	
	int count = 0;
	
	/*These variables represent the state of the executable*/
	bool Paused = false;				//True when you have paused the zoom
	bool Stopped = false;				//True when you stopped and reset the entire zoom and about to begin again
	bool Started = false;
	
	int colorScheme = 0;				//Color scheme for pixels
	long double threshold = 0.001;		//If you cross a certain threshold, stop zooming and quit
	
	/*The Mandelbrot object, initialised.
	Very important as it contains methods to manipulate,
	update and process the pixels array*/
	Mandelbrot image(width, height, MAX_ITER, centerx, centery, xwidth, ywidth, pixels, threshold);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed && !Started) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i position = sf::Mouse::getPosition(window);
					sf::Vector2f clickpos;
					
					clickpos.x = position.x;
					clickpos.y = position.y;
					
					if (green.contains(clickpos)) {		
						colorScheme = 1;
						Started = true;
						image.setColorScheme(colorScheme);
					}
					else if (red.contains(clickpos)) {
						colorScheme = 2;
						Started = true;
						image.setColorScheme(colorScheme);
					}
					else if (mixed.contains(clickpos)) {
						colorScheme = 3;
						Started = true;
						image.setColorScheme(colorScheme);
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed && Started) {
				
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i position = sf::Mouse::getPosition(window);
					sf::Vector2f clickpos;
					
					clickpos.x = position.x;
					clickpos.y = position.y;
					
					if (pause.contains(clickpos)) {		//Clicked the pause button
						/*Relevant only when the zoom is going on*/
						if (!Stopped) {			
							Paused = !Paused;
							if (Paused == false) {
								pause.setText("Pause");
							}
							else {
								pause.setText("Resume");
							}
						}
					}
					else if (stop.contains(clickpos)) {		//Clicked the stop button
						Stopped = !Stopped;
						if (Stopped == true) {
							stop.setText("Start again");
						}
						else {
							stop.setText("Stop and reset");
							Paused = false;
						}
					}
					else if (save.contains(clickpos)) {		//Saving an image. The process is paused while you do it
						Paused = true;
						pause.setText("Resume");
						/*Get the image name from the user. To be done 
						in the terminal*/
						std::cout << "Please enter the name of the image : " ;
						string name;
						std::cin >> name;
						
						/*Saving*/
						sf::Image img;
						img.create(width, height, pixels);
						img = texture.copyToImage();
						
						string str;
						str = "SavedImages/" + name + ".png";
						
						img.saveToFile(str);
					}
					else if (exit.contains(clickpos)) {
						Started = false;
						Stopped = false;
						Paused = false;
						pause.setText("Pause");
						stop.setText("Stop and reset");
						image.update(true);
					}
					else if (0<=position.x && position.x <= width && 0 <= position.y && position.y <= height) {
						/*Left click allows the user to zoom in and make 
						the point clicked the new center*/
						image.zoomIn(position.x, position.y);
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					sf::Vector2i position = sf::Mouse::getPosition(window);
					/*Right click allows you to zoom out*/
					if (0<=position.x && position.x <= width && 0 <= position.y && position.y <= height) {
						image.zoomOut(position.x, position.y);
					}
				}
			}
		}
		
		/*If the zoom isn't paused, update the image*/
		if (Started) {
			if (!Paused) {
				if (!image.update(Stopped)) {
					break;
				}
				if (Stopped) {
					Paused = true;
				}
				if (store) {
					count++;
					sf::Image img;
					img.create(width, height, pixels);
					std::string str;
					str = "Images/"+std::to_string(count)+".png";
					img = texture.copyToImage();
					img.saveToFile(str);
				}
			}
			window.clear();
			
			/*Renderinging the image using the pixels*/
			texture.update(pixels);
			sf::Sprite sprite(texture);
			window.draw(sprite);
		
			/*Drawing the buttons*/
			stop.render(&window);
			pause.render(&window);
			save.render(&window);
			exit.render(&window);
		}
		else {
			window.clear(sf::Color::Green);
			
			/*Loading sample images*/
			instr.render(&window);
			green.render(&window);
			red.render(&window);
			mixed.render(&window);
			
			std::string str_g, str_b, str_m;
			str_g = "SampleImages/green.png";
			str_b = "SampleImages/blue.png";
			str_m = "SampleImages/mixed.png";
			
			sf::Texture texture_g, texture_b, texture_m;
			texture_g.loadFromFile(str_g);
			texture_b.loadFromFile(str_b);
			texture_m.loadFromFile(str_m);
			
			sf::Sprite sprite_g(texture_g);
			sf::Sprite sprite_b(texture_b);
			sf::Sprite sprite_m(texture_m);
			
			float scale = 0.25;
			
			sprite_g.setScale(0.9*scale, scale);
			sprite_b.setScale(0.9*scale, scale);
			sprite_m.setScale(0.9*scale, scale);
			
			sprite_g.setPosition(width/8, height/2+200);
			sprite_b.setPosition(3*width/8, height/2+200);
			sprite_m.setPosition(5*width/8, height/2+200);
			
			window.draw(sprite_g);
			window.draw(sprite_b);
			window.draw(sprite_m);
		}
		window.display();
	}
	
	/*If you have stored images, then
	display them as an animation*/
	if (store) {
		sf::RenderWindow window2(sf::VideoMode(width, height), "Mandelbrot Zoom");
		sf::Texture texture2;
		int i = 0;
		while (window2.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			i++;
			if (i == count)
				break;
			std::string str;
			str = "Images/"+std::to_string(i)+".png";
			texture2.loadFromFile(str);
			sf::Sprite sprite(texture2);
			window2.clear();
			window2.draw(sprite);
			window2.display();
			std::this_thread::sleep_for(0.05s);
		}
	}
    return 0;
}
