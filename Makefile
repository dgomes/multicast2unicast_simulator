#
# Makefile created by mfg (version 2.4)
#

TARGET =	mc2un
HEADERS =	Subscriber.h Service.h Cell.h World.h Technology.h Terminal.h UMTS.h UMTSCell.h Wifi.h WifiCell.h Coordinate.h Parser.h \
		color.h config.h utils.h configuration.h
SOURCES =	Subscriber.cpp Service.cpp Cell.cpp World.cpp Technology.cpp Terminal.cpp UMTS.cpp UMTSCell.cpp Wifi.cpp Coordinate.cpp Parser.cpp \
		WifiCell.cpp main.cpp utils.cpp configuration.cpp
OBJECTS =	Subscriber.o Service.o Coordinate.o Cell.o World.o Technology.o Terminal.o UMTS.o UMTSCell.o Wifi.o WifiCell.o main.o Parser.o \
		utils.o configuration.o
CLEAN =		$(OBJECTS)	

#>		--- do not remove this line ---
AR =		ar
ARFLAGS =	cr
CC =		g++
CPPFLAGS =	-Wall -g
DEFS =
DISTCLEAN =
EXEEXT =
INCLUDES = -I/opt/local/include/
INSTALL =	install -c
INSTALL_DATA =	$(INSTALL) -m 644
INSTALL_PROGRAM =	$(INSTALL) -s
LDFLAGS = -L/opt/local/lib
LEX =		lex
LIBS =		-lm -lkmldom -lkmlbase 
LIBTOOL =	libtool $(LTFLAGS)
LPR =		lpr -h
PROGRAMS =	$(OBJECTS:.o= )
RANLIB =	ranlib
RM =		rm -f
VERSION =	0
YACC =		yacc

prefix =	/usr/local
bindir =	$(prefix)/bin
libdir =	$(prefix)/lib
mandir =	$(prefix)/man

COMPILE =	$(CC) -c $(CFLAGS) $(DEFS) $(INCLUDES) $(CPPFLAGS)

.SUFFIXES: .l .y .m .cc .cpp
.c.o:
	$(COMPILE) $< -o $@
.m.o:
	$(COMPILE) $< -o $@
.cc.o:
	$(COMPILE) $< -o $@
.cpp.o:
	$(COMPILE) $< -o $@

SHELL =		/bin/sh

$(TARGET): $(OBJECTS) $(ADDLIBS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(ADDLIBS) $(LIBS) -o $@

check: $(TARGET)

clean:
	$(RM) $(CLEAN) $(TARGET) $(TARGET)$(EXEEXT) core

distclean: clean
	$(RM) $(DISTCLEAN)

print:
	$(LPR) $(HEADERS) $(SOURCES)

install: $(TARGET)
	$(INSTALL) -d $(bindir)
	$(INSTALL_PROGRAM) $(TARGET)$(EXEEXT) $(bindir)

uninstall:
	$(RM) $(bindir)/$(TARGET)$(EXEEXT)

#>		--- do not remove this line ---

Force_Update:

Cell.o: Cell.cpp Cell.h World.h

World.o: World.cpp World.h

Technology.o: Technology.cpp Technology.h

Terminal.o: Terminal.cpp World.h Terminal.h color.h config.h utils.h

Wifi.o: Wifi.cpp Technology.h Wifi.h

UMTS.o: UMTS.cpp Technology.h UMTS.h

UMTSCell.o: UMTSCell.cpp Cell.h World.h Technology.h UMTS.h UMTSCell.h color.h \
	config.h utils.h

WifiCell.o: WifiCell.cpp Cell.h World.h Technology.h Wifi.h WifiCell.h color.h \
	config.h utils.h

main.o: main.cpp Cell.h World.h Technology.h Terminal.h Wifi.h WifiCell.h \
	color.h config.h utils.h

utils.o: utils.cpp color.h config.h utils.h

Parser.o: Parser.cpp Parser.h
	$(COMPILE) $< -o $@ #-I/usr/local/include/kml/third_party/boost_1_34_1
