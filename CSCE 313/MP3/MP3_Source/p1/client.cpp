/* 
    File: client.cpp, FINISH THIS TODAY!

    Author: Dalton Harris and Ashton Binkley
            Department of Computer Science
            Texas A&M University

    Simple client main program for MP3 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

string int2string(int number) 
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

string process_request(const string & _request)
{
  if(_request.compare(0,5,"hello") == 0)
  {
    return "hello to you too";
  }

  else if(_request.compare(0,4,"data") == 0)
  {
    return (int2string(rand()%100));
  }

  else
  {
    return "No matching request .";
  }
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) 
{
  pid_t child_id;
  int num_requests = 10000;

  if((child_id = fork()) == 0) // new child process
  {
    system("./dataserver");
  }

  else
  {
    cout << "CLIENT STARTED:" << endl;

    cout << "Establishing control channel... " << flush;
    RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
    cout << "done." << endl;

    /* -- Start sending a sequence of requests */

    timeval begin, end;
    gettimeofday(&begin,NULL);
    string reply1 = chan.send_request("hello");
    gettimeofday(&end,NULL);

    timeval begin2, end2;
    gettimeofday(&begin2,NULL);
    string temp = process_request("hello");
    gettimeofday(&end2,NULL);

    cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

    timeval begin3, end3;
    gettimeofday(&begin3,NULL);
    string reply2 = chan.send_request("data Joe Smith");
    gettimeofday(&end3,NULL);

    timeval begin4, end4;
    gettimeofday(&begin4,NULL);
    string temp2 = process_request("data Joe Smith");
    gettimeofday(&end4,NULL);

    cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;


    for(int i = 0; i < num_requests; i++) 
    {
      string request_string("data TestPerson" + int2string(i));
      string reply_string = chan.send_request(request_string);
      cout << "reply to request " << i << ":" << reply_string << endl;;
    }
   
    string reply4 = chan.send_request("quit");
    cout << "Reply to request 'quit' is '" << reply4 << "'" << endl;

    double response_time_1, response_time_2, response_time_3, response_time_4;

    response_time_1 = (end.tv_usec-begin.tv_usec);
    response_time_2 = (end2.tv_usec-begin2.tv_usec);
    response_time_3 = (end3.tv_usec-begin3.tv_usec);
    response_time_4 = (end4.tv_usec-begin3.tv_usec);

    cout << "\n> Server request \"hello\" took " << end.tv_sec-begin.tv_sec << " seconds and " << response_time_1 << " milliseconds to complete" << endl;
    cout << "> Client return \"hello\" took " << end2.tv_sec-begin2.tv_sec << " seconds and " << response_time_2 << " milliseconds to complete" << endl;

    double client_server_1 = (end.tv_usec-begin.tv_usec)+(end2.tv_usec-begin2.tv_usec);

    cout << "> Server request \"data Joe Smith\" took " << end3.tv_sec-begin3.tv_sec << " seconds and " << response_time_3 << " milliseconds to complete" << endl;
    cout << "> Client return \"data Joe Smith\" took " << end4.tv_sec-begin4.tv_sec << " seconds and " << response_time_4 << " milliseconds to complete" << endl;

    double client_server_2 = (end3.tv_usec-begin3.tv_usec)+(end3.tv_usec-begin3.tv_usec);
    double average_time = (client_server_1 + client_server_2)/num_requests;

    cout << "> Number of requests: " << num_requests << endl;
    cout << "> Average response time: " << average_time << " ms" << endl;

    response_time_1 = (end.tv_usec-begin.tv_usec) / 1000;
    response_time_2 = (end2.tv_usec-begin2.tv_usec) / 1000;
    response_time_3 = (end3.tv_usec-begin3.tv_usec) / 1000;
    response_time_4 = (end4.tv_usec-begin3.tv_usec) / 1000;

    double std_dev =  (response_time_1 - average_time) * (response_time_1 - average_time) +
                      (response_time_2 - average_time) * (response_time_2 - average_time) +
                      (response_time_3 - average_time) * (response_time_3 - average_time) +
                      (response_time_4 - average_time) * (response_time_4 - average_time);

    cout << "> Standard Deviation: " << std_dev << endl;

    cout << endl;

    usleep(10000);
    return 0;
  }

}