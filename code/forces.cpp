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
    std::vector<std::unordered_map<Particle*, double>> neighborsList(system->getNumParticles());

    double pressureMultiplier = 200;
    double restDensity = 0.05;
    double mu = 0.1;

    system->buildSpatialHash(radius*3);

    for (Particle* p : system->getParticles()) {
        std::unordered_map<Particle*, double> neighbors;
        system->getNeighbors(p, radius, neighbors);
        double density = p->mass * smoothingKernel(0, radius);
        for (const auto& [q, dist] : neighbors) {
            density += q->mass * smoothingKernel(dist, radius);
        }

        neighborsList[p->id] = neighbors;
        densities[p->id] = density;
    }

    for (Particle* p : system->getParticles()) {
        pressures[p->id] = pressureMultiplier * (densities[p->id] - restDensity);
    }

    //Compute pressions gradients
    for (Particle* p : system->getParticles()) {
        std::unordered_map<Particle*, double>& neighbors = neighborsList[p->id];
        Vec3 forcePressure = Vec3(0, 0, 0);
        Vec3 forceViscosity = Vec3(0, 0, 0);
        for (const auto& [q, dist] : neighbors) {
            double P_ij = -q->mass * ((pressures[p->id] / (densities[p->id] * densities[p->id])) + pressures[q->id] / (densities[q->id] * densities[q->id]));

            forcePressure += P_ij * spikyKernelGradient(p->pos - q->pos, dist, radius);
            
            Vec3 v_ij = mu * q->mass * (q->vel - p->vel) / (densities[q->id] * densities[p->id]);
            
            forceViscosity += v_ij * viscosityKernelLaplacian(dist, radius);
        }

        p->force += forcePressure + forceViscosity;

        p->color = Vec3(1-(densities[p->id] / (restDensity)), 0, (densities[p->id] / (restDensity)));
    }

    double avgDensity = 0.0;
    int count = system->getNumParticles();

    for (double d : densities)
        avgDensity += d;

    avgDensity /= count;

    //qDebug() << "Average density:" << avgDensity;


}



double ForceSPH::smoothingKernel(double r, double h) {
    double q = h * h - r * r;
    return smoothingKernelConstant * (q * q * q);
}

Vec3 ForceSPH::spikyKernelGradient(Vec3 ij, double dist, double h) {
    double coef = -45.0 / (M_PI * pow(h, 6));
    double factor = (h - dist) * (h - dist);
    return ij * (spikyKernelConstant * factor / dist);  // Normalized direction
}

double ForceSPH::viscosityKernelLaplacian(double r, double h) {
    return viscosityKernelConstant * (h - r);
}
