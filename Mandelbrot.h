#include <SFML/Graphics.hpp>
#include "complex.h"

#ifndef MANDELBROT_H
#define MANDELBROT_H

/*The main class. It contains member functions to update the image*/

class Mandelbrot {
	private :
		int width;				//Width of the image in pixels
		int height;				//Height of the image in pixels
		int max_iter;				//Maximum number of iterayions per complex number
		
		/*Coordinates of the center of the image*/
		long double centerx;	
		long double centery;
		
		/*Actual width and height or the spread along the X-axis and Y-axis*/
		long double xwidth;
		long double ywidth;
		
		/*Coordinates of the extreme left and extreme right*/
		long double leftx;
		long double rightx;
		
		/*Coordinates of the extreme top and extreme bottom*/
		long double topy;
		long double bottomy;
		
		/*Zoom factor*/
		long double zoom;
		/*Array containing the pixel information*/				
		sf::Uint8* pixels;
		
		int colorScheme;
		long double threshold;			
		
	public :
		Mandelbrot (int width, int height, int max_iter, long double centerx, long double centery, 
				long double xwidth, long double ywidth, sf::Uint8* pixels, long double threshold);
		
		int iter (complex c);
		
		bool update (bool Stopped);
		
		void zoomIn (int x, int y);
		
		void zoomOut (int x, int y);
		
		bool isColorSet();
		
		void setColorScheme(int colorScheme);
		
		void colorPixels(int index, int iterations);
};

#endif
