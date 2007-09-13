CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_FLAGS = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore
QT_LIBS = -lQtCore -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 -lrt \
          -lglib-2.0 -lpthread -ldl

ALLFLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_FLAGS)
ALLLIBS = -lcppu $(QT_LIBS)

TEST_SUITES = text.cpp snippet.cpp hunk.cpp
TEST_DEPS = ../text.cpp ../text.h ../snippet.cpp ../snippet.h ../hunk.cpp \
			../hunk.h
OBJS = ../text.o ../snippet.o ../hunk.o



all: run_tests
run_tests: test
	-cppu-aggregate ./test
	@echo
	@echo -ne "Press key to start valgrind "
	@read key
	-valgrind --leak-check=full --show-reachable=yes ./test

test: main.cpp $(TEST_SUITES) $(TEST_DEPS) $(OBJS)
	$(CC) $(ALLFLAGS) -o $@ $< $(OBJS) $(ALLLIBS)

clean:
	rm -f test
	rm -f *.o

.PHONY: all run_tests
