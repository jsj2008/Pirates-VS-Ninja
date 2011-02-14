// Header cs455 project 2

#ifndef	My_3dVector_HEAD
#define My_3dVector_HEAD

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include "3dPt.h"

class f3vec {
	private:
		float x;
		float y;
		float z;

	public:
		f3vec();
		f3vec(float otherX, float otherY, float otherZ);
		f3vec(const f3vec & otherP);
		f3vec(f3dPt & pt);
		f3vec(f3dPt & porig, f3dPt & pdest);
		
		f3vec & operator=(const f3vec & other);
		
		bool equals(f3vec & otherP);
		
	//getters
		float X();
		float Y();
		float Z();
		
	//setters
		void setX(float newx);
		void setY(float newy);
		void setZ(float newz);
		
	//Vector Operations
		f3vec * add(f3vec & other);
		f3vec * add(f3dPt & other);
		f3vec * subtract(f3vec & other);
		f3vec * neg();
		void negMe();
	
		f3vec * scalProd(float scalar);
		float dotProd(f3vec & other);
		float dotProd(f3dPt & other);
		f3vec * crossProd(f3vec & other);
		f3vec * normalize();
		void normMe();
		float length();
		f3dPt * genPoint(f3dPt & ro, float scale = 1.0f);
		
		static void test(void);
		
	private:
};

#endif
