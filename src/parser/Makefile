-include ../../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I../

TARGETS = libparser.a

OBJS = in.o parser.o parser_big.o choose_parser.o

all: $(TARGETS)

libparser.a: $(OBJS)
	ar cr $@ $(OBJS)
	ranlib $@

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o

.PHONY: all clean

