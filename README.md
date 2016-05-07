# Falling Particle Simulator (FPS)

## Description

The Falling Particles Simulator (FPS) is a program to visualize the evolution in time of the rigid spherical particles fall. We suppose that these particles are subject to gravity and other forces which we will detail in the file Particles.md.

The falling particles simulator considers as many particles as the user has decided to.
If the user enters a large number of particles, the more he will enter data.
Therefore, I suggest beginning with two particles.

## How to use

The FPS runs on Linux. Before using the FPS, make sure you have [Gnuplot] (http://www.gnuplot.info/) on your Linux distribution.

### Makefile
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

See [FPS Equations] (https://github.com/alphaground123/test2/blob/master/FPS_Equations.md)


In the terminal:

************ Welcome to the Falling Particle Simulator *************

Enter the number of particles: 2 <br />
Enter the total simulation time: 50 <br />
Enter the time step of the simulation: 0.01 <br />

Enter the radius of the particle 1: 0.05 <br />
Enter the mass of the particle 1: 1 <br />
Enter the coefficient of restitution of the impact of the particle 1: 0.4 <br />
Enter the friction coefficient of the particle 1: 0.4 <br />

Enter the radius of the particle 2: 0.08 <br />
Enter the mass of the particle 2: 0.5 <br />
Enter the coefficient of restitution of the impact of the particle 2: 0.2 <br />
Enter the friction coefficient of the particle 2: 0.8 <br />

Enter the initial position x of the particle 1: 4 <br />
Enter the initial position y of the particle 1: 4 <br />
Enter the initial position z of the particle 1: 4 <br />

Enter the initial velocity Vx of the particle 1: 1 <br />
Enter the initial velocity Vy of the particle is 1: 1 <br />
Enter the initial velocity Vz of the particle 1: 1 <br />

Enter the initial position x of the particle 2: 5 <br />
Enter the initial position y of the particle 2: 5 <br />
Enter the initial position z of the particle 2: 5 <br />

Enter the initial velocity Vx of the particle 2: 2 <br />
Enter the initial velocity Vy of the particle 2: 2 <br />
Enter the initial velocity Vz of the particle 2: 2 <br />

End of calculating positions, please call gnuplot and typing load 'positions.plt' to display the trajectory of each particle

And we get the plot of the particles falls as shown below:

![tag image] (https://github.com/alphaground123/test2/blob/master/images/deux_particules.png)

## License

This project is under MIT License.

Copyright (c) 2016 AuthorName

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
