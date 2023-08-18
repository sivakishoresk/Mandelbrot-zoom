#ifndef COMPLEX
#define COMPLEX

/*A class to handle complex numbers*/
class complex {
	private :
		/*Coordinates*/
		long double x;		
		long double y;
	
	public :
		complex();
		
		complex(long double a, long double b);
		
		long double mag();
		
		complex operator+ (const complex &b) const;
		
		complex operator* (const complex &b) const;
		
};

#endif
