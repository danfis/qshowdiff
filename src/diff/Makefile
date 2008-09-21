-include ../../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I../

TARGETS = libdiff.a

OBJS = snippet.o diff.o levenshtein_table.o levenshtein_distances.o

all: $(TARGETS)

libdiff.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *.moc

.PHONY: all clean
