TARGETS = diff.png qt.png
all: $(TARGETS)

%.png: %.dia
	dia -t png -e $@ $<


clean:
	rm -f *~
	rm -f *.png

.PHONY: all clean
