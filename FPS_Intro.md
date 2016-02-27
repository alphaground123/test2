# Falling Particles Simulator - FPS

## Description

The Falling Particles Simulator (FPS) is a program to visualize the evolution in time of the rigid spherical particles fall. We suppose that these particles are subject to gravity and other forces which we will detail in the file Particles.md.

The falling particles simulator considers as many particles as the user has decided to.
If the user enters a large number of particles, the more he will enter data.
Therefore, I suggest beginning with two particles.

## How to use

The FPS runs on Linux. Before using the FPS, make sure you have [Gnuplot] (http://www.gnuplot.info/) on your Linux distribution.

Open the terminal and type the command lines:
make particles_simulator
./particles_simulator

To plot the evolution in time of the falling rigid spherical particles, you need to run gnuplot and load the particles positions.

Command lines for gnuplot:
gnuplot
load 'positions.plt'

## Details

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

The user can see the trajectory of each particle in space.
