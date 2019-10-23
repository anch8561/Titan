#include <tutorials.h>

void Tutorial1() {
	Simulation sim; // create the basic simulation object.
	Mass* m1 = sim.createMass(Vec(0, 0, 1));
	Mass* m2 = sim.createMass(Vec(1, 0, 1));
	Mass* m3 = sim.createMass(Vec(1, 1, 1));
	Mass* m4 = sim.createMass(Vec(0, 1, 1));
	Mass* m5 = sim.createMass(Vec(0, 0, 2));
	Mass* m6 = sim.createMass(Vec(1, 0, 2));
	Mass* m7 = sim.createMass(Vec(1, 1, 2));
	Mass* m8 = sim.createMass(Vec(0, 1, 2));


	Spring* s1 = sim.createSpring(m1, m2);
	Spring* s2 = sim.createSpring(m2, m3);
	Spring* s3 = sim.createSpring(m3, m4);
	Spring* s4 = sim.createSpring(m4, m1);

	Spring* s5 = sim.createSpring(m1, m5);
	Spring* s6 = sim.createSpring(m5, m8);
	Spring* s7 = sim.createSpring(m8, m4);

	Spring* s8 = sim.createSpring(m8, m7);
	Spring* s9 = sim.createSpring(m5, m6);

	Spring* s10 = sim.createSpring(m2, m6);
	Spring* s11 = sim.createSpring(m6, m7);
	Spring* s12 = sim.createSpring(m3, m7);


	sim.createPlane(Vec(0, 0, 1), 0); // our plane has a unit normal in the z-direction, with 0 offset.


	double runtime = 10.0;
	sim.setBreakpoint(runtime);
	sim.start();
}

#include <math.h>

void Tutorial2() {
	Simulation sim; // create the basic simulation object.
	sim.setViewport(Vec(20, 20, 10), Vec(0, 0, 5), Vec(0, 0, 1)); // set the viewport to see the cubes

	sim.createLattice(Vec(0, 0, 20), Vec(5, 5, 5), 5, 5, 5);
	sim.createPlane(Vec(0, 0, 1), 0);

	sim.start();

	while (sim.time() < 10.0) {
		sim.pause(sim.time() + 1.0);

		sim.createLattice(Vec(cos(sim.time()), sin(sim.time()), 10), Vec(5, 5, 5), 5, 5, 5);

		if (sim.time() > 5.0) {
			sim.deleteContainer(sim.getContainerByIndex(0)); // delete the first created container each iteration, after 5 seconds.
		}

		sim.resume();
	}

	sim.stop();
}

void Tutorial3() {
	Simulation sim; // create the basic simulation object.
	sim.setViewport(Vec(20, 20, 10), Vec(0, 0, 10), Vec(0, 0, 1)); // move the viewport so you can see the cubes

	Lattice* l1 = sim.createLattice(Vec(0, 0, 20), Vec(5, 5, 5), 5, 5, 5);
	sim.createPlane(Vec(0, 0, 1), 0);

	l1->masses[0]->addConstraint(CONSTRAINT_PLANE, Vec(0, 0, 1), 0);
	l1->masses[20]->addConstraint(DIRECTION, Vec(0, 1, 1), 0);
	l1->masses[0]->setDrag(100); // add drag to the mass with drag coefficient C equal to 100.

	sim.start();

	while (sim.time() < 10.0) {
		sim.pause(sim.time() + 1.0);

		sim.get(l1); // get lattice data from the GPU;
		l1->setSpringConstants(10000 * exp(-sim.time() / 3)); // exponential decay of the spring constant
		sim.set(l1); // push the lattice data to the GPU;

		sim.resume();
	}

	sim.stop();
}

#include <stdio.h>
#include <stdlib.h>
#include <cmath> // used to compute the tetrahedron properties

void Tutorial4() {
	//Compute Tetrahedron mass coordinates
	double L = 7; //Predefined Sside length
	double R = tan((30 * 3.14 / 180)) * L / 2; // Base triangle y-coordinate
	double D = sqrt(pow((L / 2), 2) + pow(R, 2)); // Base triangle hypotenuse lenght
	double H = sqrt(pow(L, 2) - pow(D, 2)); // Tetrahedron height

	Simulation sim; // create the basic simulation object.

	// Create Masses 
	Mass* m1 = sim.createMass(Vec(L / 2, -R, 10));
	Mass* m2 = sim.createMass(Vec(-L / 2, -R, 10));
	Mass* m3 = sim.createMass(Vec(0, D, 10));
	Mass* m4 = sim.createMass(Vec(0.1, 0, 10 - H));

	// Create Springs 
	Spring* s1 = sim.createSpring(m1, m2);
	Spring* s2 = sim.createSpring(m2, m3);
	Spring* s3 = sim.createSpring(m3, m1);
	Spring* s4 = sim.createSpring(m1, m4);
	Spring* s5 = sim.createSpring(m2, m4);
	Spring* s6 = sim.createSpring(m3, m4);

	//Set Properties
	sim.defaultRestLength(); //Set the springs' rest length to the initial distance between masses
	sim.setAllSpringConstantValues(10000); // Spring constant [N/m]
	sim.setAllDeltaTValues(0.0001); //Simulation Time resolution [s]

	//Create a ground contact
	sim.createPlane(Vec(0, 0, 1), 0);

	// run Simulation
	sim.setBreakpoint(10.0);
	sim.start(); //Starts the simulation
}