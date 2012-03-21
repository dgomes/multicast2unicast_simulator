#ifndef _UTILS_H
#define _UTILS_H

/*
 *  utils.h
 *  mc2un_sim
 *
 *  Created by Diogo Gomes on 09/03/16.
 *  Copyright 2009 Universidade de Aveiro. All rights reserved.
 *
 */
#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>

#include "config.h"
#include "color.h"

using std::cout;
using std::cerr;
using std::endl;

template <class T> inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

std::string timestamp();

#define DEBUG_ID "[" << timestamp() << "] {" << __FILE__<<":"<<__LINE__<<"}\t"
#define P_HEX(x) std::hex << x << std::dec

#ifdef DEBUG
#define P_DEBUG(str) std::cerr << DEBUG_ID << FG_MAGENTA << str << RESET << std::endl; 
#else
#define P_DEBUG(str) 
#endif

#ifdef DEBUG_MAX
#define P_DEBUG_MAX(str) std::cerr << DEBUG_ID << FG_MAGENTA << str << RESET << std::endl; 
#else
#define P_DEBUG_MAX(str) 
#endif

#endif //_UTILS_H
