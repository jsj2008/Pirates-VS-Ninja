#ifndef MY_GAME_CAMERA_HEADER
#define MY_GAME_CAMERA_HEADER

#include <GL/glut.h>
#include <cmath>
#include "3dPt.h"
#include "3vec.h"
#include "model.h"

#ifndef RAD
#define RAD 0.0174532925
#endif

class game_camera {
	protected:
		f3dPt lookFrom;	//stores the offset from the player
		f3vec lookUp;
		
		float x_rotation;
		float y_rotation;
		
		game_model * player;
		
		bool third;
	
	public:
		game_camera(game_model * p = 0, const f3dPt & offset = f3dPt(0, 2, -10));
		game_camera(const game_camera & other);
		
		game_camera & operator=(const game_camera & other);
	
		virtual void draw();
		virtual void move(float x, float y, float z);
		virtual void rotate(float x, float y);
		void setTarget(game_model * m);
		bool toggleThird();
		
		void debug();
		
	private:
		void copyData(const game_camera & other);
		void rotateX();
		void rotateY();
};

//class follow_camera : public game_camera {
//	protected:
//			
//	public:
//		follow_camera(game_model * p, f3dPt & offset);
//	
//		virtual void draw();
//		virtual void move(float x, float y, float z);
//		virtual void rotate(float x, float y);
//		
//	private:
//};

#endif
