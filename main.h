
#ifndef MY_PVN_Main_HEAD
#define MY_PVN_Main_HEAD

#include <stdlib.h>
#include <GL/glut.h>
#include <cstdio>
#include <string>
#include <iterator>
#include <iostream>

#include "engine.h"
#include "state.h"
#include "render.h"
#include "controller.h"
#include "model.h"
#include "camera.h"
#include "objParser.h"

//#include "objParser.h"

//Define global constants
static const unsigned int INIT_WINDOW_SIZE_X = 500;
static const unsigned int INIT_WINDOW_SIZE_Y = 500;

//Declarations

//Globals
unsigned int windowX = INIT_WINDOW_SIZE_X;
unsigned int windowY = INIT_WINDOW_SIZE_Y;
objParser objParse;
game_render::gameRender myRenderer;
game_state currentState;

#endif

