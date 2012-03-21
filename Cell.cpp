/*
 *  Cell.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "Cell.h"
#include <iomanip>

Cell::Cell(Coordinate &c, double r) : unicast_served(0),unicast_denied(0),multicast_served(0),multicast_denied(0),multicast_services(0) {
	radius = r;
	center = c;
}

std::ostream &operator<<(std::ostream &o, Cell &c) {
	o << c.type << " @ " << c.center << " ± ";
	o << std::fixed << std::setprecision(3);
	o << c.radius << "km ";
	//for(std::list<Terminal *>::iterator i = c.clients.begin(); i!=c.clients.end(); ++i)
	//	o << "\t" << **i << endl;
	o << "bw avail: " << c.bandwidth/1000.0 << "mbit/s , " << c.broadcast_bandwidth/1000.0  << "mbit/s";
	return o;
}

bool Cell::request(Service *s, Subscriber *t) {
	P_DEBUG_MAX("Cell::request()");
	switch(s->getServiceType()) {
		case unicast:
			if(bandwidth-s->getBandwidth() >= 0) {
				bandwidth-=s->getBandwidth();
				unicast_served++;
				return true;
			} else { 
				unicast_denied++;	
				return false;
			}
			break;
		case multicast:
			std::pair<std::multimap<Service *,Subscriber *>::iterator,std::multimap<Service *,Subscriber *>::iterator> ret;

			//Search for the Service
			ret = mc_served.equal_range(s);
			for(std::multimap<Service *,Subscriber *>::iterator i = ret.first; i!=ret.second; ++i) {
					P_DEBUG_MAX("Some already being mc_served with that service!");
					mc_served.insert(std::pair<Service *,Subscriber *>(s,t));
					multicast_served++;
					return true;
				}
			//We need to instantiate the service
			if(broadcast_bandwidth-s->getBandwidth() >= 0 && bandwidth-s->getBandwidth() >= 0) {
				broadcast_bandwidth-=s->getBandwidth();
				bandwidth-=s->getBandwidth();
				mc_served.insert(std::pair<Service *,Subscriber *>(s,t));
				multicast_services++;
				multicast_served++;
				return true;
			} else {
				multicast_denied++;
				return false;
			}
			break;
	}
	return false;
}

bool Cell::free(Service *s, Subscriber *t) {
	switch(s->getServiceType()) {
		case unicast:
			bandwidth+=s->getBandwidth();
			unicast_served--;
			return true;
			break;
		case multicast:
			std::pair<std::multimap<Service *,Subscriber *>::iterator,std::multimap<Service *,Subscriber *>::iterator> ret;
			ret = mc_served.equal_range(s);
			for(std::multimap<Service *,Subscriber *>::iterator i = ret.first; i!=ret.second; ++i) {
				if((*i).second == t) {
					mc_served.erase(i);
					break;
				}
			}
			if(!mc_served.count(s)) {
				P_DEBUG("No one is left so we free the resources");
				broadcast_bandwidth+=s->getBandwidth();
				bandwidth+=s->getBandwidth();
			}
			multicast_served--;
			return true;	
			break;
	}
	return false;
}
unsigned Cell::getNumberOfMulticastSubscribersPerService(Service *s) {
	std::pair<std::multimap<Service *,Subscriber *>::iterator,std::multimap<Service *,Subscriber *>::iterator> ret; 
	ret = mc_served.equal_range(s); 
	unsigned subs = 0;
	for(std::multimap<Service *,Subscriber *>::iterator i = ret.first; i!=ret.second; ++i) {
		subs++;
	}
	return subs;
}
