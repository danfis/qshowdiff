ALL_FLAGS_TEST = $(ALL_FLAGS) -I../src/diff
ALL_LD_FLAGS_TEST = $(ALL_LD_FLAGS) -lcppu

TEST_SUITES = text.cpp snippet.cpp hunk.cpp
OBJS = ../src/diff/text.o ../src/diff/snippet.o ../src/diff/hunk.o

all: run_tests
run_tests: test
	-cppu-aggregate ./test
	@echo
	@echo -ne "Press key to start valgrind "
	@read key
	-valgrind --leak-check=full --show-reachable=yes ./test

test: main.cpp $(TEST_SUITES)
	$(CC) $(ALL_FLAGS_TEST) -o $@ $< $(OBJS) $(ALL_LD_FLAGS_TEST)

clean:
	rm -f test
	rm -f *.o

.PHONY: all run_tests
