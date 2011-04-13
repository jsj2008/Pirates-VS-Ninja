#ifndef My_physics_head_bullet
#define My_physics_head_bullet

/*
    Based heavily on the HelloWorld app provided with Bullet
*/

#include <stdio.h>

#include "btBulletDynamicsCommon.h"
#include "model.h"

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
        void addPlane(float * norm, float constant, game_model * model = NULL, float * transform = NULL, float mass = 0.0f);
        void addSphere(float radius, game_model * model = NULL, float * transform = NULL, float mass = 0.0f);
        void addBox(float * dimensions, game_model * model = NULL, float * transform = NULL, float mass = 0.0f);
        //void addCharacter();

        //TODO - Create a function to create a dynamic object, and one for static, (one for kinematic?)
    
    protected:
};

//TODO - write a MotionState class for dynamic objects
class PeteMotionState : public btMotionState {
    public:
        PeteMotionState(const btTransform &initialpos, game_model * model);

        virtual ~PeteMotionState();

        virtual void getWorldTransform(btTransform &worldTrans) const;
        virtual void setWorldTransform(const btTransform &worldTrans);
        
    protected:
        btTransform mPos1;
        game_model * myModel;
};

//TODO - write a MotionState class for kinematic objects

#endif

