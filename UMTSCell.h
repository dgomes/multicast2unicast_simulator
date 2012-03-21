#ifndef _UMTSCELL_H
#define _UMTSCELL_H

/*
 *  UMTSCell.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include "Cell.h"
#include "UMTS.h"
#include "Service.h"
#include "constants.h"

class UMTSCell : public Cell,UMTS {
public:
	UMTSCell(Coordinate &c, coord_t radius = DEFAULT_UMTSCELL_RADIUS);
	UMTSCell(coord_t lat, coord_t lon, coord_t radius = DEFAULT_UMTSCELL_RADIUS);
	~UMTSCell() {};
	virtual bool associate(Terminal *t);
	virtual bool dissociate(Terminal *t);
};

#endif
