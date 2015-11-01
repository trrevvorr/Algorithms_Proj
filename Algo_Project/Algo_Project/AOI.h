#ifndef AOI_H
#define AOI_H
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <cmath>
#include "Mission.h"
#include "Sensor.h"
using namespace std;

///////////////////////////////////////
// constants

const int AOI_SIZE = 50; // should be 50

//////////////////////////////////////

class AOI
{
public:
	/////// VARIABLES ///////
	int aoi_size;
	int num_sensor;
	int num_mission;
	
	list<Mission> m_list;
	list<Sensor> s_list;
	
	
	/////// FUNCTIONS ///////
	AOI(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors);
	
	// list accesors/modifiers
	Sensor index_sensors(int index, list<Sensor> s);
	Mission index_missions(int index);
	void update_sensor(int s_id, int duration, int available_at);
	Sensor lookup_by_sensor_id(int s_id);

	// print details
	void print_details(int num_details=0);
	void print_sensors(list<Sensor> s);
	void print_mission_success_count();
	void print_sensors_under_10();
	void print_sensor_energy_stats();
	void print_details_csv_friendly();
	
	// Other functions
	list<Sensor> find_valid_sensors(Mission m);
	bool in_range(Mission m, Sensor s);
	
	// sensor alocation algorithms
	void online_greedy();
	void offline_greedy();
    void random_algo();
};

#endif