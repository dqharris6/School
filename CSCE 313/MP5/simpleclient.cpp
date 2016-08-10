/* 
    File: simpleclient.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2013/01/31

    Simple client main program for MP3 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <iomanip>

#include <iostream>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"
#include "boundedbuffer.h"

using namespace std;

//requests
int count_john = 0;
int count_joe = 0;
int count_jane = 0;

//histograms
vector<int> histogram_john(100);
vector<int> histogram_joe(100);
vector<int> histogram_jane(100);

//default args
int num_req = 10000;
int work_threads = 15;
int size_of_buffer = 500;

//boundedbuffer
boundedbuffer* buff;
boundedbuffer* buff_john;
boundedbuffer* buff_joe;
boundedbuffer* buff_jane;

int* john = new int(0);
int* joe = new int(1);
int* jane = new int(2);

//print histogram
void histogram(vector<int> processes, string thread_name)
{
  vector<int> temp(10); // vector sets intervals at 10

  for(int i=0; i<temp.size(); ++i)
  {
    for(int j=0; j<temp.size(); ++j)
    {
      temp[i] = temp[i] + processes[i+j*10]; // populates temp vector with histogram data
    }
  }

  int sum;
  
  for(int k=0; k<10; ++k)
  {
    cout << 10*k << "-" << 10*(k+1)-1;
    cout << setw(10) << temp[k] << endl; 
    sum += temp[k];

    cout <<"Histogram total: " << sum << endl;

  }




  cout << endl;

}

void* thread_request(void* indiv_id)
{
  int id = *((int*)indiv_id);

  for(int i = 0; i < num_req; i++)
  {
    String_out* r = new String_out("test", id, 0);

    if(id == 0)
    {
      count_john++;
      r->counter = count_john;
      r->ds_response = "data John Doe";
      r->client_request = 0;
    }
    else if(id == 1)
    {
      count_joe++;
      r->counter = count_joe;
      r->ds_response = "data Joe Smith";
      r->client_request = 1;
      cout << "Found non zero" << endl;
    }
    else if(id == 2)
    {
      count_jane++;
      r->counter = count_jane;
      r->ds_response = "data Jane Smith";
      r->client_request = 2;
    }
    //add to buffer
    buff-> my_push(*r);
    delete r;
  }
  cout << "Request ID: " << id << endl;
  cout << "Status: Requests Completed" << endl;
  cout << "Exiting..." << endl;
}

void* event_request(void* c)
{
    RequestChannel* r_channels[work_threads];
    int indiv_id[work_threads];

    //file desciptor read
    fd_set read_des; 
    int max_num = 0;
    int select_res;

    String_out r = String_out("", 0,0);
    bool finish = false;
    int work_count = 0;
    int r_count = 0;
    struct timeval time_eval = {0,10};

    RequestChannel chan("control", RequestChannel::CLIENT_SIDE);

    for(int i = 0; i < work_threads; i++)
    {
        string reply = chan.send_request("newthread");
        r_channels[i] = new RequestChannel(reply, RequestChannel::CLIENT_SIDE);
        //initialize to negative so not a real request
        indiv_id[i] = -1;
    }

    for(int i = 0; i < work_threads; i++)
    {
        //fill channels
        r = buff->my_pop();
        work_count++;
        r_channels[i]->cwrite(r.ds_response);
        indiv_id[i] = r.client_request;
    }

    while(!finish)
    {
        FD_ZERO(&read_des);
        
        for(int i = 0; i < work_threads; i++)
        {
            if(r_channels[i]->read_fd() > max_num)
            {
                max_num = r_channels[i]->read_fd();
            }
            FD_SET(r_channels[i]->read_fd(), &read_des);
        }

        select_res = select(max_num+1, &read_des, NULL, NULL, &time_eval);

        if(select_res)
        {
            for(int i=0; i<work_threads; i++)
            {
                if(FD_ISSET(r_channels[i]->read_fd(), &read_des))
                {
                    string serv_resp = r_channels[i]->cread();
                    r_count++;
                    switch(indiv_id[i])
                    {
                    case 0:
                        buff_john->my_push(String_out(serv_resp, 0, 0));
                        break;
                    case 1:
                        buff_joe->my_push(String_out(serv_resp, 1, 0));
                        break;
                    case 2:
                        buff_jane->my_push(String_out(serv_resp, 2, 0));
                        break;
                    }

                    if(work_count < num_req*3)
                    {
                        r = buff->my_pop();
                        work_count++;
                        // cout << "writing\n";
                        r_channels[i]->cwrite(r.ds_response);
                        indiv_id[i] = r.client_request;
                    }
                }
            }
        }

        if(r_count == num_req*3) //if all reads complete break
        {
            break;
        }
    }

    //close 
    for(int i = 0; i < work_threads; i++)
    {
        r_channels[i]->send_request("quit");
    }
    chan.send_request("quit");
}

/*void* thread_worker(void* channel)
{
  RequestChannel* request_channel = (RequestChannel*) channel;
  String_out r("",0,0);

  int count = 0;

  while (1)
  {
    r = buff->my_pop();

    //exit
    if(r.ds_response == "kill")
    {
      break;
    }

    string response = request_channel->send_request(r.ds_response);
    r.ds_response = response;

    if(r.client_request == 0)
    {
      buff_john->my_push(r);
    }
    else if(r.client_request == 1)
    {
      buff_joe->my_push(r);
    }
    else if(r.client_request == 2)
    {
      buff_jane->my_push(r);
    }
  }

  request_channel->send_request("quit");
}*/


void* thread_statistic(void *indiv_id)
{
  int id = *((int*)indiv_id);

  String_out r("test", -1, -1);

  for(int i = 0; i < num_req; i++)
  {
    if (id == 0)
    {
      r = buff_john->my_pop();

      //incriment histogram
      histogram_john[atoi(r.ds_response.c_str())]+=1;
      cout << "r.ds_response" <<r.ds_response << endl;
    }
    else if (id == 1)
    {
      r = buff_joe->my_pop();

      //incriment histogram
      histogram_joe[atoi(r.ds_response.c_str())]+=1;
    }
    else if (id == 2)
    {
      r = buff_jane->my_pop();

      //incriment histogram
      histogram_jane[atoi(r.ds_response.c_str())]+=1;
    }
  }
  cout << "Request ID: " << id << endl;
  cout << "Status: Statistics Thread Completed" << endl;
  cout << "Exiting..." << endl;
}





int main(int argc, char * argv[]) {

  int c = 0;
  while((c = getopt (argc, argv, "n:w:b:"))!= -1)
  {
    switch(c) 
    {
      case 'n':
        num_req = atoi(optarg);
        break;

      case 'w':
        work_threads = atoi(optarg);
        break;

      case 'b':
        size_of_buffer = atoi(optarg);
        break;

      case '?':
        cout << "Exiting..." << endl;
        abort();
      
      default:
        cout << "Error" << endl;
        cout << "Please enter N=# W=# B=#" << endl;
        abort();
    }
  }
    

  //initializing arguments
  pthread_t thread_requests[3];
  pthread_t event_handler;
  // thread_workers[work_threads];
  pthread_t thread_statistics[3];

  buff = new boundedbuffer(size_of_buffer);
  buff_john = new boundedbuffer(size_of_buffer);
  buff_joe = new boundedbuffer(size_of_buffer);
  buff_jane = new boundedbuffer(size_of_buffer);

  pid_t server;
  if((server = fork()) == 0)
  {
    execl("./dataserver", NULL, NULL);
  }
  else
  {
    cout << "CLIENT STARTED:" << endl;

    cout << "Establishing Control Channel... " << flush;
    RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
    cout << "Finished" << endl;

    timeval start, stop;
    gettimeofday(&start, NULL);

    cout << "Starting Thread Creation..." << endl;
    pthread_create(&thread_requests[0], NULL, thread_request, (void*)john);
    pthread_create(&thread_requests[1], NULL, thread_request, (void*)joe);
    pthread_create(&thread_requests[2], NULL, thread_request, (void*)jane);

    /*cout << "Starting Worker Threads..." << endl;
    for(int i = 0; i < work_threads; i++) 
    {
      string reply = chan.send_request("newthread");
      RequestChannel* request_channel = new RequestChannel(reply, RequestChannel::CLIENT_SIDE);
      
      pthread_create(&thread_workers[i], NULL, thread_worker, request_channel);
    }*/

    cout << "Creating event handler..." << endl;
    pthread_create(&event_handler, NULL, event_request, NULL);

    cout << "Starting Statistics Threads..." << endl;
    pthread_create(&thread_statistics[0], NULL, thread_statistic, (void*)john);
    pthread_create(&thread_statistics[1], NULL, thread_statistic, (void*)joe);
    pthread_create(&thread_statistics[2], NULL, thread_statistic, (void*)jane);

    pthread_join(thread_requests[0], NULL);
    pthread_join(thread_requests[1], NULL);
    pthread_join(thread_requests[2], NULL);

    //killing
    /*String_out kill("kill", -5, -5);
    cout << "Killing..." << endl;
    for(int i = 0; i < work_threads; i++)
    {
      buff-> my_push(kill);
    }
    for(int i = 0; i < work_threads; i++)
    {
      pthread_join(thread_workers[i], NULL);
    }*/

    cout << "Waiting for Event Handler to finish..." << endl;
    pthread_join(event_handler,NULL);

    //exiting
    pthread_join(thread_statistics[0], NULL); 
    pthread_join(thread_statistics[1], NULL);
    pthread_join(thread_statistics[2], NULL);

    gettimeofday(&stop, NULL);

    chan.send_request("quit");
    sleep(1);

    //print histogram
    histogram(histogram_john, "John Smith");
    histogram(histogram_joe, "Joe Smith");
    histogram(histogram_jane, "Jane Smith");


    cout << "-------------------------------------------" << endl;
    cout << "Requests Total: " << num_req*3 << endl;
    cout << "Worker Threads Total: " << work_threads << endl;
    cout << "Request Time Total: " << stop.tv_sec-start.tv_sec<<" sec "<<stop.tv_usec-start.tv_usec<<" musec"<<endl;
    cout << "-------------------------------------------" << endl;

    return 0;

  } //end of if-else
} //end of main
