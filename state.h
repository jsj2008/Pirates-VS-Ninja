
#ifndef	MY_PVN_State_HEAD
#define	MY_PVN_State_HEAD

#include <list>

#include "camera.h"
#include "model.h"

class game_state {
	private:
		//Models and cameras
		game_model player;
		std::list<game_model> models;
		game_camera tempCam;
		//std::list<game_camera> cameras;
		bool thirdPerson;
		
		//state data
		int movementFlags;
		long int timeClick;
		int mouseXPos;
		int mouseYPos;
		int mouseXMove;
		int mouseYMove;
	
	public:
		game_state();
		game_state(game_state & other);
		game_state & operator=(game_state & other);
	
		game_model & getPlayer();
		int getFlags();
		bool flagSet(int flag);
		long int getTimeClick();
		int getMouseXMove();
		std::list<game_model> * getModels();
		game_camera & getCamera();
	
		void setPlayer(game_model & m);
		void moveMouse(int x, int y);
		void setFlag(int flag);
		void clearFlag(int flag);
		void setMousePosition(int xPos, int yPos);
		void clearMouseXMove();
		void addModel(game_model & gm);
		
		void toggleThirdPerson();
		bool isThirdPerson();
	
	private:
		void copyData(game_state & other);
};

#endif

