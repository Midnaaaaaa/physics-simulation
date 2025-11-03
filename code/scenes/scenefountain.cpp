#include "scenefountain.h"
#include "glutils.h"
#include "model.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QColor>


SceneFountain::SceneFountain() {
    widget = new WidgetFountain();
    connect(widget, SIGNAL(updatedParameters()), this, SLOT(updateSimParams()));
}


SceneFountain::~SceneFountain() {
    if (widget)     delete widget;
    if (shader)     delete shader;
    if (vaoFloor)   delete vaoFloor;
    if (vaoSphereH) delete vaoSphereH;
    if (vaoSphereL) delete vaoSphereL;
    if (vaoCube)    delete vaoCube;
    if (fGravity)   delete fGravity;
    for (ColliderSphere* collider : particleColliders) {
        delete collider;
    }
    

}


void SceneFountain::initialize() {
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

    // create sphere VAO
    Model sphere = Model::createIcosphere(3);
    vaoSphereH = glutils::createVAO(shader, &sphere, buffers);
    numFacesSphereH = sphere.numFaces();
    glutils::checkGLError();

    // create box VAO
    Model cube = Model::createCube();
    vaoCube = glutils::createVAO(shader, &cube, buffers);
    glutils::checkGLError();

    // create forces
    fGravity = new ForceConstAcceleration();
    system.addForce(fGravity);

    // scene description
    fountainPos = Vec3(0, 80, 0);    
    colliderSphere.setCenter(Vec3(0,100,0));
    colliderSphere.setRadius(20);
    colliderBox.setFromBounds(Vec3(30,0,20), Vec3(50,10,60));
    
    colliderPlane.setPlane(Vec3(0, 1, 0), -0.5);
    
    boardBoxes.clear();
    boardCollisions.clear();
    boardColors.clear();
    boardBaseHues.clear();
    
    int gridSize = 20;
    double boxWidth = 10.0;
    double boxDepth = 10.0;
    double boxHeight = 25.0;
    double spacing = boxWidth;
    double totalWidth = gridSize * spacing;
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            double x = (i * spacing) - (totalWidth / 2.0) + (boxWidth / 2.0);
            double z = (j * spacing) - (totalWidth / 2.0) + (boxDepth / 2.0);
            double y = boxHeight;
            
            Vec3 center(x, y, z);
            Vec3 size(boxWidth, boxHeight, boxDepth);
            
            ColliderAABB box;
            box.setFromCenterSize(center, size);
            
            boardBoxes.push_back(box);
            boardCollisions.push_back(0);
            boardColors.push_back(Vec3(0.0, 0.0, 0.0));
            boardBaseHues.push_back(0.0);
        }
    }
}


void SceneFountain::reset()
{
    // update values from UI
    updateSimParams();

    // reset random seed
    Random::seed(1337);

    // erase all particles
    fGravity->clearInfluencedParticles();
    system.deleteParticles();
    deadParticles.clear();
    
    
    planeCollisions = 0;
    planeColor = Vec3(0.0, 0.0, 0.0);
    
    for (size_t i = 0; i < boardCollisions.size(); i++) {
        boardCollisions[i] = 0;
        
        Vec3 boxCenter = boardBoxes[i].getCenter();
        Vec3 fountainPosXZ = Vec3(fountainPos[0], 0, fountainPos[2]);
        Vec3 boxCenterXZ = Vec3(boxCenter[0], 0, boxCenter[2]);
        double distance = (boxCenterXZ - fountainPosXZ).norm();
        
        double maxDistance = 150.0;
        
        double t = std::min(1.0, distance / maxDistance);
        
        boardBaseHues[i] = 240.0 - (t * 240.0);
        boardColors[i] = Vec3(0.0, 0.0, 0.0);
    }

    particleColliders.clear();

}


void SceneFountain::updateSimParams()
{
    // get gravity from UI and update force
    double g = widget->getGravity();
    fGravity->setAcceleration(Vec3(0, -g, 0));

    // get other relevant UI values and update simulation params
    kBounce = widget->getKElastic() + 0.001;
    kFriction = widget->getKFriction();
    maxParticleLife = widget->getParticleLife();
    emitRate = widget->getParticleEmitRate();

    particleCollisionsEnabled = widget->getParticleCollisions();

}


void SceneFountain::paint(const Camera& camera) {

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

    QMatrix4x4 modelMat;
    
    vaoFloor->bind();
    modelMat = QMatrix4x4();
    modelMat.translate(0, -0.5, 0);
    modelMat.scale(200, 1, 200);
    shader->setUniformValue("ModelMatrix", modelMat);
    shader->setUniformValue("matdiff", GLfloat(planeColor[0]), GLfloat(planeColor[1]), GLfloat(planeColor[2]));
    shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
    shader->setUniformValue("matshin", 0.0f);
    glFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

    // draw sphere
    vaoSphereH->bind();
    Vec3 cc = colliderSphere.getCenter();
    modelMat = QMatrix4x4();
    modelMat.translate(cc[0], cc[1], cc[2]);
    modelMat.scale(colliderSphere.getRadius());
    shader->setUniformValue("ModelMatrix", modelMat);
    shader->setUniformValue("matdiff", GLfloat(0.3), GLfloat(0.7), GLfloat(0.1));
    shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
    shader->setUniformValue("matshin", 0.0f);
    glFuncs->glDrawElements(GL_TRIANGLES, 3*numFacesSphereH, GL_UNSIGNED_INT, 0);

    vaoCube->bind();
    cc = colliderBox.getCenter();
    Vec3 hs = 0.5*colliderBox.getSize();
    modelMat = QMatrix4x4();
    
    for (size_t i = 0; i < boardBoxes.size(); i++) {
        cc = boardBoxes[i].getCenter();
        hs = 0.5*boardBoxes[i].getSize();
        modelMat = QMatrix4x4();
        modelMat.translate(cc[0], cc[1], cc[2]);
        modelMat.scale(hs[0], hs[1], hs[2]);
        shader->setUniformValue("ModelMatrix", modelMat);
        shader->setUniformValue("matdiff", GLfloat(boardColors[i][0]), GLfloat(boardColors[i][1]), GLfloat(boardColors[i][2]));
        shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
        shader->setUniformValue("matshin", 0.0f);
        glFuncs->glDrawElements(GL_TRIANGLES, 3*2*6, GL_UNSIGNED_INT, 0);
    }
    
    vaoCube->release();
    shader->release();
}


void SceneFountain::update(double dt) {

    // emit new particles, reuse dead ones if possible
    int emitParticles = std::max(1, int(std::round(emitRate * dt)));
    for (int i = 0; i < emitParticles; i++) {
        Particle* p;
        ColliderSphere* pc;
        if (!deadParticles.empty()) {
            // reuse one dead particle
            p = deadParticles.front();
            deadParticles.pop_front();

            pc = particleColliders[p->id];
        }
        else {
            // create new particle
            p = new Particle();
            p->id = system.getNumParticles();
            system.addParticle(p);

            // don't forget to add particle to forces that affect it
            fGravity->addInfluencedParticle(p);

            pc = new ColliderSphere();
            particleColliders.push_back(pc);
        }

        p->color = Vec3(153/255.0, 217/255.0, 234/255.0);
        p->radius = 1.0;
        p->life = maxParticleLife;

        double x = Random::get(-20.0, 20.0);
        double y = 0;
        double z = Random::get(-20.0, 20.0);
        p->pos = Vec3(x, y, z) + fountainPos;

		double xVel = Random::get(-10.0, 10.0);
		double zVel = Random::get(-10.0, 10.0);
        p->vel = Vec3(xVel,20,zVel);
    }

    // integration step
    Vecd ppos = system.getPositions();
    integrator.step(system, dt);
    system.setPreviousPositions(ppos);

    // collisions
    Collision colInfo;
    for (Particle* p : system.getParticles()) {
        // Colisión con el plano grande
        if (colliderPlane.testCollision(p, colInfo)) {
            colliderPlane.resolveCollision(p, colInfo, kBounce, kFriction);
            planeCollisions++;
            // De negro (0,0,0) a blanco (1,1,1)
            double intensity = std::min(1.0, planeCollisions / 10000.0);
            planeColor = Vec3(intensity, intensity, intensity);
        }
        
        if(colliderSphere.testCollision(p, colInfo)) {
            colliderSphere.resolveCollision(p, colInfo, kBounce, kFriction);
		}

		for (size_t i = 0; i < boardBoxes.size(); i++) {
		    if (boardBoxes[i].testCollision(p, colInfo)) {
		        boardBoxes[i].resolveCollision(p, colInfo, kBounce, kFriction);
		        boardCollisions[i]++;
		        boardColors[i] = getHeatmapColor(boardCollisions[i], boardBaseHues[i]);
		    }
		}
    }

    if (particleCollisionsEnabled)
    {
        system.buildSpatialHash(2);

        for (Particle* p : system.getParticles()) {
            particleColliders[p->id]->setCenter(p->pos);
        }

        // Check collisions between particles
        for (Particle* p : system.getParticles()) {
            std::unordered_map<Particle*, double> neighbors;
            system.getNeighbors(p, 2.0, neighbors);
            for (auto& neighbor : neighbors) {
				Particle* p1 = neighbor.first;
                if (p->id < p1->id) {
                    Collision colInfo;
                    if (particleColliders[p->id]->testCollision(p1, colInfo)) {
                        particleColliders[p->id]->resolveCollision(p1, colInfo, kBounce, kFriction);
                        colInfo.normal = -colInfo.normal;
                        particleColliders[p1->id]->resolveCollision(p, colInfo, kBounce, kFriction);

                        particleColliders[p->id]->setCenter(p->pos);
                        particleColliders[p1->id]->setCenter(p1->pos);
                    }
                }
            }
        }
    }

    // check dead particles
    for (Particle* p : system.getParticles()) {
        if (p->life > 0) {
            p->life -= dt;
            if (p->life < 0) {
                deadParticles.push_back(p);
            }
        }
    }
}


void SceneFountain::mousePressed(const QMouseEvent* e, const Camera&)
{
    mouseX = e->pos().x();
    mouseY = e->pos().y();
}

void SceneFountain::mouseMoved(const QMouseEvent* e, const Camera& cam)
{
    int dx = e->pos().x() - mouseX;
    int dy = e->pos().y() - mouseY;
    mouseX = e->pos().x();
    mouseY = e->pos().y();

    Vec3 disp = cam.worldSpaceDisplacement(dx, -dy, cam.getEyeDistance());

    // example
    if (e->buttons() & Qt::RightButton) {
        if (!e->modifiers()) {
            // move fountain
            fountainPos += disp;
        }
        else if (e->modifiers() & Qt::ShiftModifier){
            // move sphere
            colliderSphere.setCenter(colliderSphere.getCenter() + disp);
        }
    }
}

Vec3 SceneFountain::getHeatmapColor(int collisionCount, double baseHue, int maxCollisions)
{
    double t = std::min(1.0, double(collisionCount) / double(maxCollisions));
    
    double hue = baseHue;
    double saturation = 1.0;
    double value = t;    

	QColor color = QColor::fromHsvF(hue / 360.0, saturation, value);
    return Vec3(color.redF(), color.greenF(), color.blueF());
}
