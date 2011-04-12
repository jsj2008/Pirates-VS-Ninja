#ifndef MY_PVN_Controller_HEAD
#define MY_PVN_Controller_HEAD

#include <ctime>
#include "state.h"
#include "camera.h"
#include "flags.h"
#include "engine.h"
#include "objParser.h"
#include "render.h"

//Define global constants
#define CLOCKS_PER_MILLI (CLOCKS_PER_SEC/1000)

extern unsigned int windowX;
extern unsigned int windowY;
extern game_render::gameRender myRenderer;
extern game_physics gPhysics;
extern game_state currentState;
extern game_camera tempCam;
extern objParser objParse;

namespace game_controller {
    //long int lastGameClock = clock();

    //game state management
    game_state & init();
    game_state & initPlayer(game_state & current);
    game_state & reset();
    
    //semi-arbitrary helper functions
    game_state & loadSkybox(game_state & current);
    
    //game stuff.  Very important and all that
    void idle();    //openGL Idle function: performs the main game loop
    int timePassed(time_t start);    //gives the time passed in milliseconds
    
    //I/O handlers
    void keyboard(unsigned char key, int x, int y);
    void keyboardSpecial(int key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y);
    void keyboardSpecialUp(int key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);
    void passiveMotion(int x, int y);
    void snapBackToCenter();
}

#endif

