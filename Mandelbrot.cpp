#include <iostream>
#include <SFML/Graphics.hpp>
#include "complex.h"
#include "Mandelbrot.h"

Mandelbrot::Mandelbrot(int width, int height, int max_iter, long double centerx, long double centery, 
			long double xwidth, long double ywidth, sf::Uint8* pixels, long double threshold) {			//Constructor
	
	this->width = width;
	this->height = height;
	this->max_iter = max_iter;
	
	this->centerx = centerx;
	this->centery = centery;
	
	this->xwidth = xwidth;
	this->ywidth = ywidth;
	
	this->leftx = centerx - xwidth/2;
	this->rightx = centerx + xwidth/2;
	this->topy = centery + ywidth/2;
	this->bottomy = centery - ywidth/2;
	
	this->zoom = 1;
	this->pixels = pixels;
	
	this->colorScheme = 0;
	this->threshold = threshold;
}

/*Calculates the number of iterations taken for a complex number c
to exceed the magnitude 2*/
int Mandelbrot::iter (complex c) {
	complex C(0, 0);
	int count = 0;
	
	while (count < max_iter) {
		C = C*C + c;
		if (C.mag() > 2) {
			break;
		}
		count++;
	}
	
	return count;
}

/*Update the pixel array*/
bool Mandelbrot::update (bool Stopped) {				
	
	if (!Stopped) {
		xwidth *= 0.975;				//Usual update
		ywidth *= 0.975;
	}
	else {
		xwidth = 4;					//Reset the widths
		ywidth = 4;
	}
	
	/*Updating the boundaries*/
	leftx = centerx - xwidth/2.0;
	rightx = centerx + xwidth/2.0;
	topy = centery + ywidth/2.0;
	bottomy = centery - ywidth/2.0;
	
	/*Proceed only for valid boundarie*/
	if (rightx > leftx && topy > bottomy && zoom > threshold) {			
		zoom *= 0.975;
		if (Stopped) {
			zoom = 1;
		}
		
		/*Iterating over all the pixels*/
		for (int i = 0; i < width * height ; i++) {
			double xstep = (rightx-leftx)/width;
			double ystep = (topy-bottomy)/height;
			
			double X = leftx + ((i - (i/width)*width)%height)*xstep;
			double Y = topy - (i/width)*ystep;
				
			int num = iter(complex(X, Y));
			colorPixels(i, num);
				
			pixels[4*i + 3] = 255;
		}	
	}
	else {								//The end. The boundaries have become too close
		std::cout << leftx << " " << rightx << std::endl;
		std::cout << bottomy << " " << topy << std::endl;
		std::cout << zoom << std::endl;
		return false;
	}
	return true;
}

/*Zooming in*/
void Mandelbrot::zoomIn (int x, int y) {
	long double xstep = (rightx-leftx)/width;
	long double ystep = (topy-bottomy)/height; 
	
	centerx = leftx + (x)*xstep;
	centery = topy - (y)*ystep;
	
	xwidth *= 0.5;
	ywidth *= 0.5;
	zoom *= 0.5;
	return;
}

/*Zooming out*/
void Mandelbrot::zoomOut (int x, int y) {
	long double xstep = (rightx-leftx)/width;
	long double ystep = (topy-bottomy)/height; 
	
	centerx = leftx + (x)*xstep;
	centery = topy - (y)*ystep;
	
	xwidth *= 2;
	ywidth *= 2;
	zoom *= 2;
	return;
}

/*Has the color scheme been set?*/
bool Mandelbrot::isColorSet () {
	if (this->colorScheme == 0) {
		return false;
	}
	return true;
}

/*Three color schemes are available.
Set a particular color scheme*/
void Mandelbrot::setColorScheme (int colorScheme) {
	this->colorScheme = colorScheme;
	return;
}

/*Function to color pixels based on number of
iterations and the position*/
void Mandelbrot::colorPixels(int index, int iterations) {
	for (int j = 0; j < 3; j++) {
		if (iterations == 0) {
			pixels[4*index + j] = 0;
		}
		else {
			/*The mixed or the "colorful" color scheme :)*/
			if (colorScheme == 3) {						
				pixels[4*index + j] = (iterations%(4*(j+1)))*(256/(4*(j+1)));
			}
			else if (colorScheme == 2) {							//Blue
				if (j == 2) {
					pixels[4*index + j] = (double(iterations)/max_iter)*255;
				}
				else {
					pixels[4*index + j] = 0;
				}
			}
			else if (colorScheme == 1) {
				if (j == 1) {								//Green
					pixels[4*index + j] = (double(iterations)/max_iter)*255;
				}
				else {
					pixels[4*index + j] = 0;
				}
			}
			if (iterations == max_iter) {
				pixels[4*index+j] = 0;
			}
		}
	}	
	pixels[4*index + 3] = 255;
}
