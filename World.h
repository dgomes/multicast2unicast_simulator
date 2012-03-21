#ifndef _WORLD_H
#define _WORLD_H
/*
 *  World.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <boost/random.hpp>

#include "Cell.h"
#include "Terminal.h"

typedef boost::mt19937 base_generator;

class World {
public:
	World();
	World(Coordinate sw, Coordinate ne) : min(sw), max(ne) { World(); };
	~World();

	template <class T> 
	void placeCells(std::list<T> &list) {
		typename std::list<T>::iterator i;
		for(i = list.begin(); i != list.end(); i++) { 
    		coverage.insert(std::make_pair((*i).getPosition(), (Cell *) &(*i)));
			P_DEBUG_MAX("Place " << *i);
		}
	};
	template <class T> 
	void placeTerminals(std::list<T> &list) {
		typename std::list<T>::iterator i;
		for(i = list.begin(); i != list.end(); i++) { 
    		field.insert(std::make_pair((*i).getPosition(), (Terminal *) &(*i)));
			P_DEBUG_MAX("Place " << *i);
		}
	};

	std::vector<Coordinate> generateNormalDistribution(unsigned number_elements = 0, Coordinate mean = Coordinate(), double stddev = 0);
	std::vector<Coordinate> generatePerfectUniformDistribution(double distance_apart, coord_t lat_min = 0, coord_t lat_max = 360, coord_t lon_min = 0, coord_t lon_max = 360);
	void setSignal(const Coordinate &c, Cell *s); 
	unsigned calculateCoverage(); //returns number of associated terms
	Coordinate getMiddle();

	friend std::ostream &operator<<(std::ostream &o, World &c); 
private: 
	void seed(unsigned long s = GENERATOR_WARMER);
	std::multimap<Coordinate, Terminal *> field;
	std::multimap<Coordinate, Cell *> coverage;
	
	boost::rand48 engine;
	Coordinate min,max;		
};

#endif // _WORLD_H
