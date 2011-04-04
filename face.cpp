//represents a polygon or face of a 2d object

#include "face.h"

using namespace std;

face::face() {}

face::face(const face & other) {
    v = other.v;
    t = other.t;
    n = other.n;
}

face::face(int * vtn, int count) {
    v = vector<int>(count);
    t = vector<int>(count);
    n = vector<int>(count);
    
    for(int i = 0; i < count; i++) {
        int index = i * 3;
        v.at(i) = vtn[index];
        t.at(i) = vtn[index + 1];
        n.at(i) = vtn[index + 2];
    }
}

face & face::operator=(const face & other) {
    v = other.v;
    t = other.t;
    n = other.n;

    return *this;
}

face::face(const std::string * pts, int count) {
    int indexCount;
    string * indices;
        
    for(int i = 1; i < count; ++i) {    //Skip the f at the beginning of the line
        //cout << pts.at(i);
        indices = textUtil::splitLine(pts[i], '/', &indexCount);
        
        //cout << "point: " << pts[i] << endl;
        //cout << "indices Size: " << indices->size();// << ":" << indices->at(0) << "," << indices->at(1) << "  ";
        
        // TODO This needs to handle x, x//x, and x/x/x all equally well
        v.push_back(atoi(indices[0].c_str()));
        t.push_back(atoi(indices[1].c_str()));
        n.push_back(atoi(indices[2].c_str()));
        
        delete [] indices;
    }
    
    /*cout << "[";
    for(unsigned int j = 0; j < v.size(); ++j) {
        cout << "(" << v.at(j) << ", " << t.at(j) << ", " << n.at(j) << "), ";        
    }
    cout << "]\n";*/
}

//getters
int face::vAt(int i) {
    //adjust for array indexing
    return v.at(i) - 1;
}
int face::tAt(int i) {
    //adjust for array indexing
    return t.at(i) - 1;
}
int face::nAt(int i) {
    //adjust for array indexing
    return n.at(i) - 1;
}

unsigned int face::size() {
    return v.size();
}

void face::test() {
    int testIn[12] = {1, 0, 1, 2, 0, 1, 3, 0, 1, 4, 0, 1};

    face f(testIn, 4);
    
    f.debug();    
}

void face::debug() {
    cout << "Size: " << size() << endl;
    for(unsigned int i = 0; i < size(); ++i) {
        cout << "Face[" << i << "]: "  << v.at(i) << ", " << t.at(i) << ", " << n.at(i) << "\n";
    }
}
