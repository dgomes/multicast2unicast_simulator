/*
 *  Service.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "Service.h"

Service::Service(unsigned bw, ServiceType t, std::string n) : bandwidth(bw), type(t), name(n) {

};

std::ostream &operator<<(std::ostream &o, Service &s) {
/*	for(std::list<Subscriber *>::iterator i = s.subscribers.begin(); i!=s.subscribers.end(); ++i)
		o << ":: " << **i;*/
	o << "Service <" << s.name << "> uses " << s.bandwidth/1000.0 << "mbits/s in ";
	switch(s.type) {
		case unicast: 
			o << "unicast";
			break;
		case multicast:
			o << "multicast";
			break;
	}
	return o;
}
