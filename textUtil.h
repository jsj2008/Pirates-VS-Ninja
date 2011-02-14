// Header cs455 project 2

#ifndef	My_TextUtil_HEAD
#define My_TextUtil_HEAD

#include <cctype>
#include <string>
#include <fstream>
#include <iostream>

#include "3dPt.h"
#include "3vec.h"

namespace textUtil {
	std::string * parseLines(std::string fname, int * count);
	std::string * splitLine(std::string line, int * count);
	std::string * splitLine(std::string line, char delim, int * count);

	//general utilities
	int skipSpace(std::string str, int index=0);
	int parseWord(std::string str, std::string * strBuf, int index=0);
	int parseFloat(std::string str, float * fBuf, int index=0);
	int parsePoint(std::string  str, f3dPt ** ptBuf, int index);
	int parseVector(std::string  str, f3vec ** vecBuf, int index);
	int parse3Floats(std::string str, float * x, float * y, float * z, int index=0);
	
	//Test the functionality of the code
	std::string * growArray(std::string * oldArray, int oldCount, int * sizeOut);
	void test(void);
}

#endif
