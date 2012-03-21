#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H

/*
 *  Subscriber.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include "Service.h"
#include <iostream>
#include "utils.h"

class Service;

class Subscriber {
public:
	Subscriber() : serv(NULL), inuse(false) {};
	virtual ~Subscriber() {};
	Service *getService() const { return serv; };
	void subscribeService(Service &c);
	virtual bool startService() { 
		P_DEBUG("Subscriber::startService()");
		return false; 
	};
	bool inUse() { return inuse; };
	
	friend std::ostream &operator<<(std::ostream &o, Subscriber &t); 
private:
	Service *serv;
	bool inuse;
};

#endif // _SUBSCRIBER_H
