// Header cs455 project 2

#ifndef	My_OBJ_PARSER_HEAD
#define My_OBJ_PARSER_HEAD

#include <cctype>
#include <list>
#include <string>
#include <iostream>

#include "textUtil.h"
#include "3dPt.h"
#include "face.h"
#include "model.h"

class objParser {
	private:
		//list to store the file being parsed
		std::string * lines;
		std::list<f3dPt> verts;
		std::list<f3dPt> texVerts;
		std::list<f3dPt> normals;
		std::list<face> faces;

	public:
		//default constructor
		objParser();
		
		//default destructor
		~objParser();
		
		//clears this objParser
		void clear();
	
		//call to parse the file into the relevant pieces
		void parse(std::string fname, game_model * m);
		void storeInfo(game_model * m);
	
		void debug();
		static void test();
	private:
		void parseLine(std::string line);

};

#endif
