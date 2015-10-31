// Sensor Class Header File

#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>
#include <cstdlib>
#include <ctime>

// ===================================
// constants

const int start_energy = 1000; // should be 1000
//====================================

class Sensor
{
public:
	int sensor_id;
	float pos_x;
	float pos_y;
	int energy;
	// ASUMPTION!!!!
	// if a sensor is available at 5 then it available starting at t = 5
	int available;
	int conflictions;

	Sensor(int sensor_id, int aoi_size=0);
	
	void print_details(int s_ID=NULL);
	// for use with .sort()
	// .sort() will sort by conflictions (lowest first)
	// then by energy level (highest first)
	friend bool operator < (const Sensor &l, const Sensor &r);
	
};

#endif