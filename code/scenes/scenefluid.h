#ifndef SCENEFLUID_H
#define SCENEFLUID_H

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <list>
#include "scene.h"
#include "widgetfluid.h"
#include "particlesystem.h"
#include "integrators.h"
#include "colliders.h"
#include "forces.h"


class SceneFluid : public Scene
{
    Q_OBJECT

public:
    SceneFluid();
    virtual ~SceneFluid();

    virtual void initialize();
    virtual void reset();
    virtual void update(double dt);
    virtual void paint(const Camera& cam);

    virtual void mousePressed(const QMouseEvent* e, const Camera& cam);
    virtual void mouseMoved(const QMouseEvent* e, const Camera& cam);


    virtual void getSceneBounds(Vec3& bmin, Vec3& bmax) {
        bmin = Vec3(-110, -10, -110);
        bmax = Vec3( 110, 100,  110);
    }
    virtual unsigned int getNumParticles() { return system.getNumParticles(); }

    virtual QWidget* sceneUI() { return widget; }

public slots:
    void updateSimParams();

protected:
    WidgetFluid* widget = nullptr;

    QOpenGLShaderProgram* shader = nullptr;
    QOpenGLVertexArrayObject* vaoSphereL = nullptr;
    QOpenGLVertexArrayObject* vaoSphereH = nullptr;
    QOpenGLVertexArrayObject* vaoCube    = nullptr;
    QOpenGLVertexArrayObject* vaoFloor   = nullptr;
    unsigned int numFacesSphereL = 0, numFacesSphereH = 0;

    IntegratorSymplecticEuler integrator;
    ParticleSystem system;
    ForceConstAcceleration* fGravity;
	ForceSPH* fSPH;
    ForceGravitation* fGravitational;

	ColliderPlane colliderFloor, colliderWallLeft, colliderWallRight, colliderWallBack, colliderWallFront;

    Vec3 fountainPos;
    int mouseX, mouseY;
	bool creatingParticles = false;
	int particlesPerFrame = 10;

    bool wallCollision = true;

    double kBounce, kFriction;
    
    Particle* attractorParticle = nullptr;
};

#endif // SCENEFLUID_H
