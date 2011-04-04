
#include "camera.h"

game_camera::game_camera(game_model * p, const f3dPt & offset) {
    player = p;
    
    lookFrom = offset;
    lookUp = f3vec(0, 1, 0);
    
    third = true;
    //debug();
}

game_camera::game_camera(const game_camera & other) {
    copyData(other);
}

game_camera & game_camera::operator=(const game_camera & other) {
    copyData(other);
    return *this;
}

void game_camera::draw() {
    f3dPt pos = (player->getPosition());
    y_rotation = player->getRotation();
    
    
    if(third) {
        gluLookAt(0, 2, -2,
            pos.X(), pos.Y(), pos.Z(),
            0, 1, 0);
    }
    else {
        f3dPt from(pos.X(), pos.Y() + 2, pos.Z());
        f3dPt at(from.X() + sin(y_rotation * RAD), from.Y(), from.Z() + cos(y_rotation * RAD));
        f3dPt up(0, 1, 0);
    
        gluLookAt(from.X(), from.Y() , from.Z(),
            at.X(), at.Y(), at.Z(),
            up.X(), up.Y(), up.Z());
    }
}

void game_camera::move(float x, float y, float z) {
    lookFrom.move(x, y, z);
}

void game_camera::rotate(float x, float y) {
    x_rotation += x;
    y_rotation += y;
}

void game_camera::setTarget(game_model * m) {
    player = m;
}

bool game_camera::toggleThird() {
    third = !third;
    return third;
}

void game_camera::debug() {
    std::cout << "Camera:\n";
    std::cout << "LookFrom: "; lookFrom.debug(); std::cout << "\n";
    std::cout << "Player: ";
    //if(player) {
    //    player->debug(); std::cout << "\n";
    //}
    //else {
        std::cout << player << "\n";
    //}
}

void game_camera::copyData(const game_camera & other) {
    player = other.player;
    lookFrom = other.lookFrom;
    lookUp = other.lookUp;
    x_rotation = other.x_rotation;
    y_rotation = other.y_rotation;
}

void game_camera::rotateX() {        //look up/down
    
}

void game_camera::rotateY() {        //rotates about the player
    //translate pivot to center
    //perform orbital rotation around the y axis
    //now move back
}

//
//BEGIN follow_camera
//
//follow_camera::follow_camera(game_model * p, f3dPt & offset) : game_camera(p, offset) {}

//void follow_camera::draw() {
//    if(player) {
//        f3dPt pos = (player->getPosition());

//        gluLookAt(pos.X() + lookFrom.X(), pos.Y() + lookFrom.Y(), pos.Z() + lookFrom.Z(),
//            pos.X(), pos.Y(), pos.Z(),
//            lookUp.X(), lookUp.Y(), lookUp.Z());
//        gluLookAt(0 + lookFrom.X(), 0 + lookFrom.Y(), 0 + lookFrom.Z(),
//            0, 0, 0,
//            lookUp.X(), lookUp.Y(), lookUp.Z());
//    }
//}

//void follow_camera::move(float x, float y, float z) {}

//void follow_camera::rotate(float x, float y) {}

