CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore
QT_LIBS = -lQtCore -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 -lrt \
          -lglib-2.0 -lpthread -ldl

ALL_FLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE)
ALL_LD_FLAGS = $(QT_LIBS)

SUBDIRS = src

# export variables for sub-makes
export CC
export ALL_FLAGS
export ALL_LD_FLAGS

all:
	$(foreach dir, $(SUBDIRS), cd $(dir) && $(MAKE) $(MFLAGS) all)
	
clean:
	rm -f *.o
	$(foreach dir, $(SUBDIRS), cd $(dir) && $(MAKE) $(MFLAGS) clean)

test:
	cd tests && $(MAKE) $(MFLAGS)

.PHONY: all test clean

