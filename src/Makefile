-include ../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I./
LDFLAGS += $(QT_LIBS) \
           -Lqt/ -lqt \
           -Lparser/ -lparser \
           -Ldiff/ -ldiff


TARGETS = qshowdiff

OBJS = settings.o main.o

all: $(TARGETS)

qshowdiff: $(OBJS)
	$(MAKE) -C diff
	$(MAKE) -C parser
	$(MAKE) -C qt
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	$(MAKE) -C diff clean
	$(MAKE) -C parser clean
	$(MAKE) -C qt clean
	rm -f $(TARGETS)
	rm -f *.o

.PHONY: all clean
