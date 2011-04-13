// Header cs455 project 2

#ifndef My_Model_HEAD
#define My_Model_HEAD

#include <cmath>
#include <vector>
#include "face.h"
#include "3dPt.h"
#include "flags.h"
#include "BMPLoader.h"
//#include "matrix.h"
#include "physics.h"

#define RAD 0.0174532925

class game_model {
    friend class objParser;
    
protected:
    //Keep track of model info
    f3vec color;    //for untextured objects
    unsigned int texture;
    std::vector<f3dPt> verts;
    std::vector<f3dPt> texVerts;
    std::vector<f3dPt> normals;
    std::vector<face> faces;
    BMPClass bmp;
    
    //Keep track of position/direction
    float scale;
    f3dPt offset;
    f3dPt position;
    double y_rotation;    //old phase out?
    float * quat;
    btMotionState * physics;
    
    
    //parent in the rendering tree
    //model * parent;
    
    //Children in the rendering tree
    //model * children;
    //int childCount;

public:
    //Constructors
    //game_model();
    game_model(const game_model & other);
    //    initializes to a black cube
    game_model(f3vec col = f3vec(0, 0, 0), f3dPt pos = f3dPt(-.5, 0, -.5), double rot = 0, float size = 1.0);
    
    //operators
    game_model & operator=(const game_model & other);
    
    //setters/mutators
    void clear();
    void setColor(f3vec col);
    void setTexture(unsigned int tex);
    void move(f3vec & dir);
    void move(int dir);
    void move(float x, float y, float z);
    void setPosition(float x, float y, float z);
    void rotate(double degrees);
    void setScale(float size);
    void setQuat(float * q);
    void setQuat(float x, float y, float z, float w);
    void setPhysics(btMotionState * phys) { physics = phys; }
    void movePhysics();
    
    //getters
    std::vector<f3dPt> & getVerts();
    std::vector<f3dPt> & getTexVerts();
    std::vector<f3dPt> & getNormals();
    std::vector<face> & getFaces();
    f3vec & getColor();
    f3dPt & getOffset();
    f3dPt & getPosition();
    double getRotation();
    unsigned int getTexture();
    BMPClass & getTexHolder();
    float getScale();
    float * getQuat();
    
    //debug
    void debug();
private:
    void copyData(const game_model & other);
};

#endif
