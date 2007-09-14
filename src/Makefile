SUBDIRS = diff

all:
	$(foreach dir, $(SUBDIRS), cd $(dir) && $(MAKE) $(MFLAGS) all)
	
clean:
	$(foreach dir, $(SUBDIRS), cd $(dir) && $(MAKE) $(MFLAGS) clean)

.PHONY: all test clean
