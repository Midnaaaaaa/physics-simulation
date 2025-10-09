#include "forces.h"
#include <cmath>

void ForceConstAcceleration::apply() {
    for (Particle* p : particles) {
        p->force += p->mass * this->getAcceleration();
    }
}

void ForceDrag::apply() {
    for (Particle* p : particles) {
        p->force += -this->klinear * p->vel;
    }

    for (Particle* p : particles) {
        p->force += -this->kquadratic * p->vel.norm() *  p->vel;
    }
}

void ForceSpring::apply() {
    if (particles.size() < 2) return;
    Particle* p1 = getParticle1();
    Particle* p2 = getParticle2();

    double d = (p2->pos - p1->pos).norm();
    Vec3 dir = (p2->pos - p1->pos) / d;

    Vec3 springForce = (this->ks * (d - this->L) + this->kd * (p2->vel - p1->vel).dot(dir)) * dir;
    p1->force += springForce;
    p2->force += -springForce;
}

void ForceGravitation::apply() {
    const Particle* p_i = this->getAttractor();

    for (Particle* p_j : getInfluencedParticles()){
        double m1 = p_i->mass;
        double m2 = p_j->mass;

        Vec3 p_ij = p_i->pos - p_j->pos;
        double d = p_ij.norm();
        double d2 = d * d;

        double smoothing_den = 1 + exp(-a * d2/(b*b));
        double smoothing = 2 / smoothing_den - 1;

        Vec3 force = ((this->G * m1 * m2) * (1 / d2) * smoothing) * (p_ij / d);

        p_j->force += force;
    }
}
