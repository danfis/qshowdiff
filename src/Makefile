CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore \
			 -I/opt/qt4/include/QtGui
QT_LIBS = -lQtCore -lQtGui -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 \
		  -lrt -lglib-2.0 -lpthread -ldl

ALL_FLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE)
ALL_LD_FLAGS = $(QT_LIBS)

SUBDIRS = diff qt
OBJS = $(wildcard */*.o)

all: qshowdiff

qshowdiff: main.o all_subdirs
	$(CC) $(ALL_FLAGS) -o $@ $< $(OBJS) $(ALL_LD_FLAGS)

all_subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) $(MFLAGS) -C $$dir all;\
	done;

main.o: main.cpp
	$(CC) $(ALL_FLAGS) -c -o $@ $^
	
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) $(MFLAGS) -C $$dir clean;\
	done;

.PHONY: all test clean all_subdirs
