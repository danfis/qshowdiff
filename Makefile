CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore
QT_LIBS = -lQtCore -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 -lrt \
          -lglib-2.0 -lpthread -ldl

all: text.o

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE) -c -o $@ $< 	

clean:
	rm -f *.o
	cd tests && $(MAKE) clean

test:
	cd tests && $(MAKE)

.PHONY: all test clean
