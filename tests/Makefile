CXXFLAGS += $(QT_CFLAGS) -I../src -I../src/diff
LDFLAGS += $(QT_LIBS) -lcppu

TEST_SUITES = text.cpp hunk.cpp diff.cpp levenshtein.cpp
OBJS_LIST = snippet.o settings.o diff.o levenshtein_table.o levenshtein_distances.o
OBJS = $(foreach file, $(OBJS_LIST), ../src/objs/$(file))

all: run_tests
run_tests: test
	-cppu-aggregate ./test
	@echo
	@echo -ne "Press key to start valgrind "
	@read key
	-valgrind --leak-check=full --show-reachable=yes ./test

test: main.cpp $(TEST_SUITES)
	pwd && $(CC) $(CXXFLAGS) -o $@ $< $(OBJS) $(LDFLAGS)

clean:
	rm -f test
	rm -f *.o

.PHONY: all run_tests
