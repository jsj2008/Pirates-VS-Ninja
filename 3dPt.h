// Header cs455 project 2

#ifndef My_3dPoint_HEAD
#define My_3dPoint_HEAD

#include <iostream>
#include <cstdlib>
//#include <string>
//#include <vector>
#include <math.h>

class f3dPt {
    private:
        float x;
        float y;
        float z;
        float w;

    public:
        //constructors
        f3dPt();
        f3dPt(const f3dPt & otherP);
        f3dPt(const std::string * pt, int count);
        f3dPt(const float newx, const float newy, const float newz = 0);
        
        //operators
        f3dPt & operator=(const f3dPt & other);
        
        //getters (returns the ACTUAL values of xyz)
        float X();
        float Y();
        float Z();
        float W();
        
        //setters
        void setX(float newx);
        void setY(float newy);
        void setZ(float newz);
        void setW(float neww);
        
        //Other fun stuffs.  :D
        float dist(f3dPt & other);
        void move(float movex, float moveY, float moveZ);
        
        //debug
        void debug();
        
    private:
};

#endif
