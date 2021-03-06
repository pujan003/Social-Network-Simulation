/*
 * Generator.h
 *
 *  Created on: Oct 8, 2013
 *      Author: cs1120255
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include<ctime>
#include <stdlib.h>
#include "setEnvironment.h"
#include "setEnvironment.h"

using namespace std;

/*! \brief It contains all the generator threads as its functions. 
*
*/
class Generator{
public:
	void * generateFaculty(void*);		//Generates Faculty
	void * generateStudent(void*);		//Generates Students
	void * generateCourses(void*);		//Generates Courses
	void * generateFriends(void*);		//Generates Friends
	int init(const char*,int);

};


#endif /* GENERATOR_H_ */
