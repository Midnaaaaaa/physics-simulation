# Real-Time Physics Engine (C++ / OpenGL / Qt)

Real-time physics engine developed in C++ using OpenGL and Qt, featuring multiple numerical integrators and classic physics-based simulations.

---

## Preview

### Simulation Demo

[![Watch the video](https://img.youtube.com/vi/qKr9djDUIvg/maxresdefault.jpg)](https://www.youtube.com/watch?v=qKr9djDUIvg)

---

## Features

### Numerical Integration Methods

- Euler
- Symplectic Euler
- Midpoint
- RK2 (Runge-Kutta 2)
- RK4 (Runge-Kutta 4)
- Verlet Integration

---

### Physics Simulations

- Projectile motion system
- Cloth simulation using particle constraints
- Rope simulation with distance constraints
- Particle-based fluid simulation
- N-body gravitational system with attractors
- Fountain particle system

---

## Simulation Systems

The engine is designed around modular physics systems:

### Particle System
Core abstraction used across most simulations (fluids, cloth, fountains).

### Constraint Solver
Used for:
- Cloth stability
- Rope physics
- Structural constraints in particle systems

### Force-Based Dynamics
Supports:
- Gravity
- Attraction/repulsion fields
- Custom force generators

---

## Numerical Integration

Multiple integrators allow comparison of stability and accuracy:

- Euler (fast but unstable)
- Symplectic Euler (improved energy behavior)
- Midpoint method (better accuracy)
- RK2 / RK4 (high precision)
- Verlet (stable for particles and cloth)

---

## Rendering Pipeline

- Real-time OpenGL rendering
- GLSL shader-based visualization
- Debug visualization for forces and velocities
- Interactive camera controls via Qt

---

## Interactive Features

- Real-time parameter tweaking
- Live simulation switching
- Pause / resume system
- Adjustable physics timestep
- Visual debugging tools

---

## Technologies

- C++
- OpenGL
- Qt
- GLSL
- Numerical Integration Methods
- Physics Simulation Systems
- Particle Systems

---

## Applications

This project is suitable for:

- Physics simulation research
- Game engine development studies
- Numerical methods experimentation
- Real-time animation systems
- Educational visualization tools

---

## Future Work

- GPU-based physics acceleration
- SPH fluid simulation improvements
- Constraint solver optimization (XPBD)
- Multi-threaded simulation pipeline
- Compute shader integration

---

## License

MIT License
