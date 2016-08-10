/* 
    File: requestchannel.cpp

    Author: Dalton Harris
            Department of Computer Science
            Texas A&M University
    Date  : 2016/05/01

*/

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include "reqchannel.h"

using namespace std;

struct sockaddr_in server_socket;

// DEFINES THE CLIENT SIDE
int createClientConnection(const char * host, const char * portNo)
{
  struct sockaddr_in input_socket;
  memset(&input_socket, 0, sizeof(input_socket));
  input_socket.sin_family = AF_INET;

  if(struct servent * pse = getservbyname(portNo, "tcp"))
  {
    input_socket.sin_port = pse->s_port;
  }

  else if ((input_socket.sin_port = htons((unsigned short)atoi(portNo))) == 0)
  {
    cout << "Error: cant connect port\n";
  }
   
  if(struct hostent * hn = gethostbyname(host))
  {
    memcpy(&input_socket.sin_addr, hn->h_addr, hn->h_length);
  }  
    
  else if((input_socket.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
  {
    cout << "Error: cant determine host <" << host << ">\n";
  }  

  int s = socket(AF_INET, SOCK_STREAM, 0);
  if(s < 0)
  {
    cout << "Error: cant create socket\n";
  }  

  if(connect(s, (struct sockaddr *)&input_socket, sizeof(input_socket)) < 0)
  {
    cout << "Error: cant connect to " << host << ":" << portNo;
  }  
    
  return s;
}

// DEFINES THE SERVICE SIDE LISTENER
int createServerConnection(const char * svc, int backlog)
{

  memset(&server_socket, 0, sizeof(server_socket));
  server_socket.sin_family = AF_INET;
  server_socket.sin_addr.s_addr = INADDR_ANY;

  if(struct servent * pse = getservbyname(svc, "tcp"))
  {
    server_socket.sin_port = pse->s_port;
  }  
    
  else if((server_socket.sin_port = htons((unsigned short)atoi(svc))) == 0)
  {
    cout << "Error: can't get port\n";
  }  

  int socknum  = socket(AF_INET, SOCK_STREAM, 0);

  if(socknum < 0)
  {
    cout << "Error: can't create socket \n";
  }  
    
  if(bind(socknum, (struct sockaddr *)&server_socket, sizeof(server_socket)) < 0)
  {
    cout << "Error: can't bind...\n";
  }  
    
  listen(socknum, backlog);

  return socknum;
}


NetworkRequestChannel::NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no)
{
  stringstream ss;
  ss << _port_no;
  string port = ss.str();

  file_ds = createClientConnection(_server_host_name.c_str(), port.c_str());
}

NetworkRequestChannel::NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (void *), int backlog)
{
  stringstream ss;
  ss << _port_no;
  string port = ss.str();

  int master = createServerConnection(port.c_str(), backlog);
  int serverSize = sizeof(server_socket);


  while(true)
  {
    int * service_int = new int;

    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    *service_int = accept(master,(struct sockaddr*)&server_socket, (socklen_t*)&serverSize);

    if(service_int < 0)
    {
      delete service_int;

      if(errno == EINTR)
                continue;
      else cout << "Error: unknown error in accept()\n";
    }

    pthread_create(&thread, &attr, connection_handler, (void*)service_int);


  }
  cout << "Connection complete\n";
}

NetworkRequestChannel::~NetworkRequestChannel()
{
  close(file_ds); 
}

const int MAX_MSG = 255;

int NetworkRequestChannel::read_fd()
{
  return file_ds;
}

string NetworkRequestChannel::cread()
{
  char buf[MAX_MSG];

  if (read(file_ds, buf, MAX_MSG) < 0)
  {
    cout<<"Error reading\n";
  }  

  string s = buf;

  return s;
}

int NetworkRequestChannel::cwrite(string _msg)
{
  if (_msg.length() >= MAX_MSG) 
  {
    cout << "Error: Message too long for Channel!\n";
    return -1;
  }

  const char * s = _msg.c_str();

  if (write(file_ds, s, strlen(s)+1) < 0)
  {
    cout<<"Error writing\n";
  }  
  
}