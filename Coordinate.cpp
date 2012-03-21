/*
 *  Coordinate.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include "Coordinate.h"
#include <cmath>
#include <iomanip>

#define DISTANCE_STEP 0.00001

Coordinate::Coordinate() {
	coord = std::make_pair(0,0);
}

Coordinate::Coordinate(coord_t lat, coord_t lon) {
	lat = fmod(lat, 360);
	lon = fmod(lon, 360);
	coord = std::make_pair(lat,lon);
}

std::ostream &operator<<(std::ostream &o, const Coordinate &c) {
	o << std::fixed << std::setprecision(6);
	o << "(" << c.coord.first << "," << c.coord.second << ")";
	return o;
}

bool Coordinate::operator< (const Coordinate &o) const {
	if(coord.first==o.coord.first)
		return coord.second < o.coord.second;
	return coord.first;	
}

double degreesToRadians(double d) {
	return d*M_PI/180;
}

double Coordinate::distanceTo(Coordinate p2) const {
	//Distance calculation using the haversine formula http://en.wikipedia.org/wiki/Haversine_formula
	unsigned R = 6371; // Radius of Earth in km

    double latitudeArc  = degreesToRadians(coord.first - p2.coord.first);
    double longitudeArc = degreesToRadians(coord.second - p2.coord.second);
    double latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    double lontitudeH = sin(longitudeArc * 0.5);
    lontitudeH *= lontitudeH;
    double tmp = cos(degreesToRadians(coord.first)) * cos(degreesToRadians(p2.coord.first));
    return R * 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH));
}

Coordinate Coordinate::eastOf(double distance) const {
	//TODO actually put in here a reverse formula!!!
	Coordinate n = *this;
	double d; 
	do {
		n.coord.second+=DISTANCE_STEP*distance;
		d = distanceTo(n);
	} while(d < distance);
	P_DEBUG_MAX("East new distance = " << d << "\t" << n);
	return n;
}

Coordinate Coordinate::northOf(double distance) const {
	//TODO actually put in here a reverse formula!!!
	Coordinate n = *this;
	double d; 
	do {
		n.coord.first+=DISTANCE_STEP*distance;
		d = distanceTo(n);
	} while(d < distance);
	P_DEBUG_MAX("North new distance = " << d << "\t" << n);
	return n;
}
