#ifndef AOI_H
#define AOI_H
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <cmath>
//pow(b,p); b = base, p = power
//sqrt(n);
#include "Mission.h"
#include "Sensor.h"
using namespace std;


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
	void print_sensors(list<Sensor> s);
	void update_sensor(int s_id, int duration, int available_at);
	Sensor lookup_by_sensor_id(int s_id);

	// print details
	void print_details(int num_details=0);
	void print_mission_success_count();
	void print_sensors_under_10();
	void print_sensor_energy_stats();
	
	// Other functions
	list<Sensor> find_valid_sensors(Mission m);
	bool in_range(Mission m, Sensor s);
	
	// sensor alocation algorithms
	void online_greedy();
	void offline_greedy();
    void random_algo();

//	void sorted_valid_sensor_least_conflication(Mission a_mission);
//	bool valid(Mission a_mission, Sensor a_sensor);
//
//    void update_sensor_information(Mission a_mission);
//    void random_pick(Mission a_mission);
//
//    void find_confliction();


  

// put valid_sensor array at mission class

//  Sensor *valid_sensor=NULL;
	
//could we giev each sensor a ID????





};

#endif