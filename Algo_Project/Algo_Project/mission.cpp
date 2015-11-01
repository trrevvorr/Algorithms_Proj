#include "mission.h"
using namespace std;

Mission::Mission(int aoi_size, int duration, int num_req_sensors)
{
	// rand() returns integer between 0 and RAND_MAX
	// dividing rand() by RAND_MAX retuns a float between 0.0000... and 1.0000....
	// mutiplying that by the aoi size returns float between 0.000... and aoi_size
	pos_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * aoi_size;
	pos_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * aoi_size;
	start = (rand() % START_RANGE) + 1;
	end = start + duration - 1;
	radius = M_RADIUS;
	N_req_sensors = num_req_sensors;
	mission_succeed = false;
};

void Mission::print_details(int m_ID)
{
	cout << "\n== MISSION " << m_ID << " ==\n";
	cout << "Position: (" << pos_x << ", " << pos_y << ")\n";
	cout << "Start: " << start << " End: " << end << " Succeded: " << mission_succeed << endl;
	cout << "Radius: " << radius << " Required Sensors: " << N_req_sensors << endl;
	
	return;
}

bool operator < (const Mission &lhs, const Mission &rhs)
{
	if (lhs.start < rhs.start) {
		return true;
	}
	return false;
}