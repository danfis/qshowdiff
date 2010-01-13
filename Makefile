-include Makefile.include

all: qshowdiff man

qshowdiff:
	$(MAKE) -C src qshowdiff

man:
	$(MAKE) -C doc qshowdiff.1.gz

tests:
	$(MAKE) -C tests

install: all
	if [ ! -d $(DESTDIR) ]; then mkdir -p $(DESTDIR); fi;
	cp src/qshowdiff $(DESTDIR)/qshowdiff
	if [ ! -d $(MANDIR) ]; then mkdir -p $(MANDIR); fi;
	cp doc/qshowdiff.1.gz $(MANDIR)/qshowdiff.1.gz

clean:
	$(MAKE) -C src clean
	$(MAKE) -C doc clean
	$(MAKE) -C tests clean
	rm -f *.o

check:
	$(MAKE) -C src
	$(MAKE) -C tests check

.PHONY: all check clean install qshowdiff man tests
