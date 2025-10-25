#ifndef SCENEFOUNTAIN_H
#define SCENEFOUNTAIN_H

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <list>
#include "scene.h"
#include "widgetfountain.h"
#include "particlesystem.h"
#include "integrators.h"
#include "colliders.h"
#include "forces.h"

class SceneFountain : public Scene
{
    Q_OBJECT

public:
    SceneFountain();
    virtual ~SceneFountain();

    virtual void initialize();
    virtual void reset();
    virtual void update(double dt);
    virtual void paint(const Camera& cam);

    virtual void mousePressed(const QMouseEvent* e, const Camera& cam);
    virtual void mouseMoved(const QMouseEvent* e, const Camera& cam);

    Vec3 getHeatmapColor(int collisionCount, double baseHue, int maxCollisions = 500);

    virtual void getSceneBounds(Vec3& bmin, Vec3& bmax) {
        bmin = Vec3(-110, -10, -110);
        bmax = Vec3( 110, 100,  110);
    }
    virtual unsigned int getNumParticles() { return system.getNumParticles(); }

    virtual QWidget* sceneUI() { return widget; }

public slots:
    void updateSimParams();

protected:
    WidgetFountain* widget = nullptr;

    QOpenGLShaderProgram* shader = nullptr;
    QOpenGLVertexArrayObject* vaoSphereL = nullptr;
    QOpenGLVertexArrayObject* vaoSphereH = nullptr;
    QOpenGLVertexArrayObject* vaoCube    = nullptr;
    QOpenGLVertexArrayObject* vaoFloor   = nullptr;
    unsigned int numFacesSphereL = 0, numFacesSphereH = 0;

    IntegratorEuler integrator;
    ParticleSystem system;
    std::list<Particle*> deadParticles;
    ForceConstAcceleration* fGravity;

    ColliderSphere colliderSphere;
    ColliderAABB   colliderBox;
    ColliderPlane colliderPlane;  // Plano grande debajo del tablero


    double kBounce, kFriction;
    double emitRate;
    double maxParticleLife;

    Vec3 fountainPos;
    int mouseX, mouseY;
    
    std::vector<ColliderAABB> boardBoxes;
    std::vector<int> boardCollisions;
    std::vector<Vec3> boardColors;
    std::vector<double> boardBaseHues;
    
    int planeCollisions = 0;
    Vec3 planeColor;
};

#endif // SCENEFOUNTAIN_H
