MAKE = make
PLACE = src

DIRS = src/bor src/sck
# the sets of directories to do various things in
BUILDDIRS = $(DIRS:%=build-%)
#INSTALLDIRS = $(DIRS:%=install-%)
CLEANDIRS = $(DIRS:%=clean-%)
CLEANERDIRS = $(DIRS:%=cleaner-%)
#TESTDIRS = $(DIRS:%=test-%)

.PHONY: subdirs $(SUBDIRS)

all: $(BUILDDIRS)

$(DIRS): $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)

#install: $(INSTALLDIRS) all
#$(INSTALLDIRS):
#	$(MAKE) -C $(@:install-%=%) install

#test: $(TESTDIRS) all
#$(TESTDIRS): 
#	$(MAKE) -C $(@:test-%=%) test

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean

cleaner: $(CLEANERDIRS)
$(CLEANERDIRS): 
	$(MAKE) -C $(@:cleaner-%=%) cleaner

.PHONY: subdirs $(DIRS)
.PHONY: subdirs $(BUILDDIRS)
#.PHONY: subdirs $(INSTALLDIRS)
#.PHONY: subdirs $(TESTDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: subdirs $(CLEANERDIRS)
.PHONY: all install clean test cleaner


$(SUBDIRS):
	$(MAKE) -C $(PLACE)/$@ 
