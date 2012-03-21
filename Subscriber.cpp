/*
 *  Subscriber.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "Subscriber.h"
#include "Terminal.h"

std::ostream &operator<<(std::ostream &o, Subscriber &t) {
	o << "Subscriber: " <<  *((Terminal *) &t);
	return o;
}

void Subscriber::subscribeService(Service &c) {
	serv = &c;
	c.addSubscriber(this);
}

