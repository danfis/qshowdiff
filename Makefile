-include Makefile.include

all:
	$(MAKE) -C src
	$(MAKE) -C doc
	$(MAKE) -C tests


install: all
	cp src/qshowdiff $(DESTDIR)/qshowdiff
	cp doc/qshowdiff.1.gz $(MANDIR)/qshowdiff.1.gz

clean:
	$(MAKE) -C src clean
	$(MAKE) -C doc clean
	$(MAKE) -C tests clean
	rm -f *.o

check:
	$(MAKE) -C src
	$(MAKE) -C tests check

.PHONY: all check clean install prepare
