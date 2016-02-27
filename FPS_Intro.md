# Falling Particles Simulator - FPS

## Description

The Falling Particles Simulator (FPS) is a program to visualize the evolution in time of the rigid spherical particles fall. We suppose that these particles are subject to gravity and other forces which we will detail in the file Particles.md.

The falling particles simulator considers as many particles as the user has decided to.
If the user enters a large number of particles, the more he will enter data.
Therefore, I suggest beginning with two particles.

## How to use

The FPS runs on Linux. Before using the FPS, make sure you have [Gnuplot] (http://www.gnuplot.info/) on your Linux distribution.

Open the terminal and type the command lines: <br />
make particles_simulator <br />
./particles_simulator <br />

To plot the evolution in time of the falling rigid spherical particles, you need to run gnuplot and load the particles positions.

Command lines for gnuplot: <br />
gnuplot <br />
load 'positions.plt' <br />

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

## Example

We set the following parameters for two particles, see the tables below: 

|Parameter name|Data|
| :---: | :---: |
| Number of particles | 2 |
| Total simulation | 50 |
|Time step|0.01|

|Parameter name|Particle 1|Particle 2|
| :---: | :---: | :---: |
| Radius | 0.05 | 0.08 |
| Mass | 1 | 0.5 |
|Coefficient of restitution|0.4|0.2|
|Friction coefficient|0.4|0.8|
|Initial position x|4|5|
|Initial position y|4|5|
|Initial position z|4|5|
|Initial velocity Vx|1|2|
|Initial velocity Vy|1|2|
|Initial velocity Vz|1|2|
