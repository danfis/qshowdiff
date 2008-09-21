-include ../../Makefile.include

CXXFLAGS += $(QT_CFLAGS) -I../

TARGETS = libqt.a

OBJS = diff_view.o main_window.o

all: $(TARGETS)

libqt.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

diff_view.cpp: diff_view.moc
diff_view.moc: diff_view.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *.moc

.PHONY: all clean


