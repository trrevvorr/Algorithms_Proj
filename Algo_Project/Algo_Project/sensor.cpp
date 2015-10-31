#include "sensor.h"
using namespace std;

Sensor::Sensor(int s_id, int aoi_size)
{
	sensor_id = s_id;
	// rand() returns integer between 0 and RAND_MAX
	// dividing rand() by RAND_MAX retuns a float between 0.0000... and 1.0000....
	// mutiplying that by the aoi size returns float between 0.000... and aoi_size
	pos_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * aoi_size;
	pos_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * aoi_size;
	energy = start_energy;
	available = 1;
	conflictions = 0;
}

void Sensor::print_details(int s_ID)
{
	cout << "== SENSOR " << s_ID << " ==\n";
	cout << "Position: (" << pos_x << ", " << pos_y << ")\n";
	cout << "Energy: " << energy << " Available at: " << available << endl;
	
	return;
}

bool operator < (const Sensor &lhs, const Sensor &rhs)
{
	// sensor with least conflictions 
	if (lhs.conflictions < rhs.conflictions) {
		// lhs has fewer conflictions
		return true;
	}
	// if both sensors have same conflictions, most energy
	if (lhs.conflictions == rhs.conflictions) {
		if (lhs.energy > rhs.energy) {
			// lhs has more energy
			return true;
		}
		// rhs has more energy
		return false;
	}
	// rhs has fewer conflictions
	return false;
}