
#ifndef MY_PVN_Engine_HEAD
#define MY_PVN_Engine_HEAD

#include "state.h"
#include "model.h"
#include "camera.h"
#include "3dPt.h"
#include "3vec.h"
#include "physics.h"

extern game_state currentState;
extern game_physics gPhysics;

namespace game_engine {
    //Methods to generate the appropriate next state from the given one.
    void nextState(double timeElapsed);
    
    void moveModel(game_model & m);
    void updateCamera(game_camera & c);
}

#endif

