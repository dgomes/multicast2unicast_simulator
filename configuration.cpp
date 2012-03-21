#include "configuration.h"

/*
 *	Configuration
 */
configuration::configuration() {
};

configuration::configuration(string file) {
	try {
		read_conf(CONFIG_FILE);
	} catch (...) {
		cerr << "Problems trying to read " << CONFIG_FILE << endl;
	}
}

configuration &configuration::operator[](string s) {
	configuration &c = conf[s];
	if(path.size())
		c.path = path + "." + s;
	else
		c.path = s;
	return c;
}

const string configuration::value(const string default_value) throw(configuration_exception) {
	if (data.size()==0 && !default_value.empty()) {
		cerr << BOLD << "Using default value for "<< path << ": " << RESET << default_value << endl;
		return default_value;
	}
	return data;
}

const int configuration::value(const int default_value) throw(configuration_exception) {
	std::stringstream s_default_value;
	s_default_value << default_value;
	return atoi(value(s_default_value.str()).c_str());
}

const double configuration::value(const double default_value) throw(configuration_exception) {
	std::stringstream s_default_value;
	s_default_value << default_value;
	return atof(value(s_default_value.str()).c_str());
}

const bool configuration::enabled() throw(configuration_exception) {
	if((value("true")==string("true")) || value("1")==string("1") || value("enabled")==string("enabled")) return true;
	return false;
}
const bool configuration::disabled() throw(configuration_exception) {
	if((value("false")==string("false")) || value("0")==string("0") || value("disabled")==string("disabled")) return true;
	return false;
}

void configuration::read_conf(std::string file) {
	std::ifstream conf_file(file.c_str());
	string temp;
	unsigned index = 1;
	cerr << "Reading Conf file <"<< file << "> ... " << flush;
	#ifdef DEBUG_MAX
	cerr << endl;
	#endif
	while (!conf_file.eof()) {
		configuration *c = NULL;
		try {
			getline(conf_file,temp);
			temp = temp.substr(0,temp.find("#"));
			if (temp=="") continue;
			string val = temp.substr(temp.find("=")+1,string::npos);
			unsigned separator=temp.find("=");
			unsigned pos=0;
			while (pos!=string::npos && pos < separator) {
				string prop = temp.substr(0,temp.find("."));
	#ifdef DEBUG_MAX
				cerr << prop << ".";
	#endif
				if (c==NULL) {
					c = &conf[prop];
				} else {
					configuration *t;
					t = c;
					c = &c->conf[prop];
				}
				c->path = prop;

				if(temp.substr(0,temp.find("=")).find(".")==string::npos) break; // look for . before = if cannot find break
				temp = temp.substr(temp.find(".")+1,string::npos);
				pos = temp.find(".");
				separator=temp.find("=");
			}
			string prop = temp.substr(0,temp.find("="));
			if(prop == string("$")) {
				stringstream ss;
				index = 1;
				ss << index++;
				ss >> prop;
			}
			if(prop == string("%")) {
				stringstream ss;
				ss << index++;
				ss >> prop;
			}
				
	#ifdef DEBUG_MAX
			cerr <<  prop << "\t\t=\t" << val << endl;
	#endif
			if (c==NULL) {
				conf[prop].data=val;
				conf[prop].path=prop;
			} else {
				(c->conf[prop]).data=val;
				(c->conf[prop]).path= prop;
			}
		} catch (std::exception e)  {
			break;
		} catch (...) {
			cerr << "Error reading line: " << temp  << endl;
		}
	}
	cerr << "(done)" << endl;
	conf_file.close();

};

configuration::~configuration() {
};

