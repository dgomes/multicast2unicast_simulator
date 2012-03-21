/*
 *  UMTS.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "UMTS.h"
#include "constants.h"

UMTS::UMTS() {
	max_bandwidth = DEFAULT_UMTS_BANDWIDTH;
	max_broadcast_bandwidth = DEFAULT_UMTS_BROADCAST_BANDWIDTH;
}
