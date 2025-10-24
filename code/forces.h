#ifndef FORCES_H
#define FORCES_H

#include <vector>
#include "particle.h"

class ParticleSystem;

class Force
{
public:
    Force(void) {}
    virtual ~Force(void) {}

    virtual void apply() = 0;

    void addInfluencedParticle(Particle* p) {
        particles.push_back(p);
    }

    void setInfluencedParticles(const std::vector<Particle*>& vparticles) {
        particles = vparticles;
    }

    void clearInfluencedParticles() {
        particles.clear();
    }

    std::vector<Particle*> getInfluencedParticles() const {
        return particles;
    }

protected:
    std::vector<Particle*>	particles;
};


class ForceConstAcceleration : public Force
{
public:
    ForceConstAcceleration() { acceleration = Vec3(0,0,0); }
    ForceConstAcceleration(const Vec3& a) { acceleration = a; }
    virtual ~ForceConstAcceleration() {}

    virtual void apply();

    void setAcceleration(const Vec3& a) { acceleration = a; }
    Vec3 getAcceleration() const { return acceleration; }

protected:
    Vec3 acceleration;
};


class ForceDrag : public Force
{
public:
    ForceDrag() { klinear = kquadratic = 0; }
    ForceDrag(double k1, double k2) { klinear = k1; kquadratic = k2; }
    virtual ~ForceDrag() {}

    virtual void apply();

    void setDragCoefficients(double k1, double k2) { klinear = k1, kquadratic = k2; }
    double getLinearCoefficient() const { return klinear; }
    double getQuadraticCoefficient() const { return kquadratic; }

protected:
    double klinear, kquadratic;
};


class ForceSpring : public Force
{
public:
    ForceSpring() { ks = kd = 0; }
    ForceSpring(Particle* p1, Particle* p2, double L, double ks, double kd) {
        this->L = L; this->ks = ks; this->kd = kd;
        particles.push_back(p1);
        particles.push_back(p2);
    }
    virtual ~ForceSpring() {}

    virtual void apply();

    void setParticlePair(Particle* p1, Particle* p2) {
        particles.clear();
        particles.push_back(p1);
        particles.push_back(p2);
    }
    Particle* getParticle1() const { return particles[0]; }
    Particle* getParticle2() const { return particles[1]; }

    void setRestLength(double l) { L = l; }
    double getRestLength() const { return L; }

    void setSpringConstant(double k) { ks = k; }
    double getSpringConstant() const { return ks; }

    void setDampingCoeff(double k) { kd = k; }
    double getDampingCoeff() const { return kd; }

protected:
    double L = 0;   // resting length
    double ks = 0;  // spring coeff
    double kd = 0;  // damping coeff
};

class ForceGravitation : public Force
{
public:
    ForceGravitation() { attractor=nullptr; }
    ForceGravitation(const Particle* p, double k) { attractor = p, G = k; }
    virtual ~ForceGravitation() {}

    virtual void apply();

    void setAttractor(const Particle* p) { attractor = p; }
    const Particle* getAttractor() const { return attractor; }
    void setConstant(double k) { G = k; }
    void setSmoothingFactors(double sa, double sb) { a = sa; b = sb; }
    double getConstant() const { return G; }

protected:
    const Particle* attractor;
    double G = 6.6743e-11; // gravitational constant
    double a = 1, b = 1;
};

class ForceSPH : public Force
{
public:
    ForceSPH() { radius = 3; system = nullptr; smoothingKernelConstant = (315.0 / (64.0 * M_PI * pow(radius, 9))); spikyKernelConstant = -45.0 / (M_PI * pow(radius, 6)); viscosityKernelConstant = (45.0 / (M_PI * pow(radius, 6))); }
    ForceSPH(double radius) { this->radius = radius; system = nullptr; smoothingKernelConstant = (315.0 / (64.0 * M_PI * pow(radius, 9))); spikyKernelConstant = -45.0 / (M_PI * pow(radius, 6)); viscosityKernelConstant = (45.0 / (M_PI * pow(radius, 6)));}
    ForceSPH(ParticleSystem* ps) { system = ps; radius = 3; }
	ForceSPH(ParticleSystem* ps, double radius) { system = ps; this->radius = radius; }
    virtual ~ForceSPH() {}
    virtual void apply();
    void setParticleSystem(ParticleSystem* ps) { system = ps; }
    void setRadius(double r) { radius = r; smoothingKernelConstant = (315.0 / (64.0 * M_PI * pow(radius, 9))); spikyKernelConstant = -45.0 / (M_PI * pow(radius, 6)); viscosityKernelConstant = (45.0 / (M_PI * pow(radius, 6)));}
    double getRadius() const { return radius; }

private:
    double smoothingKernel(double r, double h);
    Vec3 spikyKernelGradient(Vec3 ij, double dist, double h);
    double viscosityKernelLaplacian(double r, double h);

protected:
    ParticleSystem* system;
    double radius;
    double smoothingKernelConstant;
    double spikyKernelConstant;
    double viscosityKernelConstant;
};



#endif // FORCES_H
