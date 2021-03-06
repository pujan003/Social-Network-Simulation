/*
 * timekeeper.cpp
 *
 *  Created on: Oct 12, 2013
 *      Author: cs1120211
 */

/*! \file
*/
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "timekeeper.h"
#include "ipc.h"
#include "globals.h"
using namespace std;

pthread_t time_threads[2];

ofstream tiper("PartA/timekeeper.txt");
long currenttime = 0; 		//in minutes
/*! The priority queue to maintain the requets into order of their time and threadID
*/
vector<Request> request_array;
pthread_mutex_t request_mutex = PTHREAD_MUTEX_INITIALIZER;

/*! The days of simulation that the user gives as input
*/
int days_of_simulation;

bool compare(Request a, Request b) {
	if (a.request_time!=b.request_time){
		return a.request_time<b.request_time;
	}
	else{
		return a.threadID<b.threadID;
	}
}

/*! \fn Request recieveRequest()
*\brief It accepts the requests from the generator threads and places the message into Request data structure
* @param void
* @return Request the recieved message
*/
Request recieveRequest(){
	struct Request stored_struct;
	int msqid;
	key_t key1 =ftok("./PartA/setEnvironment.h", 'A');

   if (key1 == -1) {
       perror("ftok");
       exit(1);
   }

   if ((msqid = msgget(key1, 0666)) == -1) {
       //perror("msggetrrgg");
       exit(1);
   }

   if (msgrcv(msqid, &stored_struct, sizeof(Request)-sizeof(long),0,0) == -1) {  // the second is 0 since i will recieve whatever is next in the queue.
	   //perror("msgrcv");
	   exit(1);
   }
   return stored_struct;
}

/*! \fn void sendWakeUpCall(WakeUp struct_to_send)
*\brief It sends the wake up call to the generator threads via the message queue.
* @param WakeUp the message data structure to send
* @return void
*/
void sendWakeUpCall(WakeUp struct_to_send){
	int msqid1;
	key_t key2 =ftok("./PartA/setEnvironment.h", 'B');
    if (key2 == -1) {
        perror("error in ftok");
        exit(1);
    }
    // connect to a message queue and get its ID using the unique key created above.
    tiper<< "Timekeeper sending wake up"<<endl;
    if ((msqid1 = msgget(key2, 0666)) == -1) {
        //perror("error in msggetgg");
        exit(1);
    }

    if (msgsnd(msqid1, &struct_to_send, sizeof(WakeUp)-sizeof(long), IPC_NOWAIT) == -1) {
    	perror("msgsnd");
    }

}

/*! \fn void* acceptRequest(void *a)
*\brief It accepts the requests from the generator and places them into the priority queue (request_array). It is a thread.
* @param void*
* @return void*
*/
void* acceptRequest(void *a){

	while(currenttime<=days_of_simulation*24*60){
		Request b = recieveRequest();
		tiper<<"TimeKeeper :: Request received from "<<b.threadID<<" "<<b.request_time<<endl;

		pthread_mutex_lock(&request_mutex);
			request_array.push_back(b);
			sort(request_array.begin(),request_array.end(),compare);
			pthread_mutex_unlock(&request_mutex);
	}
	void * ans;
	return ans;
}

/*! \fn void* wakeUp(void* i)
*\brief It sends the wakeup calls to the generator according to order in priority queue. It is a thread running parellel with the acceptRequest()
 * function
* @param void*
* @return void*
*/
void* wakeUp(void* i ){
	wakeuplable:
	while ((request_array.size()!=0)&&(currenttime<days_of_simulation*24*60)){

		pthread_mutex_lock(&request_mutex);
		WakeUp w ;
		if (currenttime<=request_array[0].request_time){
			currenttime = request_array[0].request_time;
			w.threadID=request_array[0].threadID;
			w.request_accepted=1;
			w.current_time=currenttime;
		}
		else{
			w.threadID=request_array[0].threadID;
			w.request_accepted=0;
			w.current_time=currenttime;
		}
		// call that thread depending upon the ID using IPC
		request_array.erase(request_array.begin());
		sort(request_array.begin(),request_array.end(),compare);
		tiper<<"wake up call successfully sent to "<<w.threadID<<" ArraySize now is "<<request_array.size()<<endl;
		pthread_mutex_unlock(&request_mutex);
		if (currenttime<days_of_simulation*24*60){
					sendWakeUpCall(w);
		}
		// remove that request.
	}

	if (days_of_simulation*24*60<=currenttime){
		tiper<<"TimeKeeper Terminated itself with time "<<currenttime<<endl;
		exit(getpid());
	}
	else{
		goto wakeuplable;
	}
	void * ans;
	return ans;
}

void print(){
	int a=request_array.size();
	for (int i=0;i<a;i++){
		tiper<<request_array[0].request_time<<" "<<request_array[0].threadID<<endl;
		request_array.erase(request_array.begin());
	}
}


/*! \fn int timeInit(int h)
*\brief It starts the two threads, wakeUp() and acceptRequest().
* @param int days of simulation
* @return int returns 0 on succesfull completion
*/
int timeInit(int h){
	int rc;
	void *exitstatus;
	days_of_simulation=h;
	for(int u=0;u<2;u++){
		rc=pthread_create(&time_threads[u], NULL, (u==0?&acceptRequest:wakeUp), NULL);
		if(rc){
			printf("Could not create thread\n");
			return -1;
		}
	}
	pthread_join( time_threads[0], NULL);
	pthread_join(time_threads[1], NULL);
	pthread_mutex_destroy(&request_mutex);
	return 0;
}

int main(int argc, char** argv){
	timeInit(atoi(argv[1]));
	return 0;
}







