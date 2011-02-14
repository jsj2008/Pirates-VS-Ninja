// My cs455 3d Homogenous point class

#include "3dPt.h"

using namespace std;

f3dPt::f3dPt() {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

f3dPt::f3dPt(const f3dPt & otherP) {
	x = otherP.x;
	y = otherP.y;
	z = otherP.z;
	w = otherP.w;
}

f3dPt::f3dPt(const std::string * pt, int count) {
	//cout << "creating a new point: ";
	//for(int i = 0; i < count; i++) {
	//	cout << pt[i] << ", ";
	//}
	//cout << endl;
	
	if(count >= 3) {
		x = (float)atof(pt[1].c_str());
		y = (float)atof(pt[2].c_str());
	}
	else {
		x = 0;
		y = 0;
	}
	
	if(count >= 4) {
		z = (float)atof(pt[3].c_str());
	}
	else {
		z = 0;
	}
	
	if(count >= 5) {
		w = (float)atof(pt[4].c_str());
	}
	else {
		w = 1;
	}
	
	//cout << x << ", " << y << ", " << z << ", " << w << endl;
	
	//delete [] pt;
}

f3dPt::f3dPt(const float newx, const float newy, const float newz) {
	x = newx;
	y = newy;
	z = newz;
	w = 1;
}

f3dPt & f3dPt::operator=(const f3dPt & other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	
	return *this;
}
		
float f3dPt::X() {
	return x/w;
}

float f3dPt::Y() {
	return y/w;
}

float f3dPt::Z() {
	return z/w;
}

float f3dPt::W() {
	return w;
}

void f3dPt::setX(float newx) {
	x = newx;
}

void f3dPt::setY(float newy) {
	y = newy;
}

void f3dPt::setZ(float newz) {
	z = newz;
}

void f3dPt::setW(float neww) {
	w = neww;
}

float f3dPt::dist(f3dPt & other) {
	return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

void f3dPt::move(float moveX, float moveY, float moveZ) {
	x += moveX;
	y += moveY;
	z += moveZ;
}

void f3dPt::debug() {
	cout << "(" << x << ", " << y << ", " << z << ", " << w << ")";
}
