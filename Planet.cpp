#include <iostream>

class Planet {
public:
    std::string name;
    double gravitationalAcceleration; // Acceleration due to gravity on the planet (m/s^2)
    

    // Constructor to initialize the planet's data
    Planet(std::string planetName, double gravity)
    {
        name = planetName;
        gravitationalAcceleration = gravity;
    }
};