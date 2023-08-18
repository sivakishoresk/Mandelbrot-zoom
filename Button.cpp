#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Button.h"
using namespace std;

/*Constructor*/
Button::Button (float x, float y, float width, float height, string text, sf::Font* font, sf::Color idleColor, sf::Color hoverColor) {

	this->rectangle.setPosition(sf::Vector2f(x, y));
	this->rectangle.setSize(sf::Vector2f(width, height));
	this->rectangle.setFillColor(idleColor);				//Constructing the bounding box
	this->rectangle.setOutlineThickness(5);
	this->rectangle.setOutlineColor(sf::Color::Black);
	
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Blue);					//Initialising the text
	this->text.setCharacterSize(20);
	this->text.setStyle(sf::Text::Bold);
	
	/*Setting the position of the text within the rectangle*/
	sf::Vector2f textpos;
	textpos.x = this->rectangle.getPosition().x + this->rectangle.getSize().x/2.f - this->text.getGlobalBounds().width/2.f;
	textpos.y = this->rectangle.getPosition().y + this->rectangle.getSize().y/2.f - this->text.getGlobalBounds().height/2.f;
	
	this->text.setPosition(textpos);
	
	/*Initialising the colors*/
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	
}

/*Draw the button to the screen*/
void Button::render (sf::RenderWindow* target) {
	target->draw(this->rectangle);
	target->draw(this->text);
}

/*Check whether a given point is contained within the button*/
bool Button::contains (sf::Vector2f clickpos) {
	if (this->rectangle.getGlobalBounds().contains(clickpos)) {
		return true;
	}
	return false;
}

/*Set the text within the button*/
void Button::setText (string s) {
	this->text.setString(s);
	return;
}
