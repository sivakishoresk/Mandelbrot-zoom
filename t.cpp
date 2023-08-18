#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

#define MAX_ITER 100

class complex {
	private:
		double x;
		double y;
	public:
		complex() {
			x = 0;
			y = 0;
		}
		complex(double a, double b) {
			x = a;
			y = b;
		}
		double mag() {
			return sqrt(x*x + y*y);
		}
		complex operator+ (const complex &b) const {
			double X = (this->x + b.x);
			double Y = (this->y + b.y);
			return complex(X, Y);
		}
		complex operator* (const complex &b) const {
			double X = (this->x * b.x) - (this->y * b.y);
			double Y = (this->x * b.y) + (this->y * b.x);
			return complex(X, Y);
		}
};

class stack {
	private :
		std::vector<int> val[5];
		int size;
	public :
		stack () {
			size = 0;
		}
		
		void push (std::vector<int> elem) {
			val[size] = elem;
			size++;
		}
		
		void pop () {
			size--;
		}
		
		std::vector<int> top () {
				return this->val[size-1];
		}
		
		bool isEmpty () {
			if (size == 0) {
				return true;
			}
			return false;
		}
};

int randint(int a, int b) {
	int result = a + int(b*(rand()/(1.0 + RAND_MAX)));
	return result;
}

int iter(complex c) {
	complex C(0, 0);
	int count = 0;
	while (count < MAX_ITER) {
		C = C*C + c;
		if (C.mag() > 2) {
			break;
		}
		count++;
	}
	return count;
}

int main()
{
	int width = 1024;
	int height = 1024;
	
	double zoom = 1;
	
	for (int i = 0; i<800; i++) {
		zoom *= 0.975;
	}
	
	//double xcenter = -0.16;
	//double ycenter = 1.04;
	//double xcenter = 0.42875;
	//double ycenter = -0.231345;
	double xcenter = -1.62917;
	double ycenter = -0.0203968;
	double xwidth = 4;
	double ywidth = 4;
	
	double leftx = xcenter - xwidth/2.0;
	double rightx = xcenter + xwidth/2.0;
	double topy = ycenter + ywidth/2.0;
	double bottomy = ycenter - ywidth/2.0;
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Zoom");
	sf::Texture texture;
	if (!texture.create(width, height)) {
		std::cout<<"Error"<<std::endl;
	}
	
	sf::Uint8* pixels = new sf::Uint8[width * height * 4];
	int* next = new int[width*height];
	int* rep = new int[width*height];
	
	for (int i = 0; i < width*height; i++) {
		rep[i] = 0;
		next[i] = i + 1;
	}
	
	int count = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		xwidth *= 0.975;
		ywidth *= 0.975;
		leftx = xcenter - xwidth/2.0;
		rightx = xcenter + xwidth/2.0;
		topy = ycenter + ywidth/2.0;
		bottomy = ycenter - ywidth/2.0;
		
		
		if (rightx > leftx && topy > bottomy) {
			count++;
			int prev = 0;
			int* temp1 = next;
			
			int i = 0;
			stack s;
			bool yes = true;
			while (true) {
				//std::cout<<i<<" "<<next[i]<<" "<<temp1[i]<<std::endl;
				if (i == width*height) {
					break;
				}
				double xstep = (rightx-leftx)/width;
				double ystep = (topy-bottomy)/height;
			
				double X = leftx + ((i - (i/width)*width)%height)*xstep;
				double Y = topy - (i/width)*ystep;
			
				int num = iter(complex(X, Y));
				
				if (yes) {
				if (s.isEmpty()) {
					if (temp1[i] == i+1) {
						std::vector<int> v;
						v.push_back(i);
						v.push_back(num);
						s.push(v);
					}
				}
				else {
					if (i%width == width-1) {
						//next[s.top()[0]] = i;
						double newxstep = xstep*0.975;
						double newystep = ystep*0.975;
						double newleftx = xcenter - (xwidth*0.975)/2;
						double newrightx = xcenter + (xwidth*0.975)/2;
						double newtopy = ycenter + (ywidth*0.975)/2;
						double newbottomy = ycenter - (ywidth*0.975)/2;
						double prevx = leftx + ((s.top()[0] - (s.top()[0]/width)*width)%height)*xstep;
						double prevy = topy - (s.top()[0]/width)*ystep;
						if (newleftx < prevx && prevx < newrightx && newbottomy < prevy && prevy < newtopy) {
							int prevY = (newtopy - prevy)/newystep;
							int prevX = (prevx - newleftx)/newxstep;
							int thisX = (i - (i/width)*width)%height;
							int thisY = i/width;
							if (0<=prevX && prevX < width && thisX/width == prevX/width && thisY == prevY) {
								if (i > prevX*width + prevY) {
									next[prevX*width + prevY] = i;
									std::cout << prevX << " " << prevY << " " << thisX << " " << thisY << std::endl;
								}
							}
						}
						s.pop();
					}
					else {
						if (!(s.top()[1]-1 <= num && num <= s.top()[1]+1)) {
							//next[s.top()[0]] = i;
							double newxstep = xstep*0.975;
							double newystep = ystep*0.975;
							double newleftx = xcenter - (xwidth*0.975)/2;
							double newrightx = xcenter + (xwidth*0.975)/2;
							double newtopy = ycenter + (ywidth*0.975)/2;
							double newbottomy = ycenter - (ywidth*0.975)/2;
							double prevx = leftx + ((s.top()[0] - (s.top()[0]/width)*width)%height)*xstep;
							double prevy = topy - (s.top()[0]/width)*ystep;
							if (newleftx < prevx && prevx < newrightx && newbottomy < prevy && prevy < newtopy) {
								int prevY = (newtopy - prevy)/newystep;
								int prevX = (prevx - newleftx)/newxstep;
								int thisX = (i - (i/width)*width)%height;
								int thisY = i/width;
								if (0<=prevX && prevX < width && thisX/width == prevX/width && thisY == prevY) {
									if (i > prevX*width + prevY) {
										next[prevX*width + prevY] = i;
										std::cout << prevX << " " << prevY << " " << thisX << " " << thisY << std::endl;
									}
								}
							}
							s.pop();
							std::vector<int> v;
							v.push_back(i);
							v.push_back(num);
							s.push(v);
						}
					}
				}
				yes = !yes;
				}
				else {
					temp1[i] = i+1;
					yes = !yes;
				}
				for (int k = i; k < temp1[i]; k++) {
					for (int j = 0; j < 3; j++) {
						if (num == 0) {
							pixels[4*k + j] = 0;
						}
						else {
							//pixels[4*i + j] = (num%(4*(j+1)))*(256/(4*(j+1)));
							if (num == MAX_ITER) {
								pixels[4*k+j] = 0;
							}
							else {
								if (j == 1) {
									pixels[4*k+j] = double(num)*255/MAX_ITER;
								}
								else {
									pixels[4*k+j] = 0;
								}
							}
						}
					}	
					pixels[4*k + 3] = 255;
				}
				
				i = temp1[i];
			}
		}
		else {
			std::cout << leftx << " " << rightx << std::endl;
			std::cout << bottomy << " " << topy << std::endl;
			int x;
			std::cin>>x;
		}
		//sf::Image img;
		//img.create(width, height, pixels);
		//std::string str;
		//str = "Images/"+std::to_string(count)+".png";
		texture.update(pixels);
		sf::Sprite sprite(texture);
		//img = texture.copyToImage();
		//img.saveToFile(str);
		window.clear();
		window.draw(sprite);
		window.display();
	}
	
    return 0;
}
