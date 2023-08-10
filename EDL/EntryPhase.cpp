#include <iostream>

class EntryPhase {
public:
	double entryPhaseVel(double velocity, double g) {

	    velocity = velocity + (g * 0.1);

	    return velocity;
	}

	double phaseAlt(double altitude, double velocity) {

	    altitude -= (velocity * 0.1);

	    return altitude;
	}
};