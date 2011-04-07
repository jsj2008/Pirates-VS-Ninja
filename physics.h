#ifndef My_physics_head_bullet
#define My_physics_head_bullet

/*
    Based heavily on the HelloWorld app provided with Bullet
*/

#include "btBulletDynamicsCommon.h"
#include <stdio.h>

class game_physics {
    private:
        btDefaultCollisionConfiguration* collisionConfiguration
        btCollisionDispatcher*                  dispatcher;
        btBroadphaseInterface*                  broadphase;
        btSequentialImpulseConstraintSolver*    solver;
        btDiscreteDynamicsWorld*                dynamicsWorld;
    
    public:
        game_physics();
        ~game_physics();
        
        void init();
        //void addObject(); //How the heck am I going to do THIS part...
        void update(double deltaTime);
    
    private:
};

#endif

