# Algorithms_Proj
*Group project for CS 2500 (Algorithms)
Authors: Trevor Ross and Yizheng Wang*

##Implementation 
###Classes
Our program consists of three classes:
* Sensor
* Mission
* AOI
The sensor class holds all the necessary information for each sensor such as the sensor’s coordinates, its energy level, the sensor’s unique ID, the time at which it will become available, and the number of conflictions it has with other missions.

The mission class contains the mission’s coordinates, the number of sensors it requires to succeed, its radius, its start time and its end time, and whether or not it succeeded.

The AOI class is the largest by far. It contains a list of all the sensors and missions in the AOI as well as information specific to the AOI itself such as its size and the number of sensors and missions it contains.
###Data Structures
Lists are the most prevalent data structure in our program. All the missions and sensors are stored in m_list and s_list, respectively. This allows us to add as many or as few missions or sensors as we need without fear of running out of room in a static array. Lists also have several built in functions that make managing the s_list or m_list much easier. For example, to sort the m_list by mission start time, you can just type m_list.sort();. This is possible because of the “operator <” is overloaded for the mission class. The same operator is also overloaded for the sensor class only it allows the sensors to be sorted by number of conflictions as well as the energy level.  
###Structure
The structure of our program is class based. The AOI class contains all the important  functions: 
Functions that assign sensors to missions (greedy algorithms as well as the random function). As well as the find_valid_sensors function which returns a list of sensors that are within the range of the mission’s epicenter. 
Pseudo getter/modifier functions that return sensors or missions based on a given index or unique identifier (mission index, sensor index, find sensor by id, update sensor).
Functions that print data or format data for printing (print AOI details, print sensor statistics, mission success rate, percentage of sensors under 10 energy level. 
The AOI class also contains the other two classes in the form of a list of sensors (s_list) and a list of missions (m_list). This means our program has a sort of a hierarchical structure, with the AOI containing the other two classes. 

###Process
Fist an AOI is created. Initialized with a certain number of missions and sensors. Each mission and sensor is initialized as well. All the initializations are guided by what attributes were passed when the AOI was declared. For example: AOI a1(100, 50, 5, 2); will create a new AOI named a1 with 100 sensors and 50 missions. Each mission will have a duration of 5 and require 2 sensors to succeed. The position for each mission and sensor are randomly chosen within the range of the AOI’s parameters. The start time of the missions is also randomly assigned. After all these initializations occur for each sensor and mission then the AOI is fully initialized. 
Next one of three algorithms will be called on the AOI (online greedy, offline greedy, or random). Each of these algorithms has a different method of assigning sensors to each mission. These methods are discussed in detail in the next section. However, regardless of which algorithm is chosen, the missions will be sorted based on start time (earliest first).  Next, all missions will be iterated through. For each mission, all available, valid sensors in the AOI will be selected for that mission. From there each algorithm will select a set of optimal sensors, the criteria which the optimal sensors much meet is different for each algorithm. Finally, the sensors are updated (every level is decreased and the time at which the sensor will become available is pushed back). After each mission is either assigned the proper amount of sensors or cannot find enough valid sensors, it is marked as succeed or fail. After all missions are iterated through, the results are printed. 

