#ifndef _TECHNOLOGY_H_
#define _TECHNOLOGY_H_
/*
 *  Technology.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

class Technology  {
public:
	Technology();
	~Technology() {};
	unsigned getTechBandwidth() { return max_bandwidth; };
	unsigned getTechBroadcastBandwidth() { return max_broadcast_bandwidth; };
protected:	
	unsigned max_bandwidth;
	unsigned max_broadcast_bandwidth;
};

#endif
