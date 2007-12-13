CC = g++
MOC = moc

DEBUGFLAGS = -g
CXXFLAGS += -Wall -Wno-long-long -pedantic $(DEBUGFLAGS)

QT_CFLAGS = $(shell pkg-config QtCore QtGui --cflags)
QT_LIBS = $(shell pkg-config QtCore QtGui --libs)

# export variables for sub-makes
export CC
export MOC
export CXXFLAGS
export QT_CFLAGS
export QT_LIBS

all:
	cd src && $(MAKE) all
	
clean:
	rm -f *.o
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean

check: all
	cd tests && $(MAKE)

.PHONY: all check clean
