#ifndef _TERMINAL_H
#define _TERMINAL_H

/*
 *  Terminal.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include "utils.h"
#include "Coordinate.h"
#include "Cell.h"
#include "Subscriber.h"
#include "Technology.h"
#include <vector>

class Cell;

class Terminal : public Subscriber {
public:
	Terminal();
	Terminal(Coordinate c);
	Terminal(coord_t lat, coord_t lon);
	~Terminal();
	void setPosition(Coordinate c) { position = c; }
	Coordinate getPosition() const { return position; }
	void associate(Cell *c);
	bool startService();
	bool isAssociated() { return associatedTo!=NULL; };
	
	friend std::ostream &operator<<(std::ostream &o, Terminal &t);
private:
	Coordinate position;
	Cell *associatedTo;
	std::vector<Technology *> interface;
};

#endif // _TERMINAL_H
