#ifndef _COORDINATE_H
#define _COORDINATE_H
/*
 *  Coordinate.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include <utility>
#include <iostream>
#include "utils.h"

typedef double coord_t;

class Coordinate  {
public:
	Coordinate();
	Coordinate(coord_t latitude, coord_t longitude);
	~Coordinate() {};
	
	friend std::ostream &operator<<(std::ostream &stream, const Coordinate &c);
	bool operator< (const Coordinate& ) const;
	double distanceTo(Coordinate p2) const; //return in Km
	Coordinate eastOf(double d) const;
	Coordinate northOf(double d) const;
	coord_t getLatitude() { return coord.first; };
	coord_t getLongitude() { return coord.second; };

protected:
	std::pair<coord_t, coord_t> coord; 
};

#endif //  _COORDINATE_H
