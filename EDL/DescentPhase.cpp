#include <iostream>

class DescentPhase {
public:
	
	double descentPhaseVel(double freeFallVel, int thrustForce, int mass) {

	    double thrustRetardation = thrustForce / mass;

	    double descentVel = freeFallVel - thrustRetardation; // Thrust Force is already converted into tf standard so need to multiply thrustRetardation by 0.1

	    return descentVel; 
	}
};