/*
 *  utils.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "utils.h"
#include <iomanip>

#include <sys/time.h>
#include <time.h>

std::string timestamp() {
	struct timeval tv;
	int res;
	
	res = gettimeofday(&tv, NULL);
	assert (res == 0);
	struct tm *t;
	t = localtime(&tv.tv_sec);
	std::stringstream tstamp;
	//  tstamp << tv.tv_sec << "," << tv.tv_usec/1000;
	tstamp.fill('0');
	tstamp << std::setw(2) << t->tm_hour << ":" << std::setw(2) << t->tm_min << ":" << std::setw(2) << t->tm_sec << "." << std::setw(6) << tv.tv_usec;
	return tstamp.str();
}