-include ../../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I../

TARGETS = libparser.a

OBJS = in.o parser.o parser_big.o choose_parser.o
PARSERS = $(wildcard parser_*.hpp)

all: $(TARGETS)

libparser.a: $(OBJS)
	ar cr $@ $(OBJS)
	ranlib $@

choose_parser.cpp: $(PARSERS)
	touch choose_parser.cpp

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o

.PHONY: all clean

