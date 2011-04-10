
#include "model.h"

using namespace std;

//game_model::game_model() {
//    texture = 0;
//    color = f3vec(1, 0, 0);
//    offset = f3dPt(0, 0, 0);
//    position = f3dPt(0, 0, 0);
//    y_rotation = 0;
//    verts = std::vector<f3dPt>();
//    texVerts = std::vector<f3dPt>();
//    normals = std::vector<f3dPt>();
//    faces = std::vector<face>();
//}

game_model::game_model(f3vec col, f3dPt pos, double rot, float size) {
    bmp = BMPClass();
    texture = 0;
    color = col;
    offset = pos;
    position = f3dPt(0, 0, 0);
    y_rotation = rot;
    scale = size;
    
    
    verts = std::vector<f3dPt>(8);
    texVerts = std::vector<f3dPt>();
    normals = std::vector<f3dPt>(6);
    faces = std::vector<face>(12);
    
    verts.at(0) = f3dPt(0, 0, 0);
    verts.at(1) = f3dPt(0, 0, 1);    
    verts.at(2) = f3dPt(0, 1, 0);
    verts.at(3) = f3dPt(0, 1, 1);
    verts.at(4) = f3dPt(1, 0, 0);
    verts.at(5) = f3dPt(1, 0, 1);
    verts.at(6) = f3dPt(1, 1, 0);
    verts.at(7) = f3dPt(1, 1, 1);
    
    normals.at(0) = f3dPt(0, 0, 1);
    normals.at(1) = f3dPt(0, 0, -1);
    normals.at(2) = f3dPt(0, 1, 0);
    normals.at(3) = f3dPt(0, -1, 0);
    normals.at(4) = f3dPt(1, 0, 0);
    normals.at(5) = f3dPt(-1, 0, 0);
    
    int face1[9] = {1,0,2, 7,0,2, 5,0,2};    faces.at(0) = face(face1, 3);
    int face2[9] = {1,0,2, 3,0,2, 7,0,2};    faces.at(1) = face(face2, 3);
    int face3[9] = {1,0,6, 4,0,6, 3,0,6};    faces.at(2) = face(face3, 3);
    int face4[9] = {1,0,6, 2,0,6, 4,0,6};    faces.at(3) = face(face4, 3);
    int face5[9] = {3,0,3, 8,0,3, 7,0,3};    faces.at(4) = face(face5, 3);
    int face6[9] = {3,0,3, 4,0,3, 8,0,3};    faces.at(5) = face(face6, 3);
    int face7[9] = {5,0,5, 7,0,5, 8,0,5};    faces.at(6) = face(face7, 3);
    int face8[9] = {5,0,5, 8,0,5, 6,0,5};    faces.at(7) = face(face8, 3);
    int face9[9] = {1,0,4, 5,0,4, 6,0,4};    faces.at(8) = face(face9, 3);
    int face10[9] = {1,0,4, 6,0,4, 2,0,4};    faces.at(9) = face(face10, 3);
    int face11[9] = {2,0,1, 8,0,1, 6,0,1};    faces.at(10) = face(face11, 3);
    int face12[9] = {2,0,1, 8,0,1, 4,0,1};    faces.at(11) = face(face12, 3);
}

game_model::game_model(const game_model & other) {
    copyData(other);
}

void game_model::clear() {
    offset = f3dPt(0, 0, 0);
    position = f3dPt(0, 0, 0);
    y_rotation = 0;
    verts.clear();
    texVerts.clear();
    normals.clear();
    faces.clear();
}

game_model & game_model::operator=(const game_model & other) {
    copyData(other);
    
    return *this;
}

void game_model::setColor(f3vec col) {
    color = col;
}

void game_model::setTexture(unsigned int tex) {
    texture = tex;
}
    
void game_model::move(f3vec & v) {
    position.move(v.X(), v.Y(), v.Z());
}

void game_model::move(int dir) {
    if(dir == MOVE_FORWARD) {
        position.move(sin(y_rotation * RAD) / 10, 0, cos(y_rotation * RAD) / 10);
    }
    else if(dir == MOVE_BACKWARD) {
        position.move(-sin(y_rotation * RAD) / 10, 0, -cos(y_rotation * RAD) / 10);
    }
    else if(dir == MOVE_LEFT) {
        position.move(cos(y_rotation * RAD) / 10, 0, -sin(y_rotation * RAD) / 10);
    }
    else if(dir == MOVE_RIGHT) {
        position.move(-cos(y_rotation * RAD) / 10, 0, sin(y_rotation * RAD) / 10);
    }
}

void game_model::move(float x, float y, float z) {
    position.move(x, y, z);
}

void game_model::setPosition(float x, float y, float z) {
    position.set(x, y, z);
}

void game_model::rotate(double degrees) {
    y_rotation += degrees;
}

void game_model::setScale(float size) {
    scale = size;
}

std::vector<f3dPt> & game_model::getVerts() {
    return verts;
}

std::vector<f3dPt> & game_model::getTexVerts() {
    return texVerts;
}

std::vector<f3dPt> & game_model::getNormals() {
    return normals;
}

std::vector<face> & game_model::getFaces() {
    return faces;
}

f3vec & game_model::getColor() {
    return color;
}

f3dPt & game_model::getOffset() {
    return offset;
}

f3dPt & game_model::getPosition() {
    return position;
}

double game_model::getRotation() {
    return y_rotation;
}

unsigned int game_model::getTexture() {
    return texture;
}

BMPClass & game_model::getTexHolder() {
    return bmp;
}

float game_model::getScale() {
    return scale;
}

void game_model::debug() {
    cout << "Model" << endl;
//    for(unsigned int i = 0; i < verts.size(); i++) {
//        cout << "Vert: ";
//        verts.at(i).debug();
//        cout << endl;
//    }
//    for(unsigned int i = 0; i < texVerts.size(); i++) {
//        cout << "Tex Coord: ";
//        texVerts.at(i).debug();
//        cout << endl;
//    }
//    for(unsigned int i = 0; i < normals.size(); i++) {
//        cout << "Normal: ";
//        normals.at(i).debug();
//        cout << endl;
//    }
//    for(unsigned int i = 0; i < faces.size(); i++) {
//        cout << "Face: ";
//        faces.at(i).debug();
//        cout << endl;
//    }
    cout << "Offset: "; offset.debug(); cout << endl;
    cout << "Position: "; position.debug(); cout << endl;
}

void game_model::copyData(const game_model & other) {
    color = other.color;
    texture = other.texture;
    verts = vector<f3dPt>(other.verts);
    texVerts = vector<f3dPt>(other.texVerts);
    normals = vector<f3dPt>(other.normals);
    faces = vector<face>(other.faces);
    offset = other.offset;
    position = other.position;
    y_rotation = other.y_rotation;
    scale = other.scale;
}

