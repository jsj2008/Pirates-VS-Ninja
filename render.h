
#ifndef MY_PVN_Render_HEAD
#define MY_PVN_Render_HEAD

#include <GL/glut.h>
#include <list>
#include <string>
#include "model.h"
#include "state.h"
#include "camera.h"
#include "BMPLoader.h"

extern unsigned int windowX;
extern unsigned int windowY;
extern game_state currentState;
extern game_camera tempCam;

namespace game_render {
    class gameRender {
        private:
            unsigned int textures;
            //gameState myState;
        
        public:
            void init(void);
            void bindTexture(std::string & filename, game_model & model);
            
        private:
    };

    void display(void);

    void reshape(int x, int y);
    
    void renderModel(game_model & m);
}

#endif

