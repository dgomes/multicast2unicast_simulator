/*
 *  WifiCell.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights remc_served.
 *
 */

#include "WifiCell.h"
#include "utils.h"

WifiCell::WifiCell(Coordinate &c, double r) : Cell(c,r) {
	type = "Wifi";
	P_DEBUG_MAX("Creating WifiCell at " << this->center << " with a " << this->radius << " radius");
	bandwidth = max_bandwidth;
	broadcast_bandwidth = max_broadcast_bandwidth;
}

WifiCell::WifiCell(coord_t lat, coord_t lon, double r) {
	Coordinate t(lat,lon);
	*this = WifiCell(t,r);
}

bool WifiCell::associate(Terminal *t) { 
	P_DEBUG_MAX("WifiCell::associate("<< *t << ")");
	clients.push_back(t);
	if(t->inUse()) {
		return request(t->getService(),dynamic_cast<Subscriber *>(t));
	}
	return true;
};
bool WifiCell::dissociate(Terminal *t) { 
	P_DEBUG_MAX("WifiCell::dissociate("<< *t << ")");
	clients.remove(t);
	if(t->inUse()) {
		return free(t->getService(),dynamic_cast<Subscriber *>(t));
	}	
	return true;
};

