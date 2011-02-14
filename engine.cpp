
#include "engine.h"

void game_engine::nextState(double timeElapsed) {
	moveModel(currentState.getPlayer());
}
	
void game_engine::moveModel(game_model & m) {
	int flags = currentState.getFlags();

//This is inane and redundant and needs to be updated...
	if(flags & MOVE_FORWARD) {
		m.move(MOVE_FORWARD);
	}
	else if(flags & MOVE_BACKWARD) {
		m.move(MOVE_BACKWARD);
	}
	if(flags & MOVE_LEFT) {
		m.move(MOVE_LEFT);
	}
	else if(flags & MOVE_RIGHT) {
		m.move(MOVE_RIGHT);
	}
	if(flags & TURN_LEFT) {
		m.rotate(5);
	}
	else if(flags & TURN_RIGHT) {
		m.rotate(-5);
	}
	
	currentState.getPlayer().rotate(currentState.getMouseXMove());
	currentState.clearMouseXMove();
}
	
void game_engine::updateCamera(game_camera & c) {}
	
