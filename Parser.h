#ifndef _KML_PARSER_H
#define _KML_PARSER_H
/*
 *  Parser.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <exception>
#include <stdexcept>
#include <algorithm>

#include "Coordinate.h"
#include "utils.h"

template <class T>
class KML_helper_Coord2Elem {
public:
	void operator()(Coordinate &c) { 
		list.push_back(T(c));
	};
	std::list<T> list;
};

class KML_helper_Elem2Coord {
public:
	template <class T>
	void operator()(T &t) { 
		list.push_back(t.getPosition());
	};
	std::list<Coordinate> list;
};

class KML_parser  {
public:
	KML_parser(std::string f) : filename(f) {};
	~KML_parser() {};
	std::list<Coordinate> parse();
	void save(std::list<Coordinate> &c, std::string name);
private:
	std::string filename; 
};

template <class T>
class KML_storage {
public:
	KML_storage(std::string source) : kml_parser(source),save(true) {
		std::list<Coordinate> parsed = kml_parser.parse();
		h = std::for_each(parsed.begin(), parsed.end(), KML_helper_Coord2Elem<T>());
	};
	~KML_storage() {
		if(save) {
			KML_helper_Elem2Coord save = std::for_each(h.list.begin(), h.list.end(), KML_helper_Elem2Coord());
			kml_parser.save(save.list,std::string(typeid(*h.list.begin()).name()));		
		};
	};
	std::list<T>& getElements() {return h.list; };
	unsigned size() { return h.list.size(); };
	void store(T &elem) { h.list.push_back(elem); };
	void dontSave() { save = false; };
protected:
	KML_parser kml_parser;
private:
	bool save;
	KML_helper_Coord2Elem<T> h;
};

#endif //  _KML_PARSER_H
