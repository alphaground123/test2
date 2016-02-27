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

*****
fg

![equation](http://www.sciweavers.org/download/Tex2Img_1456526628.png)

fr

![equation](http://www.sciweavers.org/download/Tex2Img_1456526682.png)

ff

![equation](http://www.sciweavers.org/download/Tex2Img_1456527164.png)

fi

![equation](http://www.sciweavers.org/download/Tex2Img_1456527148.png)

fg = composantes

![equation](http://www.sciweavers.org/download/Tex2Img_1456527329.png)

ff =

![equation](http://www.sciweavers.org/download/Tex2Img_1456527562.png)

fr = -fg

![equation](http://www.sciweavers.org/download/Tex2Img_1456527649.png)

fffff
![equation](http://www.sciweavers.org/download/Tex2Img_1456528395.png)

![equation]()




# Markdown-LaTeX

This is a Python script that looks for a README written with Markdown + ![equation](http://latex.codecogs.com/png.latex?%24%24%5CLaTeX%24%24) and outputs a README.md with the ![equation](http://latex.codecogs.com/png.latex?%24%24%5CLaTeX%24%24) equations replaced by images rendered by [CodeCogs].

You can use it with other Markdown files, just pass the path to them as an argument to the script:

```
python insert_equations.py [MARKDOWN_FILE_PATH]
```

## How to write the equations

To type the equations in the original document, just put them between double dolar signs ($).

As an example, this is a [README.md] generated by the [README] in this repo using that script, so we can type things like this:

![equation](http://latex.codecogs.com/png.latex?%24%24%20J%28%5Cmathbf%7BW_1%7D%2C%20%5Cmathbf%7Bb_1%7D%2C%20%5Cmathbf%7BW_2%7D%2C%20%5Cmathbf%7Bb_2%7D%29%20%3D%20%5Cfrac%7B1%7D%7B2t%7D%5Cmathbf%7B1_v%7D%5ET%20%5Ccdot%20%5B%28%28%5Cmathbf%7Ba_3%7D%20-%20%5Cmathbf%7BX%7D%29%20%5Codot%20%28%5Cmathbf%7Ba_3%7D%20-%20%5Cmathbf%7BX%7D%29%29%20%5Ccdot%20%5Cmathbf%7B1_t%7D%5D%20%2B%20%5Cfrac%7B%5Clambda%7D%7B2%7D%5B%5Cmathbf%7B1_h%7D%5ET%20%5Ccdot%20%28%5Cmathbf%7BW_1%7D%5Codot%20%5Cmathbf%7BW_1%7D%29%20%5Ccdot%20%5Cmathbf%7B1_v%7D%20%2B%20%5Cmathbf%7B1_v%7D%5ET%20%5Ccdot%20%28%5Cmathbf%7BW_2%7D%5Codot%20%5Cmathbf%7BW_2%7D%29%20%5Ccdot%20%5Cmathbf%7B1_h%7D%20%5D%20%2B%20%5Cbeta%5Cmathbf%7B1_h%7D%5ET%20%5Ccdot%20%5B%5Crho%20%5Clog%28%5Crho%5Cmathbf%7B1_h%7D%20%5Coslash%20%5Cboldsymbol%7B%5Chat%20%5Crho%7D%29%20%2B%20%281%20-%20%5Crho%29%5Clog%28%28%5Cmathbf%7B1_h%7D-%5Crho%5Cmathbf%7B1_h%7D%29%20%5Coslash%20%28%5Cmathbf%7B1_h%7D%20-%20%5Cboldsymbol%7B%5Chat%20%5Crho%7D%29%29%5D%24%24).

Now compare the [README] and the raw version of this [README.md].

That's a simple way to write equations here in Github. 

Have ![equation](http://latex.codecogs.com/png.latex?%24%24f%20%5Ccup%20%5Cmathbb%7BN%7D%24%24)! 

[CodeCogs]:http://www.codecogs.com/latex/eqneditor.php
[README]:https://raw.github.com/allanino/markdown-latex/master/README
[README.md]:https://raw.github.com/allanino/markdown-latex/master/README.md
