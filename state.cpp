
#include "state.h"

//Constructors

game_state::game_state() {
    tempCam.setTarget(player);
    movementFlags = 0;
    timeClick = 0;
    mouseXMove = 0;
    mouseYMove = 0;
    thirdPerson = tempCam.toggleThird();
}

game_state::game_state(game_state & other) {
    copyData(other);
}

//Operators

game_state & game_state::operator=(game_state & other) {
    copyData(other);
    return *this;
}

//Methods that read the state of this object

game_model * game_state::getPlayer() {
    return player;
}

int game_state::getFlags() {
    return movementFlags;
}

bool game_state::flagSet(int flag) {
    return movementFlags & flag;
}

long int game_state::getTimeClick() {
    long int ret = timeClick;
    timeClick = clock();
    
    return ret;
}

int game_state::getMouseXMove() {
    return mouseXMove;
}

std::list<game_model*> * game_state::getModels() {
    return &models;
}

game_camera & game_state::getCamera() {
    return tempCam;
}

//Methods that change the state of this object

void game_state::setPlayer(game_model * m) {
    player = m;
    //tempCam.setTarget(&player);
}

void game_state::moveMouse(int x, int y) {
    mouseXMove += x;
    mouseYMove += y;
}

void game_state::setFlag(int flag) {
    movementFlags |= flag;
}

void game_state::clearFlag(int flag) {
    movementFlags &= (~flag);
}

void game_state::clearMouseXMove() {
    mouseXMove = 0;
}

void game_state::addModel(game_model * gm) {
    models.push_back(gm);
}

void game_state::copyData(game_state & other) {
    player = other.player;
    models = std::list<game_model*>(other.models);
    tempCam = other.tempCam;
    tempCam.setTarget(player);
    //cameras = std::list<game_camera>(other.cameras);
    movementFlags = other.movementFlags;
    timeClick = other.timeClick;
    mouseXMove = other.mouseXMove;
    mouseYMove = other.mouseYMove;
}

void game_state::toggleThirdPerson() {
    thirdPerson = !thirdPerson;
}

bool game_state::isThirdPerson() {
    return thirdPerson;
}
