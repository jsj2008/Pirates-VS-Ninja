// Header cs455 project 2

#ifndef	My_Face_HEAD
#define My_Face_HEAD

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "textUtil.h"

class face {
	private:
		std::vector<int> v;
		std::vector<int> t;
		std::vector<int> n;
	
	public:
		//constructors
		face();
		face(const face & other);
		face(const std::string * pts, int count);
		face(int * vtn, int count);

		face & operator=(const face & other);
		
		//getters
		int vAt(int i);
		int tAt(int i);
		int nAt(int i);
		unsigned int size();
		
		//setters
		/*void setV(int newV);
		void setT(int newT);
		void setN();*/
		
		//debug
		static void test();
		void debug();
	
	private:
};

#endif
