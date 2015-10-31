
#include "AOI.h"
using namespace std;

void simulate_AOIs(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors);

int main()
{
	cout << "START - START - START - START - START - START - START\n\n";
	srand(time(NULL));
	
    // EXPIRAMENT 1
	// num_sensor_input, num_mission_input, mission_duration, mission_req_sensors
    for (int num_sensors = 50; num_sensors <= 1000; num_sensors += 50) {
        simulate_AOIs(num_sensors, 100, 10, 5);
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

//// extra expiraments ////

// 1: USE ALL SENSORS
// mission radius = aoi size (missions cover entire AOI)
// N_req_sensors = s_list.size() every mission includes every sensor
// lots of missions (decreases the average amount of energy remaining at the end)

// 2: lots of missions, few sensors
//              sucesses    mean    median
// online       90          7750     730
// offline      90
// random
