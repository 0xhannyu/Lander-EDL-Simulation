#include <iostream>

class Lander {
public:
    double altitude;
    double velocity;

    int dryMass = 626;
    int fuelMass = 845;
    int totalMass = dryMass + fuelMass;
    int crossSectionalArea = 5;

    int thrustAdj = 0;
    int thrustForceMax = 4000; // Newtons
    int thrusterActivation = 0; // %

    Lander(double initialAltitude, double initialVelocity)
    {
        altitude = initialAltitude;
        velocity = initialVelocity * 0.1;
    }
};