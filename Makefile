CC = g++
MOC = moc

DESTDIR ?= /usr/local/bin

ifeq ($(DEBUG), yes)
  DEBUGFLAGS = -g
  CXXFLAGS =
else
  DEBUGFLAGS = -DNDEBUG
endif

CXXFLAGS += -Wall -Wno-long-long -pedantic $(DEBUGFLAGS)

QT_CFLAGS = $(shell pkg-config QtCore QtGui --cflags)
QT_LIBS = $(shell pkg-config QtCore QtGui --libs)

DEFAULT_TYPE ?= git
DEFAULT_CODEC ?= DEFAULT

# export variables for sub-makes
export CC
export MOC
export CXXFLAGS
export QT_CFLAGS
export QT_LIBS
export DEFAULT_TYPE
export DEFAULT_CODEC

all: prepare
	cd src && $(MAKE) all

prepare:
	mkdir -p src/objs

install: all
	cp src/qshowdiff $(DESTDIR)/qshowdiff

clean:
	rm -f *.o
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean
	rm -rf src/objs

check: all
	cd tests && $(MAKE)

.PHONY: all check clean install prepare
