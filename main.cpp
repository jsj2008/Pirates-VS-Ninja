
#include "main.h"

int main(int argc, char** argv) {
    //textUtil::test();
    //objParser::test();
    ///eface::test();
        
    //tempCam.setTarget(&(currentState.getPlayer()));
    
    gPhysics.init();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowX, windowY);
    //glutInitWindowPosition(150, 50);    //centers in 800 x 600
    glutInitWindowPosition(500, 50);    //for the netbook
    glutCreateWindow("Pirates VS Ninja");
    myRenderer.init();
    game_controller::init();
    //currentState.getCamera().debug();
    
    glutDisplayFunc(game_render::display);
    //glutIdleFunc(game_render::display);
    glutIdleFunc(game_controller::idle);
    glutReshapeFunc(game_render::reshape);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutMouseFunc(game_controller::mouse);
    glutMotionFunc(game_controller::motion);
    glutPassiveMotionFunc(game_controller::passiveMotion);
    
    glutKeyboardFunc(game_controller::keyboard);
    glutSpecialFunc(game_controller::keyboardSpecial);
    glutKeyboardUpFunc(game_controller::keyboardUp);
    glutSpecialUpFunc(game_controller::keyboardSpecialUp);
    glutMainLoop();
    
    return 0;
}

