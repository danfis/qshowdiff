CXXFLAGS += $(QT_CFLAGS)
CXXFLAGS += -Lobjs
LDFLAGS += $(QT_LIBS)

VPATH = diff qt parser

TARGETS = qshowdiff

DIFF_OBJS = snippet.o diff.o \
			levenshtein_table.o levenshtein_distances.o
QT_OBJS = diff_view.o main_window.o
PARSER_OBJS = parser.o tokens.o

OBJS_TMP = main.o settings.o $(DIFF_OBJS) $(QT_OBJS) $(PARSER_OBJS)
OBJS = $(foreach file, $(OBJS_TMP), objs/$(file))


all: $(TARGETS)

qshowdiff: $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)


objs/%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c -o $@ $<
objs/%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
	
qt/diff_view.cpp: qt/diff_view.moc
qt/diff_view.moc: qt/diff_view.h
	$(MOC) -p'.' $< > $@

clean:
	rm -f objs/*.o
	rm -f $(TARGETS)
	rm -f *.moc
	rm -f */*.moc

.PHONY: all clean
