# System Configuration
topdir = ..
srcdir = $(topdir)/src

ifeq "$(ENVTYPE)" "mingw-w64"
	o ?= .o
	exe ?= .exe
	cc ?= x86_64-w64-mingw32-gcc
	link ?= $(cc)
	cflags ?= -O2 -DWINVER=0x0501 -D_WIN32_WINNT=0x0501
	ldflags ?= -mwindows -mconsole
	libs ?= -lws2_32
else
	o ?= .o
	exe ?=
	cc ?= gcc
	link ?= $(cc)
	cflags ?= -O2
	ldflags ?=
	libs ?=
endif


prefix ?= /usr/local
exec_prefix ?= $(prefix)

bindir ?= $(exec_prefix)/bin
libdir ?= $(exec_prefix)/lib
sbindir ?= $(exec_prefix)/sbin

sysconfdir ?= $(prefix)/etc
includedir ?= $(prefix)/include
datarootdir ?= $(prefix)/share
docdir ?= $(datarootdir)/doc/$(PROJ)
infodir ?= $(datarootdir)/info
mandir ?= $(datarootdir)/man
localstatedir ?= $(prefix)/var

INSTALL = install -p
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)
STRIP = strip -s


# Inference Rules
%$(exe) : %$(o)
	$(link) $(ldflags) -o $@ $^ $(libs)
	$(STRIP) $@
%$(o) : $(srcdir)/%.c
	$(cc) $(cflags) -c -o $@ $<

# Macro Defines
TAR_SORT_KEY ?= 6,6

PROGRAMS = \
				gai_test$(exe) \

DOC = \
				LICENSE \
				README.md \

include $(topdir)/config.mk

# Target List
all: \
				$(PROGRAMS) \

# Executables
gai_test$(exe):	gai_test$(o)

# Libraries

# Source Objects
gai_test$(o):	$(srcdir)/gai_test.c

# Clean Up Everything
clean:
	rm -f *$(o) $(PROGRAMS)

# Check
check:

# Test
test:

# Install
install: install-PROGRAMS install-DOC

install-PROGRAMS:
	@list='$(PROGRAMS)'; \
	for i in $$list; do \
		dir="`dirname \"$(DESTDIR)$(bindir)/$$i\"`"; \
		if [ ! -d "$$dir/" ]; then \
			echo " mkdir -p $$dir/"; \
			mkdir -p $$dir/; \
		fi;\
		echo " $(INSTALL_PROGRAM) $$i $(DESTDIR)$(bindir)/$$i"; \
		$(INSTALL_PROGRAM) $$i $(DESTDIR)$(bindir)/$$i; \
	done

install-DOC:
	@list='$(DOC)'; \
	for i in $$list; do \
		dir="`dirname \"$(DESTDIR)$(docdir)/$$i\"`"; \
		if [ ! -d "$$dir/" ]; then \
			echo " mkdir -p $$dir/"; \
			mkdir -p $$dir/; \
		fi;\
		echo " $(INSTALL_DATA) $(topdir)/$$i $(DESTDIR)$(docdir)/$$i"; \
		$(INSTALL_DATA) $(topdir)/$$i $(DESTDIR)$(docdir)/$$i; \
	done

# Pkg
pkg:
	@$(MAKE) DESTDIR=$(CURDIR)/$(PROJ)-$(VER).$(ENVTYPE) install; \
	tar cvf ./$(PROJ)-$(VER).$(ENVTYPE).tar ./$(PROJ)-$(VER).$(ENVTYPE) > /dev/null; \
	tar tvf ./$(PROJ)-$(VER).$(ENVTYPE).tar 2>&1 | sort -k $(TAR_SORT_KEY) | tee ./$(PROJ)-$(VER).$(ENVTYPE).tar.list.txt; \
	gzip -f ./$(PROJ)-$(VER).$(ENVTYPE).tar; \
	rm -fr ./$(PROJ)-$(VER).$(ENVTYPE)

# Dist
dist:
	@cd $(topdir); \
	git archive --format=tar --prefix=$(PROJ)-$(VER)/ $(TAG) > ../$(PROJ)-$(VER).tar; \
	tar tvf ../$(PROJ)-$(VER).tar 2>&1 | sort -k $(TAR_SORT_KEY) | tee ../$(PROJ)-$(VER).tar.list.txt; \
	gzip -f ../$(PROJ)-$(VER).tar
