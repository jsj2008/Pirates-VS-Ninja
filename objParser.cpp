// My sweet obj parser
//
//	Used to parse out the basic pieces of an obj to be passed to openGL for
//	drawing.

#include "objParser.h"

using namespace std;

//default constructor
objParser::objParser() {
	lines = 0;
}

//default destructor
objParser::~objParser() {
	clear();
}

//clears this objParser
void objParser::clear() {
	verts.clear();
	texVerts.clear();
	normals.clear();
	faces.clear();
	delete [] lines;
}

//tells the Parser to parse and store the given .obj file
void objParser::parse(string fname, game_model * m) {
	clear();
	int lineCount = 0;
	
	lines = textUtil::parseLines(fname, &lineCount);
	//cout << "Size after return: " << lineCount << endl;
	
	
	for(int i = 0; i < lineCount; ++i){
		parseLine(lines[i]);
	}
	
	storeInfo(m);
}

//stores the parsed info into the provided model
void objParser::storeInfo(game_model * m) {
	list<f3dPt>::iterator ptIter;
	list<face>::iterator faceIter;
	
	ptIter = verts.begin();
	vector<f3dPt> vertsVector(verts.size());
	for(unsigned int i = 0; i < verts.size(); i++) {
		vertsVector.at(i) = *ptIter;
		ptIter++;
	}
	m->verts = vertsVector;
	
	ptIter = texVerts.begin();
	vector<f3dPt> texVertsVector(texVerts.size());
	for(unsigned int i = 0; i < texVerts.size(); i++) {
		texVertsVector.at(i) = *ptIter;
		ptIter++;
	}
	m->texVerts = texVertsVector;
	
	ptIter = normals.begin();
	vector<f3dPt> normalsVector(normals.size());
	for(unsigned int i = 0; i < normals.size(); i++) {
		normalsVector.at(i) = *ptIter;
		ptIter++;
	}
	m->normals = normalsVector;
	
	faceIter = faces.begin();
	vector<face> facesVector(faces.size());
	for(unsigned int i = 0; i < faces.size(); i++) {
		facesVector.at(i) = *faceIter;
		faceIter++;
	}
	m->faces = facesVector;
}

//parse and store the given line
void objParser::parseLine(string line) {
	string * words;
	int wordCount = 0;
	//cout << "Parsing: " << line << endl;
	words = textUtil::splitLine(line, &wordCount);

	if(wordCount > 0) {
		//cout << "words out : " << wordCount << endl;
		//cout << words[0] << endl;
		
		if(words[0] == "v") {
			//cout << "vert\n";			
			verts.push_back(f3dPt(words, wordCount ));
		}
		else if(words[0] == "vt") {
			//cout << "tex\n";
			texVerts.push_back(f3dPt(words, wordCount));
		}
		else if(words[0] == "vn") {
			//cout << "normal\n";
			normals.push_back(f3dPt(words, wordCount));
		}
		else if(words[0] == "f") {
			//cout << "face\n";
			faces.push_back(face(words, wordCount));
		}
		else{
			//cout << "found some other stuff\n";
		}
	}
	
	delete [] words;
}

void objParser::debug() {
	list<f3dPt>::iterator ptIter;
	list<face>::iterator faceIter;
	
	cout << "Debugging objParser: \n";
	
	for(ptIter = verts.begin(); ptIter != verts.end(); ptIter++) {
		(*ptIter).debug();
		cout << endl;
	}
	
	for(ptIter = texVerts.begin(); ptIter != texVerts.end(); ptIter++) {
		(*ptIter).debug();
		cout << endl;
	}
	
	for(ptIter = normals.begin(); ptIter != normals.end(); ptIter++) {
		(*ptIter).debug();
		cout << endl;
	}
	
	for(faceIter = faces.begin(); faceIter != faces.end(); faceIter++) {
		(*faceIter).debug();
		//cout << endl;
	}
}

void objParser::test() {
	game_model m;
	objParser o;
	
	o.parse("square.obj", &m);
	
	o.debug();
	m.debug();
}

