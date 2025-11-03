#include "integrators.h"


void IntegratorEuler::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    Vecd x0 = system.getState();
    Vecd dx = system.getDerivative();
    Vecd x1 = x0 + dt*dx;
    Vecd previousPositions = system.getPositions();

    system.setState(x1);
    system.setTime(t0+dt);
    system.setPreviousPositions(previousPositions);
    system.updateForces();
}


void IntegratorSymplecticEuler::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    Vecd previousPositions = system.getPositions();
    Vecd v1 = system.getVelocities() + dt * system.getAccelerations();
    system.setVelocities(v1);
    Vecd x1 = system.getPositions() + dt * v1;
    system.setPositions(x1);
    system.setTime(t0 + dt);
    system.setPreviousPositions(previousPositions);
    system.updateForces();
}

void IntegratorMidpoint::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    Vecd x0 = system.getState();
    Vecd dx = system.getDerivative();
    Vecd x1 = x0 + (dx / 2) * dt;
    Vecd previousPositions = system.getPositions();

    system.setPreviousPositions(previousPositions);

    system.setState(x1);
    system.setTime(t0 + dt/2);

    system.updateForces();
    Vecd midPoint_dx = system.getDerivative();
    Vecd xmid = x0 + dt * midPoint_dx;
    system.setState(xmid);
    system.setTime(t0 + dt);
    system.updateForces();
}

void IntegratorRK2::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    Vecd x0 = system.getState();
    Vecd k1 = system.getDerivative();
    Vecd previousPositions = system.getPositions();
    
    system.setTime(t0 + dt);
    
    Vecd x2 = x0 + dt * k1;
    system.setState(x2);
    system.updateForces();
    Vecd k2 = system.getDerivative();


    Vecd x_final = x0 + (dt / 2) * (k1 + k2);
    system.setState(x_final);
    system.setTime(t0 + dt);
    system.setPreviousPositions(previousPositions);
    system.updateForces();
}


void IntegratorRK4::step(ParticleSystem &system, double dt) {
	double t0 = system.getTime();
	Vecd x0 = system.getState();
	Vecd k1 = system.getDerivative();
	Vecd previousPositions = system.getPositions();

	system.setTime(t0 + dt / 2);
	Vecd x2 = x0 + (dt / 2) * k1;
	system.setState(x2);

	system.updateForces();

	Vecd k2 = system.getDerivative();
	Vecd x3 = x0 + (dt / 2) * k2;
	system.setState(x3);
	system.updateForces();

	Vecd k3 = system.getDerivative();
	system.setTime(t0 + dt);
	Vecd x4 = x0 + dt * k3;
	system.setState(x4);
	system.updateForces();
	Vecd k4 = system.getDerivative();

	Vecd x_final = x0 + (dt / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
	system.setState(x_final);
	system.setTime(t0 + dt);
    system.setPreviousPositions(previousPositions);
	system.updateForces();
}


void IntegratorVerlet::step(ParticleSystem &system, double dt) {
    Vecd x0 = system.getPositions();
    Vecd x_prev = system.getPreviousPositions();
 
    Vecd x1 = x0 + kd * (x0 - x_prev) + dt * dt * system.getAccelerations();
    
    Vecd v1 = (x1 - x0)/dt;

    system.setPositions(x1);
    system.setVelocities(v1);
	system.setPreviousPositions(x0);
    system.setTime(system.getTime() + dt);
    system.updateForces();
}