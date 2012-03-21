/*
 *  Terminal.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "Terminal.h"
#include <stdlib.h>
#include <time.h>

Terminal::Terminal() : associatedTo(NULL) {
};

Terminal::Terminal(Coordinate c)  : associatedTo(NULL){
	position = c;
	P_DEBUG_MAX("Create Terminal " << position);
}
Terminal::Terminal(coord_t lat, coord_t lon)  : associatedTo(NULL){
	position = Coordinate(lat, lon);
	P_DEBUG_MAX("Create Terminal " << position);
}

Terminal::~Terminal() {
	//delete interfaces
	for(std::vector<Technology *>::iterator i=interface.begin(); i!=interface.end(); ++i)
		delete *i;
}
void Terminal::associate(Cell *c) {
	if(c!=NULL) {
		// we are free
		if(associatedTo == NULL) {
			if(c->associate(this)) {
				associatedTo = c;				
			}
		} else 
		//are we attaching to a closer cell ?
		if(position.distanceTo(c->getPosition()) < position.distanceTo(associatedTo->getPosition())) {
			associatedTo->dissociate(this);
			associatedTo = c;
			c->associate(this);
		}
	}
}

std::ostream &operator<<(std::ostream &o, Terminal &t) {
	o << "Terminal" << " @ " <<  t.position;
	if(t.associatedTo!=NULL) o << "\t attached to " << *t.associatedTo; 
	if(t.getService() != NULL) o << "\t subscribed to " << *t.getService();
	return o;
}

bool Terminal::startService() {
	if(getService()==NULL) return false;
	if(associatedTo==NULL) return false;
	return associatedTo->request(getService(),this);
}
