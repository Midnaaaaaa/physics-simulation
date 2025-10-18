#include "forces.h"
#include <cmath>
#include "particlesystem.h"
#include <QDebug>


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

void ForceSPH::apply() {
    std::vector<double> densities(system->getNumParticles(), 0.0);
    std::vector<double> pressures(system->getNumParticles(), 0.0);
    std::vector<std::vector<std::pair<Particle*, double>>> neighborsList(system->getNumParticles());

    double pressureMultiplier = 200;
    double restDensity = 0.1;

    system->buildSpatialHash(radius);

    for (Particle* p : system->getParticles()) {
        std::vector<std::pair<Particle*, double>> neighbors;
        system->getNeighbors(p, radius, neighbors);
        double density = p->mass * smoothingKernel(0, radius);
        for (std::pair<Particle*, double> q : neighbors) {
            density += q.first->mass * smoothingKernel(q.second, radius);
        }

        neighborsList[p->id] = neighbors;
        densities[p->id] = density;
    }

    for (Particle* p : system->getParticles()) {
        pressures[p->id] = std::max(0.0, pressureMultiplier * (densities[p->id] - restDensity));
    }

    //Compute pressions gradients
    for (Particle* p : system->getParticles()) {
        std::vector<std::pair<Particle*, double>> neighbors = neighborsList[p->id];
        Vec3 forcePressure = Vec3(0, 0, 0);
        for (std::pair<Particle*, double> q : neighbors) {
            //forcePressure += -q.first->mass * ((pressures[p->id] / (densities[p->id] * densities[p->id])) + (pressures[q.first->id] / (densities[q.first->id] * densities[q.first->id]))) * spikyKernelGradient(p->pos - q.first->pos, q.second, radius);
            forcePressure += -q.first->mass * (pressures[p->id] + pressures[q.first->id]) / (2 * densities[q.first->id]) * spikyKernelGradient(p->pos - q.first->pos, q.second, radius);
        }

        p->force += forcePressure / densities[p->id];

        p->color = Vec3((densities[p->id] / (restDensity)), 0, 1 - (densities[p->id] / (restDensity)));
    }

    double avgDensity = 0.0;
    int count = system->getNumParticles();

    for (double d : densities)
        avgDensity += d;

    avgDensity /= count;

    qDebug() << "Average density:" << avgDensity;


}



double ForceSPH::smoothingKernel(double r, double h) {
    double q = h * h - r * r;
    return (315.0 / (64.0 * M_PI * pow(h, 9))) * q * q * q;
}

Vec3 ForceSPH::spikyKernelGradient(Vec3 ij, double dist, double h) {
    double coef = -45.0 / (M_PI * pow(h, 6));
    double factor = (h - dist) * (h - dist);
    return ij * (coef * factor / dist);  // Normalized direction
}

double ForceSPH::viscosityKernelLaplacian(double r, double h) {
    return (45.0 / (M_PI * pow(h, 6))) * (h - r);
}
