
#include "AOI.h"
using namespace std;

///////////////////////////////////////
// constants

const int NUM_MISSIONS_PER_AOI = 1000;

///////////////////////////////////////

void simulate_AOIs(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors);
void simulate_AOIs_for_csv(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors);

int main()
{
	cout << "START - START - START - START - START - START - START\n\n";
	srand(time(NULL));
	
	cout << "# sensors,m_duration,req sensors,online success,online <10 energy,offline success,offline <10 energy,random success,random <10 energy\n";
	
    // EXPIRAMENT 1: vary the number of sensors per AOI
    for (int num_sensors = 50; num_sensors <= 1000; num_sensors += 50) {
        simulate_AOIs_for_csv(num_sensors, NUM_MISSIONS_PER_AOI, 10, 5);
    }
	
	// EXPIRAMENT 2: vary the mission duration
	for (int mission_dur = 10; mission_dur <= 100; mission_dur += 10) {
		simulate_AOIs_for_csv(500, NUM_MISSIONS_PER_AOI, mission_dur, 5);
	}
	
	// EXPIRAMENT 3: vary the number of sensors required by each mission
	for (int num_req_sensors = 1; num_req_sensors <= 20; num_req_sensors += 1) {
		simulate_AOIs_for_csv(500, NUM_MISSIONS_PER_AOI, 10, num_req_sensors);
	}
	
	cout << "\n\nEND - END - END - END - END - END - END - END - END\n";
	return 0;

}

void simulate_AOIs(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors)
{
    cout << "\n######## AOI ########\n";
    //	cout << "AOI size: " << aoi_size << endl;
    cout << "# sensors: " << num_sensor_input << " # missions " << num_mission_input;
    cout << " mission_dur: " << mission_duration;
    cout << " N_req_sensors: " << mission_req_sensors << endl;
    
    cout << "\n--Online--\n";
    AOI a_on(num_sensor_input, num_mission_input, mission_duration, mission_req_sensors);
    a_on.online_greedy();
    a_on.print_details();
    
    cout << "\n--Offline--\n";
    AOI a_off(num_sensor_input, num_mission_input, mission_duration, mission_req_sensors);
    a_off.offline_greedy();
    a_off.print_details();
    
    cout << "\n--Random--\n";
    AOI a_rnd(num_sensor_input, num_mission_input, mission_duration, mission_req_sensors);
    a_rnd.random_algo();
    a_rnd.print_details();
    
    return;
}

void simulate_AOIs_for_csv(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors)
{
	
	cout << num_sensor_input << "," << mission_duration << "," << mission_req_sensors <<",";
	
	AOI a_on(num_sensor_input, num_mission_input, mission_duration, mission_req_sensors);
	a_on.online_greedy();
	a_on.print_details_csv_friendly();

	AOI a_off(num_sensor_input, num_mission_input, mission_duration, mission_req_sensors);
	a_off.offline_greedy();
	a_off.print_details_csv_friendly();

	AOI a_rnd(num_sensor_input, num_mission_input, mission_duration, mission_req_sensors);
	a_rnd.random_algo();
	a_rnd.print_details_csv_friendly();
	
	cout << endl;
	
	return;
}