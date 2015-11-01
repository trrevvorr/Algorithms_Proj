// Mission Class Header File

#ifndef MISSION_H
#define MISSION_H
#include <iostream>
#include "sensor.h"
#include <cstdlib>
#include <ctime>

// ===================================
// constants

const int M_RADIUS = 5; // should be 5
// mission start time is a random number from 1 to start_range
const int START_RANGE = 1000; // unspecified default value
//====================================

class Mission
{
public:
	float pos_x;
	float pos_y;
	int start;
	// ASUMPTION!!!!
	// if mission has start=10 and end=12, its duration is 3; t = (10, 11, 12)
	int end;	
	int radius;
	int N_req_sensors;
	bool mission_succeed;


	Mission(int aoi_size=0, int duration=0, int num_req_sensors=0);
	
	void print_details(int m_ID=NULL);
	// overloaded for use with .sort() function
	friend bool operator < (const Mission &l, const Mission &r);
};

#endif