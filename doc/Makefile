POD2MAN = pod2man

TARGETS = diff.png qt.png qshowdiff.1.gz
all: $(TARGETS)

%.png: %.dia
	dia -t png -e $@ $<

%.1.gz: %.1
	gzip $<
%.1: %.pod
	$(POD2MAN) -s 1 -n qshowdiff <$< >$@

clean:
	rm -f *~
	rm -f *.png
	rm -f *.1*

.PHONY: all clean
