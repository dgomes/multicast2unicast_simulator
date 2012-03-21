/*
 *  Wifi.cpp
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */

#include "Wifi.h"
#include "constants.h"

Wifi::Wifi() {
	max_bandwidth = DEFAULT_WIFI_BANDWIDTH;
	max_broadcast_bandwidth = DEFAULT_WIFI_BROADCAST_BANDWIDTH;
}
