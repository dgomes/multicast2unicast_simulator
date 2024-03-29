#ifndef _COLOR_H
#define _COLOR_H
//
// File: color.h
// Created by: Diogo Gomes <etdgomes@ua.pt>
// Created on: Thu Jul 31 15:20:15 2003
//
#ifndef NO_COLOR
#define RESET (char) 0x1b << "[0m"

#define BOLD (char) 0x1b << "[1m"
#define ITALIC (char) 0x1b << "[3m"

#define BLINK (char) 0x1b << "[5m"
#define NOBLINK (char) 0x1b << "[25m"

#define FG_BLACK (char) 0x1b << "[30m"
#define FG_RED (char) 0x1b << "[31m"
#define FG_GREEN (char) 0x1b << "[32m"
#define FG_YELLOW (char) 0x1b << "[33m"
#define FG_BLUE (char) 0x1b << "[34m"
#define FG_MAGENTA (char) 0x1b << "[35m"
#define FG_CYAN (char) 0x1b << "[36m"
#define FG_WHITE (char) 0x1b << "[37m"

#define BG_BLACK (char) 0x1b << "[40m"
#define BG_RED (char) 0x1b << "[41m"
#define BG_GREEN (char) 0x1b << "[42m"
#define BG_YELLOW (char) 0x1b << "[43m"
#define BG_BLUE (char) 0x1b << "[44m"
#define BG_MAGENTA (char) 0x1b << "[45m"
#define BG_CYAN (char) 0x1b << "[46m"
#define BG_WHITE (char) 0x1b << "[47m"

#else // No Color

#define RESET ""
#define BOLD ""
#define ITALIC ""
#define BLINK ""
#define NOBLINK ""

#define FG_BLACK ""
#define FG_RED ""
#define FG_GREEN ""
#define FG_YELLOW ""
#define FG_BLUE ""
#define FG_MAGENTA ""
#define FG_CYAN ""
#define FG_WHITE ""

#define BG_BLACK ""
#define BG_RED ""
#define BG_GREEN ""
#define BG_YELLOW ""
#define BG_BLUE ""
#define BG_MAGENTA ""
#define BG_CYAN ""
#define BG_WHITE ""

#endif  //No Color
#endif  //_COLOR_H
