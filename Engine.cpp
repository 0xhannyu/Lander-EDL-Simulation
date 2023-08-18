#include <iostream>

class Engine {
public:
	int engineThrust(double currentVelocity, int targetVelocity, int maxThrust) {

		int ft = 0;

		if(currentVelocity > targetVelocity) {

			if(currentVelocity >= (targetVelocity * 2)) { ft = maxThrust; }

			else if(currentVelocity >= (targetVelocity) * 1.5 && currentVelocity < (targetVelocity * 2)) { ft = maxThrust * 0.8; }

			else if(currentVelocity >= (targetVelocity) * 1.3 && currentVelocity < (targetVelocity * 1.5)) { ft = maxThrust * 0.6; }

			else if(currentVelocity >= targetVelocity && currentVelocity < (targetVelocity * 1.3)) { ft = maxThrust * 0.4; }
		}

		else { ft = 0; }

		return ft;
	}
};