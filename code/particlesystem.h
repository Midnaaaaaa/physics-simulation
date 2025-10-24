#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include <unordered_set>
#include "defines.h"
#include "particle.h"

class Force;

class ParticleSystem
{
public:
    ParticleSystem() {}
    virtual ~ParticleSystem() {}

    // phase space
    virtual int  getStateSize()	        const;
    virtual Vecd getState()				const;
    virtual Vecd getDerivative()		const;
    virtual Vecd getSecondDerivative()	const;

    // sets phase space values (pos-vel)
    virtual void setState(const Vecd& state);

    // clear and recompute force accumulators per particle
    virtual void updateForces();

    // individual physical magnitudes getters and setters
    virtual Vecd getPositions()         const;
    virtual Vecd getVelocities()        const;
    virtual Vecd getAccelerations()     const;
    virtual Vecd getPreviousPositions() const;
    virtual void setPositions(const Vecd& pos);
    virtual void setVelocities(const Vecd& vel);
    virtual void setPreviousPositions(const Vecd& pos);

    // particles
    unsigned int getNumParticles() const;
    void addParticle(Particle* p);
    const Particle* getParticle(unsigned int i) const;
    Particle* getParticle(unsigned int i);
    const std::vector<Particle*>& getParticles() const;
    std::vector<Particle*>& getParticles();
    void clearParticles();  // clears vector but does not delete items
    void deleteParticles(); // deletes items and clears vector

    // forces
    void addForce(Force* f);
    unsigned int getNumForces() const;
    const Force* getForce(unsigned int i) const;
    Force* getForce(unsigned int i);
    void clearForces();     // clears vector but does not delete items
    void deleteForces();    // deletes items and clears vector

    // time
    double getTime() const;
    void setTime(double t);
    const double* getTimePointer() const;

	//Spatial Hashing
    void buildSpatialHash(double cellSize);
    void getNeighbors(Particle* p, double radius, std::unordered_map<Particle*, double>& neighbors);


private:
    int computeHashKeyFromCell(int xi, int yi, int zi);
    int computeHashKey(const Vec3& position);
	int computeGridCell(const double axisPos);

protected:
    std::vector<Particle*>	particles;
    std::vector<Force*>		forces;
    double time = 0;

	//Spatial Hashing
	int tableSize = 0;
	std::vector<int> hashTable;
    std::vector<int> particleEntries;
    double spacing = 1.0;
};


#endif // PARTICLESYSTEM_H
