#ifndef _WIFICELL_H
#define _WIFICELL_H

/*
 *  WifiCell.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include "Cell.h"
#include "Wifi.h"
#include "Service.h"
#include "constants.h"

class WifiCell : public Cell,Wifi {
public:
	WifiCell(Coordinate &c, coord_t radius = DEFAULT_WIFICELL_RADIUS);
	WifiCell(coord_t lat, coord_t lon, coord_t radius = DEFAULT_WIFICELL_RADIUS);
	~WifiCell() {};
	virtual bool associate(Terminal *t);
	virtual bool dissociate(Terminal *t);
};

#endif
