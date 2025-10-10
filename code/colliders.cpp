#include "colliders.h"
#include <cmath>


/*
 * Generic function for collision response from contact plane
 */
void Collider::resolveCollision(Particle* p, const Collision& col, double kElastic, double kFriction) const
{
    float planeDisplacement = -col.normal.dot(col.position);
    float projectedDistance = col.normal.dot(p->pos) + planeDisplacement;
    Vec3 newPos = p->pos - (1 + kElastic) * projectedDistance * col.normal;

    Vec3 vN = -kElastic * col.normal.dot(p->vel) * col.normal;
    Vec3 vT = (1 - kFriction) * p->vel - vN;

    p->pos = newPos;
    p->vel = vN + vT;
}



/*
 * Plane
 */
bool ColliderPlane::isInside(const Particle* p) const
{
    return this->planeN.dot(p->pos) + this->planeD <= 0 + p->radius;
}


bool ColliderPlane::testCollision(const Particle* p, Collision& colInfo) const
{
    double lambda = -(this->planeN.dot(p->prevPos) + this->planeD - p->radius) / this->planeN.dot(p->pos - p->prevPos);
    if (lambda >= 0 && lambda <= 1) {
        colInfo.position = p->prevPos + lambda * (p->pos - p->prevPos);
        colInfo.normal = this->planeN;
        return true;
    }
    return false;
}



/*
 * Sphere
 */
bool ColliderSphere::isInside(const Particle* p) const
{
    return (p->pos - this->center).norm() <= this->radius + p->radius;
}


bool ColliderSphere::testCollision(const Particle* p, Collision& colInfo) const
{
    Vec3 v = p->pos - p->prevPos;
    double a = v.dot(v);
    double b = 2 * v.dot(p->prevPos - this->center);
    double c = this->center.dot(this->center) + p->prevPos.dot(p->prevPos) - 2 * this->center.dot(p->prevPos) - (this->radius + p->radius) * (this->radius + p->radius);
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    double sqrtDisc = std::sqrt(discriminant);
    double lambda1 = (-b - sqrtDisc) / (2 * a);
    double lambda2 = (-b + sqrtDisc) / (2 * a);
    
    double lambda = (lambda1 >= 0 && lambda1 <= 1) ? lambda1 : ((lambda2 >= 0 && lambda2 <= 1) ? lambda2 : -1);
	colInfo.position = p->prevPos + lambda * v;
	colInfo.normal = (colInfo.position - this->center).normalized();
	return true;
}



/*
 * AABB
 */
bool ColliderAABB::isInside(const Particle* p) const
{
    return ((p->pos.array() > bmin.array()) && (p->pos.array() < bmax.array())).all();
}


bool ColliderAABB::testCollision(const Particle* particle, Collision& collisionInfo) const
{
    Vec3 displacement = particle->pos - particle->prevPos;

    double tEnter = 0.0;
    double tExit = 1.0;
    Vec3 normal = Vec3::Zero();

    for (int axis = 0; axis < 3; ++axis)
    {
        double velocityAlongAxis = displacement[axis];

        if (std::abs(velocityAlongAxis) < 1e-8)
        {
            if (particle->prevPos[axis] < bmin[axis] - particle->radius ||
                particle->prevPos[axis] > bmax[axis] + particle->radius)
            {
                return false;
            }
            continue;
        }

        double tMinAxis = (bmin[axis] - particle->prevPos[axis] - particle->radius) * 1 / velocityAlongAxis;
        double tMaxAxis = (bmax[axis] - particle->prevPos[axis] + particle->radius) * 1 / velocityAlongAxis;

        if (tMinAxis > tMaxAxis)
            std::swap(tMinAxis, tMaxAxis);

        if (tMinAxis > tEnter)
        {
            tEnter = tMinAxis;
            normal = Vec3::Zero();
            normal[axis] = (velocityAlongAxis > 0.0) ? -1.0 : 1.0;
        }

        if (tMaxAxis < tExit)
            tExit = tMaxAxis;

        if (tEnter > tExit)
            return false;
    }

    if (tEnter >= 0.0 && tEnter <= 1.0)
    {
        collisionInfo.position = particle->prevPos + tEnter * displacement;
        collisionInfo.normal = normal;
        return true;
    }

    return false;
}
