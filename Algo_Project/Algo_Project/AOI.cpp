#include "AOI.h"

// Default constructor for AOI, Initializes Mission List and Sensor list as well
AOI::AOI(int num_sensor_input, int num_mission_input, int mission_duration, int mission_req_sensors)
{
	// initialize AOI specific variables
	aoi_size = 50;
	num_sensor = num_sensor_input;
	num_mission = num_mission_input;
	
	// initialize Sensors
	for (int i = 0; i < num_sensor; i++)
	{
		s_list.push_back(Sensor(i, aoi_size));
	}
	
	// initialize Missions
	for (int i = 0; i < num_mission; i++)
	{
		m_list.push_back(Mission(aoi_size, mission_duration, mission_req_sensors));
	}

}

// Prints the values of the member variables of the AOI
// if you pass it a 1 (num_details=1), it will print all the Missions in the m_list as well
// if you pass it a 2, it will print all the Sensors in the s_list as well
// if you pass it a 3, it will print both the sensors and the missions
void AOI::print_details(int num_details)
{
//	cout << "### AOI ###\n";
////	cout << "AOI size: " << aoi_size << endl;
//	cout << "# sensors: " << num_sensor << " # missions " << num_mission;
//    cout << " mission_dur: " << index_missions(0).end - index_missions(0).start +1;
//    cout << " N_req_sensors: " << index_missions(0).N_req_sensors << endl;
	if (num_details == 2 || num_details == 3) {
		cout << "\n### SENSORS ###\n\n";
		for (int i = 0; i < num_sensor; i++) {
			index_sensors(i, s_list).print_details(i);
		}
	}
	
	if (num_details == 1 || num_details == 3) {
		cout << "\n### MISSIONS ###\n\n";
		for (int i = 0; i < num_mission; i++) {
			index_missions(i).print_details(i);
		}
	}
	
	//cout << "### RESULTS ###\n";
	print_mission_success_count();
	print_sensors_under_10();
    print_sensor_energy_stats();
}

// Returns the sensor at the index of the s list. For example:
// index_sensors(0, s_list) will retun the frist sensor in the s_list
// WARNING, updating the sensor returned will not update it in the actual list
Sensor AOI::index_sensors(int index, list<Sensor> s)
{
	list<Sensor>::iterator list_iter = s.begin();
	for (int i = 0; i < index; i++) {
		list_iter++;
	}
	
	return *list_iter;
}

// Returns the Mission at the index of the m_list. For example:
// index_missions(0) will retun the frist sensor in the m_list
//WARNING, updating the Mission returned will not update it in the actual list
Mission AOI::index_missions(int index)
{
	list<Mission>::iterator list_iter = m_list.begin();
	for (int i = 0; i < index; i++) {
		list_iter++;
	}
	
	return *list_iter;
}

// Prints the number of missions that have succeeded (mission_succeed == true)
void AOI::print_mission_success_count()
{
	int succeed_count = 0;
	
	for (int i = 0; i < num_mission; i++) {
		if (index_missions(i).mission_succeed) {
			succeed_count++;
		}
	}
	
	cout << "Number of Missions that succeeded: " << succeed_count << endl;
	return;
}

// Prints the number of sensors with less than 10 energy units remaining
void AOI::print_sensors_under_10()
{
	int count_under_10 = 0;
	
	for (int i = 0; i < num_sensor; i++) {
		if (index_sensors(i, s_list).energy < 10) {
			count_under_10++;
		}
	}
	
	cout << "Number of Sensors having <10 energy left: " << count_under_10 << endl;
	return;
}

// prints the mean and median energy levels of all sensors in s_list
void AOI::print_sensor_energy_stats()
{
	list<int> energies;
	int total_energy = 0, mean, median = -1;
	list<Sensor>::iterator s_iter = s_list.begin();
	
	for (int i = 0; i < num_sensor; i++) {
		energies.push_back(s_iter->energy);
		s_iter++;
	}
	
	energies.sort();
	list<int>::iterator int_iter = energies.begin();
	for (int i = 0; i < num_sensor; i++) {
		total_energy += *int_iter;
		if (i == num_sensor/2) {
			median = *int_iter;
		}
		int_iter++;
	}
	mean = total_energy/num_sensor;
	cout << "Mean Energy: " << mean << ", Median Energy: " << median << endl;
	
	return;
}

// Returns a list of sensors that:
// A) are available at the time the mission will begin
// B) have enough energy to conplete the mission
// C) are within the radius of the Mission it was passed (m)
list<Sensor> AOI::find_valid_sensors(Mission m)
{
	// float m_x, m_y, s_x, s_y, dist;
	list<Sensor> valid_sensors;
    list<Sensor>::iterator s_iter = s_list.begin();
    
	for (int i = 0; i < num_sensor; i++) {
		if ((s_iter->available <= m.start) &&
			(s_iter->energy > (m.end - m.start))) {
			if (in_range(m, *s_iter)) {
				// add sensor i to list of valid sensors
				valid_sensors.push_back(*s_iter);
			}
		}
        s_iter++;
	}
	return valid_sensors;
}

bool AOI::in_range(Mission m, Sensor s)
{
	float m_x = m.pos_x;
	float m_y = m.pos_y;
	float s_x = s.pos_x;
	float s_y = s.pos_y;
	float dist = sqrt(pow((m_x - s_x),2) + pow((m_y - s_y),2));
	
	if (dist <= m.radius) {return true;}
	return false;
}


// Prints out the Sensors in the list it is passed (s)
void AOI::print_sensors(list<Sensor> s)
{
	for (int i = 0; i < s.size(); i++) {
		index_sensors(i, s).print_details(i);
	}
	return;
}

// Itterates through all missions, finding a list of valid sensors for each
// sorts the list of valid sensors for each mission by energy level (highest to lowest)
// picks N missions with the highest energy s.t. N = N_req_sensors
// updates mission_suceed
// updates sensors (time available, energy level)
void AOI::online_greedy()
{
	list<Sensor> valid_sensors, to_print;
	// used to update mission in m_list so the changes are not just local
	list<Mission>::iterator m_iter;
	// this saves keystrokes and computation time but this_mission should only
	// be used for RETRIEVING detail about the mission. Changing this_mission
	// will NOT update the coorisponding mission in m_list
	// Mission this_mission;
	// used for updating energy level of optimal sensors
	int m_duration, s_id;
	
	// sorts by mission start time (earliest first)
	m_list.sort();
    m_iter = m_list.begin();
	for (int m_index = 0; m_index < num_mission; m_index++) {
		// this_mission = index_missions(m_index);
		m_duration = m_iter->end - m_iter->start + 1;
		
		valid_sensors = find_valid_sensors(*m_iter);
		
		// if enough valid sensors were found
		if (valid_sensors.size() >= m_iter->N_req_sensors) {
			m_iter->mission_succeed = true;
			
			// sort sensors by energy level (highest to lowest)
			valid_sensors.sort();
			
//			// print outcome
//			(*m_iter).print_details(m_index);
//			cout << "\nOPTIMAL SENSORS\n";
			// update the first N sensors of the sorted valid_sensor list
			// N = N_req_sensors
			for (int i = 0; i < m_iter->N_req_sensors; i++) {
				s_id = index_sensors(i, valid_sensors).sensor_id;
				update_sensor(s_id, m_duration, m_iter->end);
				
//				to_print.push_back(lookup_by_sensor_id(s_id));
			}
//			print_sensors(to_print);
//			to_print.clear();
//			cout << endl;
		}
		else
		{
//			this_mission.print_details(m_index);
//			cout << "MISSION FAILED!\n";
		}
        m_iter++;
	}
	return;
}

void AOI::offline_greedy()
{
	list<Sensor> valid_sensors, to_print;
	// used to update mission in m_list so the changes are not just local
	list<Mission>::iterator m_iter;
	// this saves keystrokes and computation time but this_mission should only
	// be used for RETRIEVING detail about the mission. Changing this_mission
	// will NOT update the coorisponding mission in m_list
	Mission this_mission;
	// used for updating energy level of optimal sensors
	int m_duration, s_id;
	
	// sorts by mission start time (earliest first)
	m_list.sort();
	
	for (int m_index = 0; m_index < num_mission; m_index++) {
		this_mission = index_missions(m_index);
		m_duration = this_mission.end - this_mission.start + 1;
		
		valid_sensors = find_valid_sensors(this_mission);
		
		// if enough valid sensors were found
		if (valid_sensors.size() >= this_mission.N_req_sensors) {
			m_iter = m_list.begin();
			// advance itterator to mission m_index in m_list;
			advance(m_iter, m_index);
			m_iter->mission_succeed = true;
			
//			// print outcome
//			m_iter->print_details(m_index);
//			cout << "\nOPTIMAL SENSORS\n";
			
			// int m = m_index + 1;
			m_iter++;
			while (m_iter->start <= this_mission.end) {
				list<Sensor>::iterator this_sensor = valid_sensors.begin();
				// loop for every sensor in valid sensor list
				while (1) {
					if (in_range(*m_iter, *this_sensor)) {
						this_sensor->conflictions++;
					}
					if (this_sensor == valid_sensors.end()) {break;}
					this_sensor++;
				}
				m_iter++;
			}
			
			// sort sensors by number of conflictions (lowest to highest)
			// then by energy level (highest to lowest)
			valid_sensors.sort();
			
			// update the first N sensors of the sorted valid_sensor list
			// N = N_req_sensors
			for (int i = 0; i < this_mission.N_req_sensors; i++) {
				s_id = index_sensors(i, valid_sensors).sensor_id;
				update_sensor(s_id, m_duration, this_mission.end);

//				to_print.push_back(lookup_by_sensor_id(s_id));
//				cout << "SENSOR " << i << " CONFLICTIONS: " << index_sensors(i, valid_sensors).conflictions << endl;
			}
//			print_sensors(to_print);
//			to_print.clear();
//			cout << endl;
		}
//		else
//		{
//			this_mission.print_details(m_index);
//			cout << "MISSION FAILED!\n";
//		}
	}
	return;
}

void AOI::update_sensor(int s_id, int m_duration, int m_end_time)
{
	list<Sensor>::iterator s_iter = s_list.begin();
	for (int i = 0; i < s_list.size(); i++) {
		if (s_iter->sensor_id == s_id) {
			s_iter->available = m_end_time + 1;
			s_iter->energy = s_iter->energy - m_duration;
			return;
		}
		s_iter++;
	}
	cout << "\nERROR!!! sensor_id: " << s_id << " was not found!!!\n";
	cout << "Updates could not be made!!!\n\n";
	return;
}

Sensor AOI::lookup_by_sensor_id(int s_id)
{
	list<Sensor>::iterator s_iter = s_list.begin();
	for (int i = 0; i < s_list.size(); i++) {
		if (s_iter->sensor_id == s_id) {
			return *s_iter;
		}
		s_iter++;
	}
	cout << "\nERROR!!! sensor_id: " << s_id << " was not found!!!\n";
	cout << "Bad sensor return!!!\n\n";
	return *s_list.end();
}

void AOI::random_algo()
{
    list<Sensor> valid_sensors, picked_sensors,to_print;
    list<Mission>::iterator m_iter;
    list<Sensor>::iterator s_iter, s_iter_2;
    Mission this_mission;
    int m_duration, s_id, num_valid_sen ,picked_index;
    
    // sorts by mission start time (earliest first)
    m_list.sort();

    for (int m_index = 0; m_index < num_mission; m_index++) {
        this_mission = index_missions(m_index);
        m_duration = this_mission.end - this_mission.start + 1;
        
        valid_sensors = find_valid_sensors(this_mission);
        if (valid_sensors.size() >= this_mission.N_req_sensors) {
            m_iter = m_list.begin();
            advance(m_iter, m_index);
            (*m_iter).mission_succeed = true;
            
            num_valid_sen = static_cast<int>(valid_sensors.size());
            for(int i=0; i<this_mission.N_req_sensors;i++)
            {
                picked_index=rand()%(num_valid_sen -i);
                picked_sensors.push_back(index_sensors(picked_index,valid_sensors));
                s_id=index_sensors(picked_index,valid_sensors).sensor_id;
                update_sensor(s_id,m_duration,this_mission.end);
                s_iter_2 = valid_sensors.begin();
                for (int i = 0; i < picked_index; i++) {
                    s_iter_2++;
                }
                s_iter=valid_sensors.begin();
                swap(*s_iter,*s_iter_2);
                valid_sensors.pop_front();
            }
            
//            (*m_iter).print_details(m_index);
//            cout << "\nRANDOMLY PICKED SENSORS\n";
//            for (int i = 0; i < this_mission.N_req_sensors; i++) {
//                
//                int s_id = index_sensors(i, picked_sensors).sensor_id;
//                to_print.push_back(lookup_by_sensor_id(s_id));
//            }
//            print_sensors(to_print);
//            to_print.clear();
            picked_sensors.clear();
//            cout << endl;
        }
//        else
//        {
//            this_mission.print_details(m_index);
//            cout << "MISSION FAILED!\n";
//
    }
    return;
}








