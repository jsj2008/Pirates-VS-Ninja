#ifndef My_physics_head_bullet
#define My_physics_head_bullet

/*
    Based heavily on the HelloWorld app provided with Bullet
*/

#include "btBulletDynamicsCommon.h"
#include <stdio.h>

class game_physics {
    private:
        //Default pieces of the dynamics world        
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher*                  dispatcher;
        btBroadphaseInterface*                  broadphase;
        btSequentialImpulseConstraintSolver*    solver;
        btDiscreteDynamicsWorld*                dynamicsWorld;
        
	    //Holds all the physics objects (so they can be cleaned up later)
	    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    
    public:
        game_physics();
        ~game_physics();
        
        void init();
        void update(double deltaTime);
        
        //methods to add common objects
        //
        //  Transform is an array of 7 floats
        //      4 for the rotational quat
        //      and 3 to specify the origin
        //  Defaults to null to just stay at the origin and not rotate
        //
        void addPlane(float * norm, float constant, float * transform = NULL, float mass = 0.0f);
        void addSphere(float radius, float * transform = NULL, float mass = 0.0f);
        void addBox(float * dimensions, float * transform = NULL, float mass = 0.0f);

        //TODO - Create a function to create a dynamic object, and one for static, (one for kinematic?)
    
    private:
};

//TODO - write a MotionState class for dynamic objects
//TODO - write a MotionState class for kinematic objects

#endif

