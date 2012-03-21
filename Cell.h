#ifndef _CELL_H
#define _CELL_H
/*
 *  Cell.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include <utility>
#include <list>
#include <map>
#include "utils.h"
#include "Coordinate.h"
#include "constants.h"
#include "Terminal.h"
#include "Service.h"

class Terminal;
class Cell {
public:
	Cell() : type("default"),unicast_served(0),unicast_denied(0),multicast_served(0),multicast_denied(0),multicast_services(0) { };
	//Cell(const Cell&);
	Cell(Coordinate &c, double radius=DEFAULT_CELL_RADIUS);
	virtual ~Cell() {};
	Coordinate& getPosition() { return center; };
	double getRadius() { return radius; };
	unsigned getNumberOfClients() { return clients.size(); };
	virtual bool associate(Terminal *t) { return false;};
	virtual bool dissociate(Terminal *t) { return false;};
	
	friend std::ostream &operator<<(std::ostream &o, Cell &c);
	
	virtual bool request(Service *s,Subscriber *t);
	virtual bool free(Service *s, Subscriber *t);

	unsigned getNumberOfUnicastSubscribers() { return unicast_served; };
	unsigned getNumberOfMulticastSubscribers() { return multicast_served; };
	unsigned getNumberOfMulticastServices() { return multicast_services; };
	unsigned getNumberOfUnicastSubscribersDeniedService() { return unicast_denied; };
	unsigned getNumberOfMulticastSubscribersDeniedService() { return multicast_denied; };
	unsigned getNumberOfMulticastSubscribersPerService(Service *);
protected:
	std::string type;
	double radius;
	Coordinate center;
	std::list<Terminal *> clients;
	std::multimap<Service *, Subscriber*> mc_served;
	unsigned bandwidth; // in kbits/s
	unsigned broadcast_bandwidth; // in kbits/s 

	unsigned unicast_served,unicast_denied,multicast_served,multicast_denied,multicast_services; 
};
#endif //_CELL_H
