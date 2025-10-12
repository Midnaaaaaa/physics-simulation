#include "particlesystem.h"

Vecd ParticleSystem::getState() const {
    Vecd state(this->getStateSize());
    for (unsigned int i = 0; i < particles.size(); i++) {
        state[Particle::PhaseDimension*i    ] = particles[i]->pos[0];
        state[Particle::PhaseDimension*i + 1] = particles[i]->pos[1];
        state[Particle::PhaseDimension*i + 2] = particles[i]->pos[2];
        state[Particle::PhaseDimension*i + 3] = particles[i]->vel[0];
        state[Particle::PhaseDimension*i + 4] = particles[i]->vel[1];
        state[Particle::PhaseDimension*i + 5] = particles[i]->vel[2];
    }
    return state;
}

Vecd ParticleSystem::getDerivative() const {
    Vecd deriv(this->getStateSize());
    for (unsigned int i = 0; i < particles.size(); i++) {
        deriv[Particle::PhaseDimension*i    ] = particles[i]->vel[0];
        deriv[Particle::PhaseDimension*i + 1] = particles[i]->vel[1];
        deriv[Particle::PhaseDimension*i + 2] = particles[i]->vel[2];
        deriv[Particle::PhaseDimension*i + 3] = particles[i]->force[0]/particles[i]->mass;
        deriv[Particle::PhaseDimension*i + 4] = particles[i]->force[1]/particles[i]->mass;
        deriv[Particle::PhaseDimension*i + 5] = particles[i]->force[2]/particles[i]->mass;
    }
    return deriv;
}

Vecd ParticleSystem::getSecondDerivative() const {
    Vecd deriv(this->getStateSize());
    for (unsigned int i = 0; i < particles.size(); i++) {
        deriv[Particle::PhaseDimension*i + 0] = particles[i]->force[0]/particles[i]->mass;
        deriv[Particle::PhaseDimension*i + 1] = particles[i]->force[1]/particles[i]->mass;
        deriv[Particle::PhaseDimension*i + 2] = particles[i]->force[2]/particles[i]->mass;
        deriv[Particle::PhaseDimension*i + 3] = 0;
        deriv[Particle::PhaseDimension*i + 4] = 0;
        deriv[Particle::PhaseDimension*i + 5] = 0;
    }
    return deriv;
}

void ParticleSystem::setState(const Vecd& state) {
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->pos[0]  = state[Particle::PhaseDimension*i    ];
        particles[i]->pos[1]  = state[Particle::PhaseDimension*i + 1];
        particles[i]->pos[2]  = state[Particle::PhaseDimension*i + 2];
        particles[i]->vel[0]  = state[Particle::PhaseDimension*i + 3];
        particles[i]->vel[1]  = state[Particle::PhaseDimension*i + 4];
        particles[i]->vel[2]  = state[Particle::PhaseDimension*i + 5];
    }
}

void ParticleSystem::updateForces() {
    // clear force accumulators
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->force = Vec3(0.0, 0.0, 0.0);
    }
    // apply forces
    for (unsigned int i = 0; i < forces.size(); i++) {
        forces[i]->apply();
    }
}

Vecd ParticleSystem::getPositions() const {
    Vecd res(3*this->getNumParticles());
    for (unsigned int i = 0; i < particles.size(); i++) {
        res[3*i  ] = particles[i]->pos[0];
        res[3*i+1] = particles[i]->pos[1];
        res[3*i+2] = particles[i]->pos[2];
    }
    return res;
}

Vecd ParticleSystem::getVelocities() const {
    Vecd res(3*this->getNumParticles());
    for (unsigned int i = 0; i < particles.size(); i++) {
        res[3*i  ] = particles[i]->vel[0];
        res[3*i+1] = particles[i]->vel[1];
        res[3*i+2] = particles[i]->vel[2];
    }
    return res;
}

Vecd ParticleSystem::getAccelerations() const {
    Vecd res(3*this->getNumParticles());
    for (unsigned int i = 0; i < particles.size(); i++) {
        res[3*i  ] = particles[i]->force[0]/particles[i]->mass;
        res[3*i+1] = particles[i]->force[1]/particles[i]->mass;
        res[3*i+2] = particles[i]->force[2]/particles[i]->mass;
    }
    return res;
}

Vecd ParticleSystem::getPreviousPositions() const {
    Vecd res(3*this->getNumParticles());
    for (unsigned int i = 0; i < particles.size(); i++) {
        res[3*i  ] = particles[i]->prevPos[0];
        res[3*i+1] = particles[i]->prevPos[1];
        res[3*i+2] = particles[i]->prevPos[2];
    }
    return res;
}

void ParticleSystem::setPositions(const Vecd& pos) {
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->pos[0] = pos[3*i    ];
        particles[i]->pos[1] = pos[3*i + 1];
        particles[i]->pos[2] = pos[3*i + 2];
    }
}

void ParticleSystem::setVelocities(const Vecd& vel) {
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->vel[0] = vel[3*i    ];
        particles[i]->vel[1] = vel[3*i + 1];
        particles[i]->vel[2] = vel[3*i + 2];
    }
}

void ParticleSystem::setPreviousPositions(const Vecd& ppos) {
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->prevPos[0] = ppos[3*i    ];
        particles[i]->prevPos[1] = ppos[3*i + 1];
        particles[i]->prevPos[2] = ppos[3*i + 2];
    }
}


void ParticleSystem::clearSpatialHash() {
	hashTable.clear();
    particleEntries.clear();
	spacing = 1.0;
    if (particles.size() > 0) {
        spacing = (particles[0]->radius) * 2.0;
        tableSize = particles.size() * 2;
    }
}

void ParticleSystem::buildSpatialHash(double cellSize) {
	clearSpatialHash();

	hashTable.resize(tableSize + 1, 0);
	particleEntries.resize(particles.size(), 0);

    for(Particle* p : particles) {
        int key = computeHashKey(p->pos);
        hashTable[key]++;
	}

	//Partial sum to get starting indices
    for(int i = 0; i < hashTable.size(); i++) {
        hashTable[i + 1] += hashTable[i];
	}

    for(Particle* p : particles) {
        int index = computeHashKey(p->pos);
        int particleEntriesIndex = hashTable[index]--;
        particleEntries[particleEntriesIndex] = p->id;
	}

}

int ParticleSystem::computeGridCell(const double axisPos) {
    return int(floor(axisPos / spacing));
}

int ParticleSystem::computeHashKey(const Vec3& position) {

    int xi = computeGridCell(position[0]);
    int yi = computeGridCell(position[1]);
    int zi = computeGridCell(position[2]);

	double h = (xi * 92837111) ^ (yi * 689287499) ^ (zi * 283923481);
    return abs(int(h)) % tableSize;
}
std::unordered_set<Particle*> ParticleSystem::getNeighbors(Particle* p, double radius) {
    std::unordered_set<Particle*> neighbors;
	int xi = computeGridCell(p->pos[0] - radius);
	int yi = computeGridCell(p->pos[1] - radius);
	int zi = computeGridCell(p->pos[2] - radius);

	int x1 = computeGridCell(p->pos[0] + radius);
	int y1 = computeGridCell(p->pos[1] + radius);
    int z1 = computeGridCell(p->pos[2] + radius);
    for(int x = xi; x <= x1; x++) {
        for(int y = yi; y <= y1; y++) {
            for(int z = zi; z <= z1; z++) {
                int key = computeHashKey(Vec3(x, y, z));
                int startIndex = hashTable[key];
                int endIndex = hashTable[key + 1];

                for(int i = startIndex; i < endIndex; i++) {
                    Particle* np = particles[particleEntries[i]];
                    if(np->id != p->id) {
                        Vec3 diff = np->pos - p->pos;
                        if(diff.squaredNorm() <= radius * radius) {
							neighbors.insert(np);
                        }
                    }
                }
            }
        }
    }
	return neighbors;
}