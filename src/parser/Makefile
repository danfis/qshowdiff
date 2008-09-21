-include ../../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I../

TARGETS = libparser.a

OBJS = parser.o tokens.o in.o choose_parser.o

all: $(TARGETS)

libparser.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o

.PHONY: all clean

