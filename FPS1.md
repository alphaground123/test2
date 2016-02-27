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

![equation](http://www.sciweavers.org/download/Tex2Img_1456526547.png)

with:

![equation](http://www.sciweavers.org/download/Tex2Img_1456526628.png) the vector of the gravitational forces acting on the particle:

![equation](http://www.sciweavers.org/download/Tex2Img_1456527329.png)

![equation](http://www.sciweavers.org/download/Tex2Img_1456526682.png) the vector of the reaction force acting on the particle in contact with ground:

![equation](http://www.sciweavers.org/download/Tex2Img_1456527649.png)

![equation](http://www.sciweavers.org/download/Tex2Img_1456527164.png) the vector of the friction force acting on the particle in contact with ground:

![equation](http://www.sciweavers.org/download/Tex2Img_1456533016.png)

where ![equation](http://www.sciweavers.org/download/Tex2Img_1456529475.png) and ![equation](http://www.sciweavers.org/download/Tex2Img_1456529632.png)
represent the ith component of the linear velocity of the particle and the coefficient of friction particle/ground. This model is a composite model allowing both to account for phenomena of Coulomb and viscous.

- ![equation](http://www.sciweavers.org/download/Tex2Img_1456527148.png) is the vector of the impulse force related to the impact between the particle and the ground.
When a particle comes into contact with soil, the particle undergoes impact strength and which is linked (as long as the particle is in contact with the ground):

![equation](http://www.sciweavers.org/download/Tex2Img_1456532916.png)

![equation](http://www.sciweavers.org/download/Tex2Img_1456529864.png) and ![equation](http://www.sciweavers.org/download/Tex2Img_1456529911.png) represent the simulation steps and the coefficient of restitution characterizing a particle impact/ground

With the model selected, the calculation of the forces acting on a particle depends only on its speed and assumed physical specifications at any time. To first order, the acceleration, velocity and position of the particle are given to each step of numerical integration by the relations:

![equation](http://www.sciweavers.org/download/Tex2Img_1456534047.png)

The initial conditions (k = 0) are: 

![equation](http://www.sciweavers.org/download/Tex2Img_1456535016.png) 
