# Falling Particle Simulator - FPS

The purpose of this program is to develop a simulator easy to use in order to visualize the falling rigid spherical particles subjected to gravity and a set of forces. We use the numerical integration of the equations to make the movement of the particles.

We suppose that:
- The center of mass of a particle is coincident with the center of gravity
- Particles rotational movements are not simulated
- The radius, density, coefficient of restitution particle/ground and the friction coefficient particle/ground can be different from one particle to another

In addition, two simplifying assumptions are made:
- The ground is supposed plane and zero slope 
- Collisions between particles are not simulated

The movement equation of a particle is described by:

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/sum_forces.png)

with:

- ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/force_g.png) the vector of the gravitational forces acting on the particle:

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/gravity.png)

- ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/force_r.png) the vector of the reaction force acting on the particle in contact with ground:

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/reaction_force.png)

- ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/force_f.png) the vector of the friction force acting on the particle in contact with ground:

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/friction_force.png)

where ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/velocity_ith.png) and ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/varphi.png)
represent the ith component of the linear velocity of the particle and the coefficient of friction particle/ground. This model is a composite model allowing both to account for phenomena of Coulomb and viscous.

- ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/force_i.png) is the vector of the impulse force related to the impact between the particle and the ground.
When a particle comes into contact with soil, the particle undergoes impact strength and which is linked (as long as the particle is in contact with the ground):

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/impulse_force.png)

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/delta_t.png) and ![equation](https://github.com/alphaground123/test2/blob/master/images_equations/restitution_coefficient.png) represent the simulation steps and the coefficient of restitution characterizing a particle impact/ground

With the model selected, the calculation of the forces acting on a particle depends only on its speed and assumed physical specifications at any time. To first order, the acceleration, velocity and position of the particle are given to each step of numerical integration by the relations:

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/position_vector.png)

The initial conditions (k = 0) are: 

![equation](https://github.com/alphaground123/test2/blob/master/images_equations/initial_position_velocity.png) 
