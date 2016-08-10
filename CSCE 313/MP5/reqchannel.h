/* 
    File: requestchannel.h

    Author: Dalton Harris
            Department of Computer Science
            Texas A&M University
    Date  : 2016/05/01

*/

#ifndef _NETWORKREQUESTCHANNEL_H_
#define _NETWORKREQUESTCHANNEL_H_

#include <iostream>
#include <fstream>
#include <string>
#include "semaphore.h"

using namespace std;

class NetworkRequestChannel {

private:
  int file_ds; // socket file descriptor;

public:
  NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no);
  NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (void *), int backlog);

  ~NetworkRequestChannel();

  string cread();
  int cwrite(string _msg);
  int read_fd();

};

#endif