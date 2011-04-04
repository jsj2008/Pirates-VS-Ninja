
#include "controller.h"
//Only needed for debug
#include <iostream>

game_state & game_controller::init() {
	game_state newState;
	
	initPlayer(newState);
	
	game_model ground(f3vec(0, 1, 0));
	std::string s("grass.bmp");
	myRenderer.bindTexture(s, ground);
	objParse.parse("square.obj", &ground);
	newState.addModel(ground);
	//loadSkybox(newState);
	
	currentState = newState;
	
	return currentState;
}

game_state & game_controller::initPlayer(game_state & current) {
	game_model p(f3vec(0, 0, 0), f3dPt(0, 10.931100, 0), 0, .1);
	objParse.parse("humanoid.obj", &p);
	current.setPlayer(p);
	return current;
}

game_state & game_controller::reset() {
	
	return currentState;
}

game_state & game_controller::loadSkybox(game_state & current) {
	game_model c1(f3vec(.47451, .70980, .90588), f3dPt(0, 0, 0), 0, 1);
	c1.move(0, 0, -500);
	std::string str("clouds.bmp");
	myRenderer.bindTexture(str, c1);
	objParse.parse("sky1.obj", &c1);
	current.addModel(c1);
	
	unsigned int tex = c1.getTexture();
	
	game_model c2(f3vec(.47451, .70980, .90588), f3dPt(0, 0, 0), 90, 1);
	c2.move(0, 500, 0);
	objParse.parse("sky1.obj", &c2);
	c2.setTexture(tex);
	current.addModel(c2);
	
	game_model c3(f3vec(.47451, .70980, .90588), f3dPt(0, 0, 0), 180, 1);
	c3.move(0, 0, 500);
	objParse.parse("sky1.obj", &c3);
	c3.setTexture(tex);
	current.addModel(c3);
	
	game_model c4(f3vec(.47451, .70980, .90588), f3dPt(0, 0, 0), 270, 1);
	c4.move(0, -500, 0);
	objParse.parse("sky1.obj", &c4);
	c4.setTexture(tex);
	current.addModel(c4);
	
	return current;
}

void game_controller::idle() {
	double timeSlice = timePassed(currentState.getTimeClick());
	//std::cout << "Time passed: " << timeSlice << std::endl;

	game_engine::nextState(timeSlice);

	glutPostRedisplay();
}

int game_controller::timePassed(time_t start) {
	return (clock() - start)/CLOCKS_PER_MILLI;
}

void game_controller::keyboard(unsigned char key, int x, int y) {
	//std::cout << "Key DWN: " << key << " (" << x << ", " << y << ") \n";
	switch(key) {
		//MOVEMENT KEYS
		//	only allow motion in one direction per axis at a time
		case 'w':
			//currentState.getPlayer().move(MOVE_FORWARD);
			currentState.setFlag(MOVE_FORWARD);
			currentState.clearFlag(MOVE_BACKWARD);
			break;
		case 'a':
			//currentState.getPlayer().move(MOVE_BACKWARD);
			currentState.setFlag(MOVE_LEFT);
			currentState.clearFlag(MOVE_RIGHT);
			break;
		case 's':
			//currentState.getPlayer().move(MOVE_LEFT);
			currentState.setFlag(MOVE_BACKWARD);
			currentState.clearFlag(MOVE_FORWARD);
			break;
		case 'd':
			//currentState.getPlayer().move(MOVE_RIGHT);
			currentState.setFlag(MOVE_RIGHT);
			currentState.clearFlag(MOVE_LEFT);
			//tempCam.move();
			break;
		case 27:	//ESCAPE KEY
			exit(0);
		default:
			std::cout << "Unimplemented key: " << key << std::endl;
	}
}

void game_controller::keyboardSpecial(int key, int x, int y) {
	//std::cout << "Special DWN: " << key << " (" << x << ", " << y << ") \n";
	
	switch(key) {
		case 1:
			currentState.getCamera().toggleThird();
			currentState.toggleThirdPerson();
			break;
		case 100:
			//currentState.getPlayer().rotate(5);
			currentState.setFlag(TURN_LEFT);
			currentState.clearFlag(TURN_RIGHT);
			break;
		case 102:
			//currentState.getPlayer().rotate(-5);
			currentState.setFlag(TURN_RIGHT);
			currentState.clearFlag(TURN_LEFT);
			break;
	}
}

void game_controller::keyboardUp(unsigned char key, int x, int y) {
	//std::cout << "Key UP: " << key << " (" << x << ", " << y << ") \n";
	switch(key) {
		case 'w':
			currentState.clearFlag(MOVE_FORWARD);
			break;
		case 'a':
			currentState.clearFlag(MOVE_LEFT);
			break;
		case 's':
			currentState.clearFlag(MOVE_BACKWARD);
			break;
		case 'd':
			currentState.clearFlag(MOVE_RIGHT);
			break;
	}
}

void game_controller::keyboardSpecialUp(int key, int x, int y) {
	//std::cout << "Special UP: " << key << " (" << x << ", " << y << ") \n";
	
	switch(key) {
		case 100:
			currentState.clearFlag(TURN_LEFT);
			break;
		case 102:
			currentState.clearFlag(TURN_RIGHT);
			break;
	}
}

void game_controller::mouse(int button, int state, int x, int y) {
	//std::cout << "Button: " << button << " - State: " << state << " (" << x << ", " << y << ") \n";
}

void game_controller::motion(int x, int y) {
	//std::cout << "Motion: (" << x << ", " << y << ") \n";
}

void game_controller::passiveMotion(int x, int y) {
	//std::cout << "Passive motion: (" << x << ", " << y << ") \n";
	
	currentState.moveMouse(x, y);
}

void game_controller::mouseEntry(int state) {
	if(state == GLUT_LEFT) {
	    //std::cout << "Left!  Snapping to: (" << windowX / 2 << ", " << windowY / 2 << ") \n";
		currentState.setMousePosition(windowX / 2, windowY / 2);
		//currentState.mouseXPos = windowX / 2;
		glutWarpPointer(windowX / 2, windowY / 2);
	}
	
}

