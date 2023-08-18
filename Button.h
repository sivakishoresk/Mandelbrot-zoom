#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

#ifndef BUTTON_H
#define BUTTON_H

/*Button class to model a button in SFML*/
class Button {
	private :
		sf::RectangleShape rectangle;			//The bounding box
		sf::Text text;					//The text within the button
		
		sf::Color idleColor;				//Color of the button when idle
		sf::Color hoverColor;				//Color of the button when you hover upon it
		
	public :
		Button (float x, float y, float witdh, float height, string text, sf::Font* font, sf::Color hoverColor, sf::Color activeColor);
		
		void render(sf::RenderWindow* target);
		
		bool contains(sf::Vector2f clickpos);	
		
		void setText(string s);
};

#endif
