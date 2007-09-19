CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore \
			 -I/opt/qt4/include/QtGui
QT_LIBS = -lQtCore -lQtGui -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 \
		  -lrt -lglib-2.0 -lpthread -ldl
QT_LIBS =  -lQtGui -L/opt/qt4-debug/lib -L/usr/X11R6/lib \
  -laudio -lXt -lpng -lSM -lICE -lQtCore -lz -pthread \
  -lgthread-2.0 -lrt -lglib-2.0 -lpthread -lXi -lXrender -lXrandr -lXfixes \
  -lXcursor -lXinerama -lfreetype -lfontconfig -lXext -lX11 -lm -ldl

ALL_FLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE)
ALL_LD_FLAGS = $(QT_LIBS)


VPATH = diff qt

TARGETS = qshowdiff

DIFF_OBJS = snippet.o diff.o file.o hunk.o text.o
QT_OBJS = diff_view.o main_window.o

OBJS_TMP = main.o settings.o $(DIFF_OBJS) $(QT_OBJS)
OBJS = $(foreach file, $(OBJS_TMP), objs/$(file))

all: $(TARGETS)

qshowdiff: $(OBJS)
	$(CC) $(ALL_FLAGS) -o $@ $(OBJS) $(ALL_LD_FLAGS)

objs/%.o: %.cpp %.h
	$(CC) $(ALL_FLAGS) -c -o $@ $<
objs/%.o: %.cpp
	$(CC) $(ALL_FLAGS) -c -o $@ $<
	
clean:
	rm -f objs/*.o
	rm -f $(TARGETS)

.PHONY: all clean
