/*
 * setEnvironment.h
 *
 *  Created on: Oct 8, 2013
 *      Author: cs1120255
 */
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "network.h"

using namespace std;

#ifndef setEnvironment_H_
#define setEnvironment_H_

struct University;	//University struct - contains data of a University
struct GraphNode;		//GraphNode struct - contains data of student and faculty node

/*! \brief Contains data of a Course such as its name, frequency, intructor node and the department that offers it
*/
typedef struct Course{	
	string course_name;
	string dept_that_offers;
	float frequency_per_year;
	GraphNode* instructor;
}Course;

/*! \brief Contains data of an Interest such as its name and its popularity
*/
typedef struct Interest{	// 
	string interest_name;
	float popularity;
}Interest;

/*! \brief Contains data of a Department such as its name, the university it belongs to, number of faculty and students.
*
*
*/
typedef struct Department{   // Department - contains data of a Department
	string dept_name;
	University * dep_univ;
	int num_faculty;
	int num_students_per_year;
	float semester_dept_courses;
	float semester_nondept_courses;
	/*! 
	*List of the faculty nodes (pointers to the GraphNode corresponding to that faculty)
	*/
	vector<GraphNode*> faculties;
	/*! 
	*List of the courses the department offers
	*/
	vector<Course> course_array;
	/*!
	* List of the courses floated that semester (pointers to the corresponding course data structure)
	*/
	vector<Course*> floated_courses;
}Department;

/*! 
* \brief Conatins all the data about the departments, interests, hostels, etc that it reads from the file.
*/
typedef struct University{	//University struct - contains data of a University
	string university_name;
	vector<Department> department_array;
	vector<Interest> interest_array;
	vector<string> hostel_name;
	vector<string> locality_name;
	float friendship_rate;
	float openness;
	float friendliness;

}University;

/*! \brief contains data of a random for faculty, student, course and friend
*/
typedef struct Randomseed{	
	int faculty_random;
	int student_random;
	int course_random;
	int friend_random;
}Randomseed;

/*! \brief Contains the data about the whole environment. Contains the array of University given in the input file and the Randomseed 
*/
typedef struct UniversityRandomseedTuple{	
	vector<University > university_array;
	Randomseed randomseed;

}UniversityRandomseedTuple;

/*! \brief Exposes all the functions that it needs to read the input file and place the data into the correct data structures.
*/
class SetEnvironment{
public:
	/*! \brief It reads the file and puts the entire data into one string
	* @param const char* the input filename
	* @return string 
	*/
	string fileRead(const char*);	
	/*! \brief Breaks file in blocks containing particular University
	* @param string corresponding to that university
	* @return University data structure filling it with required data
	*/	
	University makeUniversity(string); 
	/*! \brief Reads data from a block of a university and modifies the UniversityRandomseedTuple
	* @param string corresponding to a particular university
	* @return UniversityRansomseedTuple containing the data about a particualr university
	*/
	UniversityRandomseedTuple separteUniversities(string);
	/*! \brief print function to just to check if the input file parsing is done properly and the data is being placed at the correct data 		*	structure
	* @param UniversityRandomseedTuple the data structure to check with
	* @return void
	*/	
	void print(UniversityRandomseedTuple);
	/*! \brief The final function that sets the environment from the given file
	* @param const char* the input filename
	*@return UniversityRansomseedTuple contains all the data from the input file
	*/
	UniversityRandomseedTuple setEnvironment(const char*); 
};

#endif /* setEnvironment_H_ */
