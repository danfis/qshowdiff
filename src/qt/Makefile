CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore \
			 -I/opt/qt4/include/QtGui
QT_LIBS = -lQtCore -lQtGui -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 \
		  -lrt -lglib-2.0 -lpthread -ldl

ALL_FLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE)
ALL_LD_FLAGS = $(QT_LIBS)

TARGETS = main_window.o diff_view.o

all: $(TARGETS)

%.o: %.cpp %.h
	$(CC) $(ALL_FLAGS) -c -o $@ $< 	

clean:
	rm -f *.o

.PHONY: all test clean
