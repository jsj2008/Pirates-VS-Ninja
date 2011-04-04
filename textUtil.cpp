
#include "textUtil.h"

using namespace std;

string * textUtil::parseLines(string fname, int * count) {
    int arrayMax = 100;
    string * ret = new string[arrayMax];
    string temp;
    ifstream fin(fname.c_str(), ios_base::in);
    
    int i = 0;
    //cout << "parsing: " << fname << endl;
    while(getline(fin, temp)) {
        if (i >= arrayMax) {
            //string * temp = ret;
            ret = growArray(ret, i, &arrayMax);
            //delete [] temp;
        }
        
        //cout << temp << endl;
        ret[i] = temp;
        i++;
    }

    /*for(int i = 0; i < ret.size(); i++) {
        cout << ret.at(i) << endl;
    }*/
    //cout << "Size at return: " << i << endl;
    
    *count = i;
    return ret;
}

string * textUtil::growArray(string * oldArray, int oldCount, int * sizeOut) {
    int newSize = 2 * oldCount;
    string * ret = new string[newSize];
    for(int i = 0; i < oldCount; ++i) {
        ret[i] = oldArray[i];
    }
    
    *sizeOut = newSize;
    return ret;
}

//Works great for strings with only one whitespace char in between the chunks,
//    otherwise it wil need some work.
string * textUtil::splitLine(string line, int * count) {
    string * ret = new string[100];
    int i = 0;

    if(line.size() == 0) {
        *count = 0;
        return NULL;
    }
    
    //Set up my string iterators (two to surround each chunk)
    string::iterator strS, strE;
    strS = line.begin();
    strE = strS + 1;
    
    //Divvy up the string
    while(strE < line.end()) {
        while(strE < line.end() && !isspace(*strE)) {
            ++strE;
        }
        //Add string to the array
        ret[i] = (string(strS,strE));
        i++;
        
        if(strE < line.end()) {
            strS = strE + 1;
            strE += 1;
        }
        
        if(i >= 100) {
            cout << "Doh!\n";
        }
    }
    
    /*for(int i = 0; i < ret.size(); i++) {
        cout << ret.at(i) << endl;
    }*/
    
    *count = i;
    return ret;
}

//Works great for strings with only one delimiter char in between the chunks,
//    otherwise it may need some work.
string * textUtil::splitLine(string line, char delim, int * count) {
    string * ret = new string[100];
    int i = 0;

    if(line.size() == 0) {
        *count = 0;
        return NULL;
    }
    
    //Set up my string iterators (two to surround each chunk)
    string::iterator strS, strE;
    strS = line.begin();
    strE = line.begin() + 1;
    
    //Divvy up the string
    while(strE < line.end()) {
        while(strE < line.end() && *strE != delim) {
            ++strE;
        }
        //Add string to the array
        ret[i] = (string(strS,strE));
        i++;
        
        if(strE < line.end()) {
            strS = strE + 1;
            strE += 1;
        }
    }
    
    /*for(unsigned int i = 0; i < ret.size(); i++) {
        cout << ret.at(i) << endl;
    }*/
    
    *count = i;
    return ret;
}
    
int textUtil::skipSpace(string  str, int index) {
    while(index < (int)str.length() && isspace(str[index])) {
        index++;
    }
    
    return index;
}

int textUtil::parseWord(string  str, string * strBuf, int index) {
    int start = index;
    
    while(index < (int)str.length() && isalpha(str[index])) {
        index++;
    }
    
    *strBuf = string(str, start, index - start);

    return index;
}

int textUtil::parseFloat(string  str, float * fBuf, int index) {
    int start = index;
    
    //grab the '-' if there is one
    if(index + 1 < (int)str.length() && str[index] == '-' &&
        (isdigit(str[index + 1]) || (str[index + 1] == '.' && 
            (index + 2 < (int)str.length() && isdigit(str[index + 2]))))) {
        index++;
        //cout << "Found a neg!\n";
    }
    //grab the pre-decimal digits
    while(index < (int)str.length() && isdigit(str[index])) {
        index++;
    }
    //check for a decimal point and post-decimal digits
    if(index + 1 < (int)str.length() && str[index] == '.' && isdigit(str[index + 1])) {
        index++;
        while(index < (int)str.length() && isdigit(str[index])) {
            index++;
        }
        //cout << "Found a decimal\n";
    }
    
    *fBuf = (float)atof(str.substr(start, index - start).c_str());

    return index;
}

int textUtil::parsePoint(string  str, f3dPt ** ptBuf, int index) {
    float x, y, z;
    
    index = parse3Floats(str, &x, &y, &z, index);
    
    *ptBuf = new f3dPt(x, y, z);

    return index;
}

int textUtil::parseVector(string  str, f3vec ** vecBuf, int index) {
    float x, y, z;
    
    index = parse3Floats(str, &x, &y, &z, index);
    
    *vecBuf = new f3vec(x, y, z);

    return index;
}

int textUtil::parse3Floats(string  str, float * x, float * y, float * z, int index) {
    index = parseFloat(str, x, index);
    index = skipSpace(str, index);
    index = parseFloat(str, y, index);
    index = skipSpace(str, index);
    index = parseFloat(str, z, index);
    
    return index;
}

void textUtil::test() {
    ///    Test the whole thing
    //string * testResults;
    //int i;
    
    //testResults = parseLines("box.obj", &i);
    
    //cout << "Printing test results\n";
    //cout << "ptr: " << testResults << "\tcount: " << i << endl;
    //for(i = i - 1; i >= 0; i--) {
        //cout << testResults[i] << endl;
    //}
    
    ///    Test SplitLines
    string * testResults;
    string * testResults2;
    int i = -1;
    
    testResults = splitLine("I love the stuff split by the thingies.", &i);
    
    for(i = i - 1; i>= 0; i--) {
        cout << testResults[i] << endl;
    }
    
    testResults2 = splitLine("Here.is.some.stuff.that.is.to.be.split", '.', &i);
    
    for(i = i - 1; i>= 0; i--) {
        cout << testResults2[i] << endl;
    }
}

