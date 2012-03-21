#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define CONFIG_FILE "config.cfg"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <exception>
#include <string>
#include <map>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sstream>
#include "utils.h"

using namespace std;

class configuration_exception
{
	public:
		configuration_exception() {};
		~configuration_exception() {};
};


class configuration
{
	public:
		configuration();
		configuration(string file);
		void read_conf(string file);
		~configuration();
		configuration &operator[](string s);
		const string value(const string default_value) throw(configuration_exception);
		const int value(const int default_value) throw(configuration_exception);
		const double value(const double default_value) throw(configuration_exception);
		const bool enabled() throw(configuration_exception); 
		const bool disabled() throw(configuration_exception); 
		const unsigned size() {
			return conf.size();
		};
	protected:
		map<string,configuration> conf;
		string path;
		string data;
};

#endif // _CONFIGURATION_H_
