#include <iostream>
#include <unistd.h>
#include <windows.h>
#include <math.h>
#include <chrono>

#include "Lander.cpp"
#include "Planet.cpp"
#include "EDL/EntryPhase.cpp"
#include "EDL/DescentPhase.cpp"
#include "Engine.cpp"

using namespace std;

const double atmosphericDragCoefficient = 0;
const double atmosphericDensity = 0;
const int tf = 100000;

Planet planet("Moon", 1.625);
Lander sv(1300, 85); // Initial Altitude, Initial Velocity

int landingPhaseAltitudeUL = 1000;
int descentPhaseAltitudeUL = 5000;

int targetVel = sqrt(2 * planet.gravitationalAcceleration * landingPhaseAltitudeUL);

EntryPhase ep;
DescentPhase dp;

double calculateAtmosphericDrag(double velocity, int crossSectionalArea) {

    double dragForce = 0.5 * atmosphericDragCoefficient * crossSectionalArea * atmosphericDensity * velocity * velocity;

    return dragForce;
}

void entryPhase() {

    auto inEP = std::chrono::high_resolution_clock::now();

    while(sv.altitude > descentPhaseAltitudeUL) {

        system("cls");

        cout << "| ENTRY PHASE | No Thrusters Activated |\n\n";

        cout << "Altitude : " << sv.altitude << " m\n"
             << "Velocity : " << sv.velocity << " m/s\n"
             << "Planet : " << planet.name << ", Gravity : " << planet.gravitationalAcceleration << " m/s^2\n"
             << "Atmospheric Drag : " << calculateAtmosphericDrag(sv.velocity, sv.crossSectionalArea) << " N";

        cout.flush();

        sv.altitude = ep.phaseAlt(sv.altitude, sv.velocity);
        sv.velocity = ep.entryPhaseVel(sv.velocity, planet.gravitationalAcceleration);

        usleep(tf); // Sleep for 100 milliseconds (0.1 seconds)
    }

    auto edEP = std::chrono::high_resolution_clock::now();

    auto durEP = std::chrono::duration_cast<std::chrono::seconds>(edEP - inEP);

    cout << "\n\n| ENTRY PHASE OVER in " << durEP.count() << " sec | ENTERING DESCENT PHASE |\n\n";
    cout << "Activating Thrusters (" << sv.thrusterActivation << "%)...\n";
}

void descentPhase() {

    Engine eng;

    auto inDP = std::chrono::high_resolution_clock::now();

    while(sv.altitude > landingPhaseAltitudeUL) {

        system("cls");

        cout << "| DESCENT PHASE | Thrusters Activated |\n\n";

        cout << "Altitude : " << sv.altitude << " m\n"
             << "Velocity : " << sv.velocity << " m/s\n"
             << "Planet : " << planet.name << ", Gravity : " << planet.gravitationalAcceleration << " m/s^2\n"
             << "Engine Activation : " << sv.thrusterActivation << " %\n"
             << "GWeight : " << sv.totalMass << " kg | Fuel Weight : " << sv.fuelMass << " kg";

        cout.flush();

        sv.thrustAdj = eng.engineThrust(sv.velocity, targetVel, sv.thrustForceMax);
        sv.thrusterActivation = (sv.thrustAdj / sv.thrustForceMax) * 100;
        sv.fuelMass -= (sv.thrustAdj / 3000) * planet.gravitationalAcceleration;
        sv.totalMass = sv.dryMass + sv.fuelMass;

        sv.altitude = ep.phaseAlt(sv.altitude, sv.velocity);
        sv.velocity = dp.descentPhaseVel(ep.entryPhaseVel(sv.velocity, planet.gravitationalAcceleration), sv.thrustAdj, sv.totalMass);

        usleep(tf);
    }

    auto edDP = std::chrono::high_resolution_clock::now();

    auto durDP = std::chrono::duration_cast<std::chrono::seconds>(edDP - inDP);

    cout << "\n\n| DESCENT PHASE OVER in " << durDP.count() << " sec | ENTERING LANDING PHASE |\n\n";
}

void landingPhase() {

    auto inLP = std::chrono::high_resolution_clock::now();

    while(sv.altitude > 0) {

        system("cls");

        cout << "| LANDING PHASE |\n\n";

        cout << "Altitude : " << sv.altitude << "m\n"
             << "Velocity : " << sv.velocity << "m/s\n"
             << "Engine Activation : " << sv.thrusterActivation << " %\n"
             << "GWeight : " << sv.totalMass << "kg | Fuel Weight : " << sv.fuelMass << "kg";

        cout.flush();

        double acc = sv.velocity>5?(targetVel * targetVel)/(2 * landingPhaseAltitudeUL):0;
        sv.thrustAdj = (int) sv.totalMass * acc;
        sv.thrusterActivation = (sv.thrustAdj / sv.thrustForceMax) * 100;
        sv.fuelMass -= (sv.thrustAdj / 3000) * planet.gravitationalAcceleration;
        sv.totalMass = sv.dryMass + sv.fuelMass;

        sv.altitude = ep.phaseAlt(sv.altitude, sv.velocity);
        sv.velocity = dp.descentPhaseVel(ep.entryPhaseVel(sv.velocity, planet.gravitationalAcceleration), sv.thrustAdj, sv.totalMass);

        usleep(tf);
    }

    auto edLP = std::chrono::high_resolution_clock::now();

    auto durLP = std::chrono::duration_cast<std::chrono::seconds>(edLP - inLP);

    cout << "\n\n| LANDING PHASE OVER in " << durLP.count() << " sec | SUCCESSFULLY LANDED |\n\n";
}

int main() {

    entryPhase();

    usleep(3000000);

    descentPhase();

    usleep(3000000);

    landingPhase();

    return 0;
}