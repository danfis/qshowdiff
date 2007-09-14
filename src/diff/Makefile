TARGETS = text.o snippet.o hunk.o file.o

all: $(TARGETS)

%.o: %.cpp %.h
	$(CC) $(ALL_FLAGS) -c -o $@ $< 	

clean:
	rm -f *.o

.PHONY: all test clean
