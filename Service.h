#ifndef _SERVICE_H_
#define _SERVICE_H_
/*
 *  Service.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include "Subscriber.h"
#include <list>
#include <iostream>

enum ServiceType {unicast,multicast};

class Subscriber;

class Service  {
public:
	Service(unsigned bw, ServiceType t, std::string name ="");
	~Service() {};
	unsigned getBandwidth() { return bandwidth; };
	std::string getName() { return name; };
	ServiceType getServiceType() { return type; };
	void addSubscriber(Subscriber *t) { subscribers.push_back(t); };
	friend std::ostream &operator<<(std::ostream &o, Service &s); 
private:
	unsigned bandwidth; //in kbit/s 
	ServiceType type;	
	std::string name;	
	std::list<Subscriber *> subscribers;
};

#endif
