SUBDIRS := $(wildcard Lab*)

.PHONY: all clean $(SUBDIRS)

all: TASK := all
all: $(SUBDIRS)

clean: TASK := clean
clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(or $(TASK),console)
