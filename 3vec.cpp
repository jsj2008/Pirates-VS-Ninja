// My cs455 3d vector class

#include "3vec.h"

using namespace std;

f3vec::f3vec() {
    x = 0;
    y = 0;
    z = 0;
}

f3vec::f3vec(float otherX, float otherY, float otherZ) {
    x = otherX;
    y = otherY;
    z = otherZ;
}

f3vec::f3vec(const f3vec & otherP) {
    x = otherP.x;
    y = otherP.y;
    z = otherP.z;
}

f3vec::f3vec(f3dPt & pt) {
    x = pt.X();
    y = pt.Y();
    z = pt.Z();
}

f3vec::f3vec(f3dPt & porig, f3dPt & pdest) {
    x = pdest.X() - porig.X();
    y = pdest.Y() - porig.Y();
    z = pdest.Z() - porig.Z();
}

f3vec & f3vec::operator=(const f3vec & other) {
    x = other.x;
    y = other.y;
    z = other.z;
    
    return *this;
}
        
float f3vec::X() {
    return x;
}

float f3vec::Y() {
    return y;
}

float f3vec::Z() {
    return z;
}

void f3vec::setX(float newx) {
    x = newx;
}

void f3vec::setY(float newy) {
    y = newy;
}

void f3vec::setZ(float newz) {
    z = newz;
}
        
bool f3vec::equals(f3vec & other) {
    if(x == other.x)
        if(y == other.y)
            if(z == other.z)
                return true;

    return false;
}

f3vec * f3vec::add(f3vec & other) {
    f3vec * ret = new f3vec(x + other.x, y + other.y, z + other.z);
    
    return ret;
}

f3vec * f3vec::add(f3dPt & other) {
    f3vec * ret = new f3vec(x + other.X(), y + other.Y(), z + other.Z());
    
    return ret;
}

f3vec * f3vec::subtract(f3vec & other) {
    f3vec * ret = new f3vec(x - other.x, y - other.y, z - other.z);
    
    return ret;
}

f3vec * f3vec::neg() {
    f3vec * ret = new f3vec(-x, -y, -z );
    
    return ret;
}

void f3vec::negMe() {
    x = -x;
    y = -y;
    z = -z;
}
        
f3vec * f3vec::scalProd(float scalar) {
    f3vec * ret = new f3vec(x * scalar, y * scalar, z * scalar);
    
    return ret;
} 

float f3vec::dotProd(f3vec & other) {
    return ((x * other.x) + (y * other.y) + (z * other.z));
}

float f3vec::dotProd(f3dPt & other) {
    return ((x * other.X()) + (y * other.Y()) + (z * other.Z()));
}

f3vec * f3vec::crossProd(f3vec & other) {
    f3vec * ret = new f3vec((y * other.z) - (z * other.y),
                    (z * other.x) - (x * other.z),
                    (x * other.y) - (y * other.x));
    
    return ret;
}

f3vec * f3vec::normalize() {
    float len = length();

    f3vec * ret = new f3vec(x / len, y / len, z / len);
    
    return ret;
}

void f3vec::normMe() {
    float len = length();

    x = x / len;
    y = y / len;
    z = z / len;
}

float f3vec::length() {
    return (float)sqrt((x * x) + (y * y) + (z * z));
}

f3dPt * f3vec::genPoint(f3dPt & ro, float scale) {
    f3dPt * ret = new f3dPt(ro);
    
    ret->setX(ret->X() + (x * scale));
    ret->setY(ret->Y() + (y * scale));
    ret->setZ(ret->Z() + (z * scale));
    
    return ret;
}

void f3vec::test() {
    f3vec * test1 = new f3vec;
    f3vec * test2 = new f3vec(1.0f, 1.0f, 1.0f);
    f3vec * test3 = test1->add(*test2);
    
    cout << "test3: " << test3->x << ", " << test3->y << ", " << test3->z << endl;
    
    f3vec * test4 = test3->subtract(*test2);
    
    if(test4->equals(*test1))
        cout << "Yup add/subt seems to work\n";
        
    cout << "length1: " << sqrt(3) << "<->" << test2->length() << endl;
    
    f3vec * test5 = test2->normalize();
    cout << "test5(" << 1/sqrt(3) << "): " << test5->x << ", " << test5->y << ", " << test5->z << endl;
    cout << "length5: " << test5->length() << endl;
    
    f3vec * test6 = test2->scalProd(.37f);
    cout << "test6(.37): " << test6->x << ", " << test6->y << ", " << test6->z << endl;
    
    cout << "1 . 2: (" << test1->dotProd(*test2) << " =? 0)" << endl;
    cout << "2 . 6: (" << test2->dotProd(*test6) << " =? " << 3 * .37 << ")" << endl;
    
    f3vec * test7 = test1->crossProd(*test2);
    f3vec * test8 = new f3vec(1.0f, -1.0f, 1.0f);
    f3vec * test9 = test2->crossProd(*test8);
    cout << "test7(1 x 2): " << test7->x << ", " << test7->y << ", " << test7->z << endl;
    cout << "test9(2 x 8): " << test9->x << ", " << test9->y << ", " << test9->z << endl;
}

