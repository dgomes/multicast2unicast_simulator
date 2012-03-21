/*
 *  UMTSCell.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights remc_served.
 *
 */

#include "UMTSCell.h"
#include "utils.h"

UMTSCell::UMTSCell(Coordinate &c, double r) : Cell(c,r) {
	type = "UMTS";
	P_DEBUG_MAX("Creating UMTSCell at " << this->center << " with a " << this->radius << " radius");
	bandwidth = max_bandwidth;
	broadcast_bandwidth = max_broadcast_bandwidth;
}

UMTSCell::UMTSCell(coord_t lat, coord_t lon, double r) {
	Coordinate t(lat,lon);
	*this = UMTSCell(t,r);
}

bool UMTSCell::associate(Terminal *t) { 
	P_DEBUG_MAX("UMTSCell::associate("<< *t << ")");
	clients.push_back(t);
	if(t->inUse()) {
		return request(t->getService(),dynamic_cast<Subscriber *>(t));
	}
	return true;
};
bool UMTSCell::dissociate(Terminal *t) { 
	P_DEBUG_MAX("UMTSCell::dissociate("<< *t << ")");
	clients.remove(t);
	if(t->inUse()) {
		return free(t->getService(),dynamic_cast<Subscriber *>(t));
	}	
	return true;
};

