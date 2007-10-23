CC = g++
CXXFLAGS = -Wall -Wno-long-long -pedantic
DEBUGFLAGS = -g
QT_INCLUDE = -DQT_SHARED -I/opt/qt4/include -I/opt/qt4/include/QtCore \
			 -I/opt/qt4/include/QtGui
QT_LIBS = -lQtCore -lQtGui -L/opt/qt4/lib/ -lz -lm -pthread -lgthread-2.0 \
		  -lrt -lglib-2.0 -lpthread -ldl

ALL_FLAGS = $(CXXFLAGS) $(DEBUGFLAGS) $(QT_INCLUDE)
ALL_LD_FLAGS = $(QT_LIBS)

ALL_FLAGS += -I../src/diff
ALL_LD_FLAGS += -lcppu

TEST_SUITES = text.cpp snippet.cpp hunk.cpp diff.cpp levenshtein.cpp
OBJS_LIST = snippet.o settings.o text.o hunk.o diff.o file.o levenshtein.o
OBJS = $(foreach file, $(OBJS_LIST), ../src/objs/$(file))

all: run_tests
run_tests: test
	-cppu-aggregate ./test
	@echo
	@echo -ne "Press key to start valgrind "
	@read key
	-valgrind --leak-check=full --show-reachable=yes ./test

test: main.cpp $(TEST_SUITES)
	pwd && $(CC) $(ALL_FLAGS) -o $@ $< $(OBJS) $(ALL_LD_FLAGS)

clean:
	rm -f test
	rm -f *.o

.PHONY: all run_tests
