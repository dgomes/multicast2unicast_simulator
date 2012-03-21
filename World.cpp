/*
 *  World.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "World.h"
#include <cmath>
#include <iomanip>

World::World() {
	engine.seed((int) time(0));
}

void World::setSignal(const Coordinate &c, Cell *s) { 
	coverage.insert(std::make_pair(c, s));
};

std::ostream &operator<<(std::ostream &o, World &c) {
/*
	for (std::multimap<Coordinate, Cell *>::iterator it = c.coverage.begin(); it != c.coverage.end(); ++it) {
		o << (*it).first << " => " << *(*it).second << std::endl;
	}
*/
	for (std::multimap<Coordinate, Terminal *>::iterator it = c.field.begin(); it != c.field.end(); ++it)
		o << (*it).first << " => " << *((*it).second) << std::endl;
	return o;
}

unsigned World::calculateCoverage() {
	unsigned a = 0; //number of associated terms
	for (std::multimap<Coordinate, Terminal *>::iterator term = field.begin(); term != field.end(); ++term) {
		for (std::multimap<Coordinate, Cell *>::iterator cell = coverage.begin(); cell != coverage.end(); ++cell) {
			double distance;
			if((distance = term->first.distanceTo(cell->first)) < cell->second->getRadius()) {
				P_DEBUG_MAX(*(term->second) << " is covered by [" << *(cell->second) << "] (" << distance << "km)");
				(term->second)->associate(cell->second);
			} else {
				P_DEBUG_MAX(*(term->second) << " is out of range of " << *(cell->second) << " (" << distance << "km)");
			}
		}
		if(term->second->isAssociated()) a++;
	}
	return a;
};

std::vector<Coordinate> World::generatePerfectUniformDistribution(double distance_apart, coord_t lat_min, coord_t lat_max, coord_t lon_min, coord_t lon_max) {
	lat_min = fmod(lat_min, 360);
	lat_max = fmod(lat_max, 360);
	lon_min = fmod(lon_min, 360);
	lon_max = fmod(lon_max, 360);

	if(lat_min == 0 && lon_min == 0 && lat_max == 0 && lon_max == 0) {
		lat_min = min.getLatitude();
		lat_max = max.getLatitude();
		lon_min = min.getLongitude();
		lon_max = max.getLongitude(); 
	}
	std::vector<Coordinate> dist;

	Coordinate t,m = min;
	do {
		t = m;
		do {
			P_DEBUG_MAX("new coordinate " << t);
			dist.push_back(t);
			t = t.eastOf(distance_apart);	
		} while (t.getLongitude() < lon_max);
		m = m.northOf(distance_apart);
	} while (m.getLatitude() < lat_max);

	return dist;
}

void World::seed(unsigned long s) {
	s = s % GENERATOR_WARMER;
    engine.seed((int)time(0));
    boost::uniform_int<int> field(0,GENERATOR_WARMER);
    boost::variate_generator<boost::rand48&, boost::uniform_int<int> > generator(engine, field);
	unsigned long garbage = 0;
	do {
		garbage++;
		generator();
	} while(garbage < s);
}

Coordinate World::getMiddle() {
	return Coordinate((min.getLatitude()+max.getLatitude())/2,(min.getLongitude()+max.getLongitude())/2);
}

std::vector<Coordinate> World::generateNormalDistribution(unsigned number_elements, Coordinate mean, double stddev) {
	seed();
	
	coord_t lat_mean = mean.getLatitude();
	coord_t lon_mean = mean.getLongitude();

	if(lat_mean == 0 && lon_mean == 0) {
		lat_mean = getMiddle().getLatitude();
		lon_mean = getMiddle().getLongitude();
	}

	coord_t lat_stdev = fabs(mean.getLatitude() - mean.northOf(stddev).getLatitude()); 
	coord_t lon_stdev = fabs(mean.getLongitude() - mean.eastOf(stddev).getLongitude());

	P_DEBUG_MAX("mean = " << mean);
	P_DEBUG_MAX("lat_stdev = " << lat_stdev);
	P_DEBUG_MAX("lon_stdev = " << lon_stdev);

    boost::normal_distribution<coord_t> lat_normal_dist(lat_mean,lat_stdev);
    boost::normal_distribution<coord_t> lon_normal_dist(lon_mean,lon_stdev);
	boost::variate_generator<boost::rand48&, boost::normal_distribution<coord_t> > lat_generator(engine, lat_normal_dist);
	boost::variate_generator<boost::rand48&, boost::normal_distribution<coord_t> > lon_generator(engine, lon_normal_dist);
	
    std::vector<Coordinate> dist;
	while(number_elements>0) {	
		Coordinate r(lat_generator(),lon_generator());
		dist.push_back(r);
		number_elements--;
	}
	return dist;	
}

World::~World() {
}
