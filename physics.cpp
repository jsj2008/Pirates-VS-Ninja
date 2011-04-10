
#include "physics.h"

game_physics::game_physics() {
    dynamicsWorld = 0;
    solver = 0;
    broadphase = 0;
    dispatcher = 0;
    collisionConfiguration = 0;
}

game_physics::~game_physics() {
    //cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	for (int i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0;j<collisionShapes.size();j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

    //Take out the rest of the trash
    delete dynamicsWorld;
    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;
}

void game_physics::init() {
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

    //Construct our cool little world
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	
    //Set Gravity
	dynamicsWorld->setGravity(btVector3(btScalar(0.),btScalar(-10.),btScalar(0.)));
}

void game_physics::update(double deltaTime) {
    //Make sure you have a good enough max ticks!  Prolly ten?
    //dynamicsWorld->stepSimulation(1.f/60.f,10);
}

void game_physics::addPlane(float * norm, float constant, game_model * model, float * transform, float mass) {
    btCollisionShape* tempShape = new btStaticPlaneShape(btVector3(btScalar(norm[0]),btScalar(norm[1]),btScalar(norm[2])), btScalar(constant));
    collisionShapes.push_back(tempShape);

    btTransform planeTransform;
	planeTransform.setIdentity();
	if(transform) {
	    planeTransform.setOrigin(btVector3(btScalar(transform[4]), btScalar(transform[5]), btScalar(transform[6])));
	    planeTransform.setRotation(btQuaternion(btScalar(transform[0]), btScalar(transform[1]), btScalar(transform[2]), btScalar(transform[3])));
	}
	
	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		tempShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is recommended, it provides inte    rpolation capabilities, and only synchronizes 'active' objects
	//  will need to change this to my own MotionState when I write one, though.
	btDefaultMotionState* myMotionState = new btDefaultMotionState(planeTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, tempShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
}

void game_physics::addSphere(float radius, game_model * model, float * transform, float mass) {
	btCollisionShape* tempShape = new btSphereShape(btScalar(radius));
	collisionShapes.push_back(tempShape);

    /// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
	if(transform) {
	    startTransform.setOrigin(btVector3(btScalar(transform[4]), btScalar(transform[5]), btScalar(transform[6])));
	    startTransform.setRotation(btQuaternion(btScalar(transform[0]), btScalar(transform[1]), btScalar(transform[2]), btScalar(transform[3])));
	}

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		tempShape->calculateLocalInertia(mass,localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, tempShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	dynamicsWorld->addRigidBody(body);
}

void game_physics::addBox(float * dimensions, game_model * model, float * transform, float mass) {
	btCollisionShape* tempShape = new btBoxShape(btVector3(btScalar(dimensions[0]),btScalar(dimensions[1]),btScalar(dimensions[2])));
	collisionShapes.push_back(tempShape);

    /// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
	if(transform) {
	    startTransform.setOrigin(btVector3(btScalar(transform[4]), btScalar(transform[5]), btScalar(transform[6])));
	    startTransform.setRotation(btQuaternion(btScalar(transform[0]), btScalar(transform[1]), btScalar(transform[2]), btScalar(transform[3])));
	}

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		tempShape->calculateLocalInertia(mass,localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, tempShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	dynamicsWorld->addRigidBody(body);	
}


////
//  Dynamic MotionState
///
PeteMotionState::PeteMotionState(const btTransform &initialpos, game_model * model) {
    mPos1 = initialpos;
    myModel = model;
}

PeteMotionState::~PeteMotionState() {
}

void PeteMotionState::getWorldTransform(btTransform &worldTrans) const {
    worldTrans = mPos1;
}

void PeteMotionState::setWorldTransform(const btTransform &worldTrans) {
    //Act on the info given
    btVector3 pos = worldTrans.getOrigin();
    myModel->setPosition(pos.x(), pos.y(), pos.z());
    
    //do rotation?
}
