#include "scenefluid.h"
#include "glutils.h"
#include "model.h"
#include <QOpenGLFunctions_3_3_Core>


SceneFluid::SceneFluid() {
    widget = new WidgetFluid();
    connect(widget, SIGNAL(updatedParameters()), this, SLOT(updateSimParams()));
}


SceneFluid::~SceneFluid() {
    if (widget)     delete widget;
    if (shader)     delete shader;
    if (vaoFloor)   delete vaoFloor;
    if (vaoSphereH) delete vaoSphereH;
    if (vaoSphereL) delete vaoSphereL;
    if (vaoCube)    delete vaoCube;
    if (fGravity)   delete fGravity;
    if (fGravitational) delete fGravitational;
    if (attractorParticle) delete attractorParticle;
}


void SceneFluid::initialize() {
    // load shader
    shader = glutils::loadShaderProgram(":/shaders/phong.vert", ":/shaders/phong.frag");

    // create floor VAO
    Model quad = Model::createQuad();
    vaoFloor = glutils::createVAO(shader, &quad, buffers);
    glutils::checkGLError();

    // create particle VAOs
    Model sphereLowres = Model::createIcosphere(1);
    vaoSphereL = glutils::createVAO(shader, &sphereLowres, buffers);
    numFacesSphereL = sphereLowres.numFaces();
    glutils::checkGLError();

    // create forces
    fGravity = new ForceConstAcceleration();
    system.addForce(fGravity);

    fSPH = new ForceSPH();
    fSPH->setParticleSystem(&system);
    fSPH->setRadius(4);
    system.addForce(fSPH);

    fGravitational = new ForceGravitation();
    fGravitational->setConstant(100.0);
    system.addForce(fGravitational);

    // scene description
    fountainPos = Vec3(0, 80, 0);    
    colliderFloor.setPlane(Vec3(0, 1, 0), 0);    
	colliderWallLeft.setPlane(Vec3(1, 0, 0), -50);  // Expanded to -60
	colliderWallRight.setPlane(Vec3(-1, 0, 0), -50); // Expanded to -60
	colliderWallBack.setPlane(Vec3(0, 0, 1), -10);   // Expanded to -30
    colliderWallFront.setPlane(Vec3(0, 0, -1), -10); // Expanded to -30
}


void SceneFluid::reset()
{
    // update values from UI
    updateSimParams();

    // reset random seed
    Random::seed(1337);

    // erase all particles
    fGravity->clearInfluencedParticles();
	fSPH->clearInfluencedParticles();
    fGravitational->clearInfluencedParticles();
    system.deleteParticles();

    if (attractorParticle) {
        delete attractorParticle;
        attractorParticle = nullptr;
    }

    int particlesPerDim = 10;
    double spacing = 2.0;

    double cubeSize = (particlesPerDim - 1) * spacing;
    double startY = 1;

    double separation = 30;

    double startX1 = -separation - cubeSize / 2.0;
    double startZ1 = -cubeSize / 2.0;

    for (int i = 0; i < particlesPerDim; ++i) {
        for (int j = 0; j < particlesPerDim; ++j) {
            for (int k = 0; k < particlesPerDim; ++k) {
                Particle* p = new Particle();
                p->id = system.getNumParticles();
                system.addParticle(p);
                fGravity->addInfluencedParticle(p);
                fSPH->addInfluencedParticle(p);

                p->radius = 1.0;
                p->elasticity = 0.3;
                p->friction = 0.1;

                double x = startX1 + i * spacing;
                double y = startY + j * spacing;
                double z = startZ1 + k * spacing;
                p->pos = Vec3(x, y, z);
                p->vel = Vec3(0, 0, 0);
                p->color = Vec3(0.0, 0.0, 0.5);
                p->mass = 1;
            }
        }
    }

    double startX2 = separation - cubeSize / 2.0;
    double startZ2 = -cubeSize / 2.0;

    for (int i = 0; i < particlesPerDim; ++i) {
        for (int j = 0; j < particlesPerDim; ++j) {
            for (int k = 0; k < particlesPerDim; ++k) {
                Particle* p = new Particle();
                p->id = system.getNumParticles();
                system.addParticle(p);
                fGravity->addInfluencedParticle(p);
                fSPH->addInfluencedParticle(p);

                p->radius = 1.0;
                p->elasticity = 0.3;
                p->friction = 0.1;

                double x = startX2 + i * spacing;
                double y = startY + j * spacing;
                double z = startZ2 + k * spacing;
                p->pos = Vec3(x, y, z);
                p->vel = Vec3(0, 0, 0);
                p->color = Vec3(0.0, 0.0, 0.5);
                p->mass = 1;
            }
        }
    }
}


void SceneFluid::updateSimParams()
{
    // get gravity from UI and update force
    double g = widget->getGravity();
    fGravity->setAcceleration(Vec3(0, -g, 0));
}


void SceneFluid::paint(const Camera& camera) {

    QOpenGLFunctions* glFuncs = nullptr;
    glFuncs = QOpenGLContext::currentContext()->functions();

    shader->bind();

    // camera matrices
    QMatrix4x4 camProj = camera.getPerspectiveMatrix();
    QMatrix4x4 camView = camera.getViewMatrix();
    shader->setUniformValue("ProjMatrix", camProj);
    shader->setUniformValue("ViewMatrix", camView);

    // lighting
    const int numLights = 1;
    const QVector3D lightPosWorld[numLights] = {QVector3D(100,500,100)};
    const QVector3D lightColor[numLights] = {QVector3D(1,1,1)};
    QVector3D lightPosCam[numLights];
    for (int i = 0; i < numLights; i++) {
        lightPosCam[i] = camView.map(lightPosWorld[i]);  // map = matrix * vector
    }
    shader->setUniformValue("numLights", numLights);
    shader->setUniformValueArray("lightPos", lightPosCam, numLights);
    shader->setUniformValueArray("lightColor", lightColor, numLights);

    // draw floor
    vaoFloor->bind();
    QMatrix4x4 modelMat;
    modelMat.scale(50, 1, 50);
    shader->setUniformValue("ModelMatrix", modelMat);
    shader->setUniformValue("matdiff", 0.8f, 0.8f, 0.8f);
    shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
    shader->setUniformValue("matshin", 0.0f);
    glFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // draw left wall
	//modelMat = QMatrix4x4();
	//modelMat.translate(-50, 50, 0);
	//modelMat.rotate(90, 0, 0, 1);
	//modelMat.scale(50, 1, 50);
	//shader->setUniformValue("ModelMatrix", modelMat);
	//shader->setUniformValue("matdiff", 0.8f, 0.8f, 0.8f);
	//shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
	//shader->setUniformValue("matshin", 0.0f);
	//glFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//// draw right wall
	//modelMat = QMatrix4x4();
	//modelMat.translate(50, 50, 0);
	//modelMat.rotate(-90, 0, 0, 1);
	//modelMat.scale(50, 1, 50);
	//shader->setUniformValue("ModelMatrix", modelMat);
	//shader->setUniformValue("matdiff", 0.8f, 0.8f, 0.8f);
	//shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
	//shader->setUniformValue("matshin", 0.0f);
	//glFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//// draw back wall
	//modelMat = QMatrix4x4();
	//modelMat.translate(0, 50, -50);
	//modelMat.rotate(90, 1, 0, 0);
	//modelMat.scale(50, 1, 50);
	//shader->setUniformValue("ModelMatrix", modelMat);
	//shader->setUniformValue("matdiff", 0.8f, 0.8f, 0.8f);
	//shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
	//shader->setUniformValue("matshin", 0.0f);
	//glFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//// draw front wall
	//modelMat = QMatrix4x4();
	//modelMat.translate(0, 50, 50);
	//modelMat.rotate(-90, 1, 0, 0);
	//modelMat.scale(50, 1, 50);
	//shader->setUniformValue("ModelMatrix", modelMat);
	//shader->setUniformValue("matdiff", 0.8f, 0.8f, 0.8f);
	//shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
	//shader->setUniformValue("matshin", 0.0f);
	//glFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // draw the particles
    vaoSphereL->bind();
    for (const Particle* particle : system.getParticles()) {
        Vec3   p = particle->pos;
        Vec3   c = particle->color;
        double r = particle->radius;

        modelMat = QMatrix4x4();
        modelMat.translate(p[0], p[1], p[2]);
        modelMat.scale(r);
        shader->setUniformValue("ModelMatrix", modelMat);

        shader->setUniformValue("matdiff", GLfloat(c[0]), GLfloat(c[1]), GLfloat(c[2]));
        shader->setUniformValue("matspec", 1.0f, 1.0f, 1.0f);
        shader->setUniformValue("matshin", 100.f);

        glFuncs->glDrawElements(GL_TRIANGLES, 3*numFacesSphereL, GL_UNSIGNED_INT, 0);
    }

    // draw the attractor particle if it exists
    if (attractorParticle) {
        Vec3   p = attractorParticle->pos;
        Vec3   c = attractorParticle->color;
        double r = attractorParticle->radius;

        modelMat = QMatrix4x4();
        modelMat.translate(p[0], p[1], p[2]);
        modelMat.scale(r);
        shader->setUniformValue("ModelMatrix", modelMat);

        shader->setUniformValue("matdiff", GLfloat(c[0]), GLfloat(c[1]), GLfloat(c[2]));
        shader->setUniformValue("matspec", 1.0f, 1.0f, 1.0f);
        shader->setUniformValue("matshin", 100.f);

        glFuncs->glDrawElements(GL_TRIANGLES, 3*numFacesSphereL, GL_UNSIGNED_INT, 0);
    }
}


void SceneFluid::update(double dt) {
    // integration step
    Vecd ppos = system.getPositions();
    integrator.step(system, dt);
    system.setPreviousPositions(ppos);

    // collisions
    Collision colInfo;
    for (Particle* p : system.getParticles()) {
        if (colliderFloor.testCollision(p, colInfo)) {
            colliderFloor.resolveCollision(p, colInfo, p->elasticity, p->friction);
        }
        if (colliderWallBack.testCollision(p, colInfo)) {
            colliderWallBack.resolveCollision(p, colInfo, p->elasticity, p->friction);
        }
        if (colliderWallLeft.testCollision(p, colInfo)) {
            colliderWallLeft.resolveCollision(p, colInfo, p->elasticity, p->friction);
        }
        if (colliderWallFront.testCollision(p, colInfo)) {
            colliderWallFront.resolveCollision(p, colInfo, p->elasticity, p->friction);
        }
        if (colliderWallRight.testCollision(p, colInfo)) {
            colliderWallRight.resolveCollision(p, colInfo, p->elasticity, p->friction);
        }
    }
}

void SceneFluid::mousePressed(const QMouseEvent* e, const Camera& cam)
{
    mouseX = e->pos().x();
    mouseY = e->pos().y();
}

void SceneFluid::mouseMoved(const QMouseEvent* e, const Camera& cam)
{
    int dx = e->pos().x() - mouseX;
    int dy = e->pos().y() - mouseY;
    mouseX = e->pos().x();
    mouseY = e->pos().y();

    // Move the attractor particle with right button drag
    if (e->buttons() & Qt::RightButton) {
        if (!attractorParticle) {
			attractorParticle = new Particle();
			attractorParticle->pos = cam.getEye();
			attractorParticle->vel = Vec3(0, 0, 0);
			attractorParticle->mass = 100;
			attractorParticle->radius = 2.0;
			attractorParticle->color = Vec3(1.0, 1.0, 0.0);

			fGravitational->setAttractor(attractorParticle);

			for (Particle* p : system.getParticles()) {
				fGravitational->addInfluencedParticle(p);
			}
		}
        double d = -(attractorParticle->pos - cam.getPos()).dot(cam.zAxis());
        Vec3 disp = cam.worldSpaceDisplacement(dx, -dy, d);
        attractorParticle->pos += disp;
        
    }
    else {
        fGravitational->clearInfluencedParticles();
        fGravitational->setAttractor(nullptr);
        delete attractorParticle;
        attractorParticle = nullptr;
    }
}


