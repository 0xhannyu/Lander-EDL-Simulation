#include <iostream>

class Engine {
public:
	int engineThrust(double currentVelocity, int targetVelocity, int maxThrust, int mass) {

		int a = (int) currentVelocity - targetVelocity;

		int thrustReq = mass * a;

		int ft = 0;

		if(currentVelocity > targetVelocity) {

			if(thrustReq > maxThrust * 5) { ft = maxThrust; }
			else if(thrustReq < maxThrust * 5 && thrustReq > maxThrust * 3) { ft = 0.8 * maxThrust; }
			else if(thrustReq < maxThrust * 3 && thrustReq > maxThrust) { ft = 0.6 * maxThrust; }
			else if(thrustReq < maxThrust) { ft = thrustReq; }
		}

		else { ft = 0; }

		return ft;
	}
};