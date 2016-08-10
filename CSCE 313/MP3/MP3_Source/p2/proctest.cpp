#include <sstream>
#include <cctype>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

enum index {PID, COMM, STATE, PPID, PGRP, SESSION, TTY_NR, TPGID, FLAGS, MINFLT, CMINFLT, 
				   MAJFLT, CMAJFLT, UTIME, STIME, CUTIME, CSTIME, PRIORITY, NICE, NUM_THREADS,
				   ITREALVALUE, STARTTIME, VSIZE, RSS, RSSLIM, STARTCODE, ENDCODE, STARTSTACK,
				   KSTKESP, KSTKEIP, SIGNAL, BLOCKED, SIGIGNORE, SIGCATCH, WCHAN, NSWAP, ONSWAP,
				   EXIT_SIGNAL, PROCESSOR, RT_PRIORITY, POLICY, DELAYACCT_BLKIO_TICKS, GUEST_TIME,
				   CGUEST_TIME};

				   
bool is_valid(string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		char buff = s[i];
		if(buff < 48 || buff > 57)
		{
			return false;
		}
	}

	return true;
}

string to_lower(string s)
{
	for (int i=0; s[i]; i++) 
	{
		s[i] = tolower(s[i]);
	}

	return s;
}

string int2string(int number) 
{
   stringstream ss;
   ss << number;
   return ss.str();
}

vector<string> &split(const string &s, char delim, vector<string> &element_vec) 
{
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) 
    {
        if (item.length() > 0) 
        {
            element_vec.push_back(item);  
        }
    }

    return element_vec;
}


vector<string> split(const string &s, char delim) 
{
    vector<string> element_vec;
    split(s, delim, element_vec);
    return element_vec;
}

int run_pid()
{
	cout << endl << "---- Process Examinations Application ----" << endl;
	cout << "Usage: " << endl;
	cout << "  <ls>     lists processes" << endl;
	cout << "  <quit>   quits application" << endl;
	cout << "  <clear>  clears window" << endl;

	cout << "\nInput Process ID: ";

	string input;
	cin >> input;

	system("clear");

	cout << endl;

	input = to_lower(input);

	if(input == "ls")
	{
		system("ls /proc");
		return run_pid();
	}

	else if(input == "quit")
	{
		cout << "Program terminated" << endl;
		return -1;
	}

	else if(input == "clear")
	{
		system("clear");
		return run_pid();
	}

	else if(is_valid(input))
	{
		int pid = atoi(input.c_str());
		return pid; 
	}

	else
	{
		cout << "Eror: Invalid input \n";
		return run_pid();
	}
	
}

int main(int argc, char * argv[]) 
{
	int pid = run_pid();
	
	while(pid != -1)
	{
		ifstream stat;
		ifstream status;
		ifstream maps;

		stat.open("/proc/" + int2string(pid) + "/stat");
		status.open("/proc/" + int2string(pid) + "/status");

		if(stat && status)
		{
			string raw;
			string buff;

			while(getline(stat, buff))
			{
				raw += buff;
			}

			istringstream iss(raw);
			istream_iterator<string> beg(iss), end;
			vector<string> stat_val(beg, end);
					
			//raw = "";
			vector<vector <string> > status_val;
			
			while(getline(status, buff))
			{
				vector<string> split_vector = split(buff, ':');
				string info = split_vector[1];
				istringstream iss2(info);
				istream_iterator<string> beq(iss2), end;
				vector<string> buff_vec(beq, end);
				status_val.push_back(buff_vec);
				raw += buff + '\n';
			}

		// Identifiers
			cout << "------------------------------------------------" << endl;
			cout << "PID = " << stat_val.at(PID) << endl;
			cout << "PPID = " << stat_val.at(PPID) << endl;
			cout << "EUID = " << status_val.at(6).at(1) << endl;
			cout << "EGID = " << status_val.at(7).at(1) << endl;
			cout << "RUID = " << status_val.at(6).at(0) << endl;
			cout << "RRGID = " << status_val.at(7).at(0) << endl;
			cout << "FSUID = " << status_val.at(6).at(3) << endl;
			cout << "FSGID = " << status_val.at(7).at(3) << endl;
			
		// State
			cout << "------------------------------------------------" << endl;
			string stat_val_at_state = stat_val.at(STATE);
			cout << "STATE = " << stat_val_at_state << endl;
			
		// Thread Information
			cout << "------------------------------------------------" << endl;
			cout << "NUM_THREADS = " << stat_val.at(NUM_THREADS) << endl;	
			
		// Priority
			cout << "------------------------------------------------" << endl;
			cout << "PRIORITY = " << stat_val.at(PRIORITY) << endl;
			cout << "NICE = " << stat_val.at(NICE) << endl;
			
		// Time Information
			cout << "------------------------------------------------" << endl;
			cout << "STIME = " << stat_val.at(STIME) << endl;
			cout << "UTIME = " << stat_val.at(UTIME) << endl;
			cout << "CSTIME = " << stat_val.at(CSTIME) << endl;
			cout << "CUTIME = " << stat_val.at(CUTIME) << endl;
			
		// Address Space
			cout << "------------------------------------------------" << endl;
			cout << "STARTCODE = " << stat_val.at(STARTCODE) << endl;
			cout << "ENDCODE = " << stat_val.at(ENDCODE) << endl;
			cout << "KSTKESP = " << stat_val.at(KSTKESP) << endl;
			cout << "KSTKEIP = " << stat_val.at(KSTKEIP) << endl;
			
		// Resources
			cout << "------------------------------------------------" << endl;
			cout << "FDSize = " << status_val.at(8).at(0) << endl;
			cout << "voluntary_ctxt_switches = " << status_val.at(37).at(0) << endl;
			cout << "nonvoluntary_ctxt_switches = " << status_val.at(38).at(0) << endl;
			
		// Processors
			cout << "------------------------------------------------" << endl;
			cout << "Cpus_allowed = " << status_val.at(33).at(0) << endl;
			cout << "PROCESSOR = " << stat_val.at(PROCESSOR)  << endl;
			
		}

		else
		{
			cout << "ERROR: pid " << pid << " could not be opened" << endl;
			cout << "Note: This process may not exist, enter 'ls' to find available processes" << endl;
		}
		
		cout << "------------------------------------------------" << endl;
		cout << "Accessing Memory Map: " << endl;
		maps.open("/proc/" + int2string(pid) + "/maps");
		
		if(maps)
		{
			string buff;
			string raw = "";
			int i = 0;

			while(getline(maps, buff) && i < 3)
			{
				raw += buff + '\n';
				i++;
			}

			if(raw == "")
			{
				cout << "Memory map empty\n";
			}

			else
			{
				cout << "------------------------------------------------" << endl;
				cout << raw << endl << endl;
				ofstream out;
				out.open("out.txt");
				out << raw;
				out.close();
			}

		}

		else
		{
			cout << "Error: Memory map could not be processed\n";
			cout << "Note: process may not be running\n";
		}
		
		stat.close();
		status.close();
		maps.close();

		cout << endl << "   Enter anything to try again. " << endl;
		cout << "   Enter 0 to exit application. " << endl;

		string run_again;
		cin >> run_again;

		if(run_again == "0")
		{
			pid = -1;
		}

		else
		{
			system("clear");
			pid = run_pid();
		}
	}
	
	cout << "Program terminated." << endl;
	return 0;
}