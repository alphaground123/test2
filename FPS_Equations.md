# Falling Particles Simulator - FPS

The Falling Particles Simulator (FPS) is a program to visualize the evolution in time of the rigid spherical particles fall. We suppose that these particles are subject to gravity and other forces which we will detail in the file Particles.md.

The fallling particles simulator considers as many particles as the user has decided to.
If the user enters a large number of particles, the more he will enter data.
Therefore, I suggest beginning with two particles.

Usage:
The command lines are:
make particles_simulator
./particles_simulator

To plot the evolution in time of the falling rigid spherical particles, you need to run gnuplot and load the particles positions.

Command lines for gnuplot:
gnuplot
load 'positions.plt'

In the FPS, we distinguish two properties:
- The simulation properties
- The particle properties
 
The simulation properties are:
- The number of particles
- The total simulation time
- The time step of the simulation

The particle properties are:
- The radius of the particle
- The mass of the particle
- The coefficient of restitution to the impact
- The friction coefficient
- Its initial position
- Its initial speed

Once the PFS has all the data, it will calculate all positions in the x, y and z axes of the particles over time.
All the x, y and z positions of each particle are stored in the .data files and some commands for gnuplot are generated in the file 'positions.plt' that will be created automatically.

Then the user type in the terminal, the command "gnuplot" to call gnuplot, then load the file positions.plt by typing:
load 'positions.plt'

The user can see the trajectory of each particle in space as shown below:

## An example of using:

************ Welcome to the Falling Particle Simulator *************

Enter the number of particles: 2  <br />
Enter the total simulation time: 50 <br />
Enter the time step of the simulation: 0.01 <br />

Enter the radius of the particle 1: 0.05<br />
Enter the mass of the particle 1: 1<br />
Enter the coefficient of restitution of the impact of the particle 1: 0.4<br />
Enter the friction coefficient of the particle 1: 0.4<br />

Enter the radius of the particle 2: 0.08<br />
Enter the mass of the particle 2: 0.5<br />
Enter the coefficient of restitution of the impact of the particle 2: 0.2<br />
Enter the friction coefficient of the particle 2: 0.8<br />

Enter the initial position x of the particle 1: 4<br />
Enter the initial position y of the particle 1: 4<br />
Enter the initial position z of the particle 1: 4<br />

Enter the initial velocity Vx of the particle 1: 1<br />
Enter the initial velocity Vy of the particle is 1: 1<br />
Enter the initial velocity Vz of the particle 1: 1<br />

Enter the initial position x of the particle 2: 5<br />
Enter the initial position y of the particle 2: 5<br />
Enter the initial position z of the particle 2: 5<br />

Enter the initial velocity Vx of the particle 2: 2<br />
Enter the initial velocity Vy of the particle 2: 2<br />
Enter the initial velocity Vz of the particle 2: 2<br />

End of calculating positions, please call gnuplot
and typing load 'positions.plt' to display the trajectory of each particle

And we get the plot of the particles falls as shown below:

![tag image] (https://github.com/alphaground123/test2/blob/master/cinq_particules.png)
