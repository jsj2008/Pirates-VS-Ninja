
#include "render.h"
#include "btBulletDynamicsCommon.h"

using namespace std;

void game_render::gameRender::init(void) {
    //reset texture codes
    textures = 7;

    // select clearing(background) color
    glClearColor(.47451, .70980, .90588, 0);
    glClearDepth(1);

    //setup nicities
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // initialize viewing values
    glViewport(0,0,windowX,windowY);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    gluPerspective(45, (float)windowX/(float)windowY, .1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //Set up lighting
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float diffuse_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	float ambient_color[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	float position[4]      = {0.0f,20.0f, 3.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    //Set default drawing color
    //glColor3f(1.0, 1.0, 1.0);
}

void game_render::gameRender::bindTexture(string & filename, game_model & model) {
    model.setTexture(++textures);
    //cout << model.getTexture() << endl;

    BMPLoad(filename, model.getTexHolder());
    glBindTexture(GL_TEXTURE_2D, model.getTexture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model.getTexHolder().width,
        model.getTexHolder().height, 0, GL_RGB, GL_UNSIGNED_BYTE,
        model.getTexHolder().bytes);
}

//END CLASS

void game_render::display(void) {
    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        
    glLoadIdentity();
    //currentState.getCamera().debug();
    currentState.getCamera().draw();
    list<game_model*> * models = currentState.getModels();
    list<game_model*>::iterator modelIter;
    for(modelIter = models->begin(); modelIter != models->end(); modelIter++) {
        //(*modelIter).debug();
        renderModel(*modelIter);
    }
    
    if(currentState.isThirdPerson()) {
        renderModel(currentState.getPlayer());
        //currentState.getPlayer().debug();
    }
    
    
    glFlush();
    glutSwapBuffers();
    
    //glDisable(GL_TEXTURE_2D);
}

void game_render::reshape(int x, int y) {
    windowX = x;
    windowY = y;
    
    glMatrixMode(GL_PROJECTION);
    glViewport(0,0,x,y);
    glLoadIdentity();
    gluPerspective(45, (float)x/(float)y, .1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void game_render::renderModel(game_model * m) {
    f3vec col = m->getColor();
    glColor3f(col.X(), col.Y(), col.Z());
    glBindTexture(GL_TEXTURE_2D, m->getTexture());

    glPushMatrix();
    
    glTranslatef(m->getPosition().X(), m->getPosition().Y(), m->getPosition().Z());
    //cout << "Position: " << m->getPosition().X() << ", " << m->getPosition().Y() << ", " << m->getPosition().Z() << endl;
    glRotatef(m->getRotation(), 0.0, 1.0, 0.0);
    //cout << "offset X: " << m->getOffset().X() << endl;
    applyQuat(m);
    float scale = m->getScale();
    glScalef(scale, scale, scale);
    glTranslatef(m->getOffset().X(), m->getOffset().Y(), m->getOffset().Z());
    //cout << "Offset: " << m->getOffset().X() << ", " << m->getOffset().Y() << ", " << m->getOffset().Z() << endl;
    
    for(unsigned int i = 0; i < m->getFaces().size(); ++i) {
        face currFace = m->getFaces().at(i);
        
        //draw the face
        glBegin(GL_POLYGON);
        //glBegin(GL_LINE_LOOP);
        
        for(unsigned int j = 0; j < currFace.size(); ++j) {
            //Extract the current vertex from the vertex array based on the current point in the face
            //cout << "#vs: " << m->getVertices().size() << "  j: " << j << "  index: " << currFace.vAt(j) << endl;
            
            f3dPt currNorm = m->getNormals().at(currFace.nAt(j));
            glNormal3f(currNorm.X(), currNorm.Y(), currNorm.Z());

            if(m->getTexVerts().size() > 0 && m->getTexture())
            {
                //cout << "i, j: " << i << ", " << j << endl;
                //if(currFace.tAt(j) > 0)
                {
                    f3dPt currTex = m->getTexVerts().at(currFace.tAt(j));
                    //cout << "\tx,y: " << currTex.X() << ", " << currTex.Y() << endl;
                    glTexCoord2f(currTex.X(), currTex.Y());
                }
            }


            f3dPt currVert = m->getVerts().at(currFace.vAt(j));
            //cout << "Vertex: (" << currVert.X() << ", " << currVert.Y() << ", " << currVert.Z() << ")\n";
            glVertex3f(currVert.X(), currVert.Y(), currVert.Z());
        }
        
        glEnd();
    }
    
    glPopMatrix();
}

void game_render::applyQuat(game_model * m) {
    float * q = m->getQuat();
    btTransform transform;
    transform.setIdentity();
    btQuaternion rot(q[0], q[1], q[2], q[3]);
    transform.setRotation(rot);
//    f3vec pos = m->getPosition();
//    transform.setOrigin(btVector3(pos.X(), pos.Y(), pos.Z()));

	float matx[16];
    transform.getOpenGLMatrix(matx);
	
	//Hack to get cubes to translate correctly.  Need to get the physics lined up with the render...
	glMultMatrixf(matx);
}
