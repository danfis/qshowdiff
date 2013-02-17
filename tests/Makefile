-include ../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I../src/
LDFLAGS += $(QT_LIBS) -L../src/diff -ldiff -Lcu/ -lcu

OBJS = diff.o hunk.o levenshtein.o text.o

CHECK_REG=../../cu/check-regressions

all: test

test: $(OBJS)
	$(CXX) $(CXXCFLAGS) -o $@ main.cpp $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

check: all
	@echo ""
	@echo "----------------------------------------";
	./test
	@echo "----------------------------------------";
	@echo "Checking regressions:";
	./$(CHECK_REG) regressions
	@echo ""

check-valgrind: all
	valgrind -q --leak-check=full --show-reachable=yes --trace-children=yes ./test

clean:
	rm -f *.o
	rm -f objs/*.o
	rm -f test
	rm -f tmp.*
	rm -f regressions/tmp.*

.PHONY: all clean check check-valgrind
	

