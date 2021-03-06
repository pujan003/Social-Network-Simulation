#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/*!
* \brief The data structure that the generator threads send to the timekeeper as a request via the message queue.
*/

struct Request{
	/*!
	*  A unique long number in the Request structure as per required in sending and recieving structure via the message queue.
       *for threadID
	 *1. generateFaculty
	 *2. generateStudents
	 *3. generateCourses
	 *4. generateFriends
	*/

	long threadID;  

	/*! 
	* the waking up time as given by the thread to the timekeeper
 	*/	
	long request_time;
	


};
/*!
* \brief The data structure that the timekeeper sends to the generator as a wake up call via the message queue.
*/
 struct WakeUp{
	/*!
	*  A unique long number in the Request structure as per required in sending and recieving structure via the message queue.
       *for threadID
	 *1. generateFaculty
	 *2. generateStudents
	 *3. generateCourses
	 *4. generateFriends
	*/
	long threadID;  

	/*!
	*whether the request send by the thread corresponding to the threadID is accepted by the timekeeper.
	*/
	bool request_accepted; 

	/*! the current time of the timekeeper
	*/

	long current_time;
	
};


