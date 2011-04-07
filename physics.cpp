
#include "physics.h"

game_physics::game_physics() {
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

    //Construct our cool little world
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));
}

game_physics::~game_physics() {
    //Take out the trash
    delete dynamicsWorld;
    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;

    
}

void game_physics::init() {}

void game_physics::update(double deltaTime) {
    //Make sure you have a good enough max ticks!  Prolly ten?
}
