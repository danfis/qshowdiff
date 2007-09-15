CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore \
			 -I/opt/qt4/include/QtGui

ALL_FLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE)

TARGETS = snippet.o

all: $(TARGETS)

%.o: %.cpp %.h
	$(CC) $(ALL_FLAGS) -c -o $@ $< 	

clean:
	rm -f *.o

.PHONY: all test clean
