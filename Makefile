
PROJECT=quick2wire-gpio-admin
VERSION=1.0.0

PACKAGE=$(PROJECT)-$(VERSION)

DEB_REVISION=1

CC=gcc
CFLAGS=-Wall -O2

ARCH:=$(shell uname -m)
SRCDIR=src
OUTDIR=out/$(ARCH)

SRC=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRC:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

ifndef DESTDIR
DESTDIR=/usr/local
endif


all: $(OUTDIR)/gpio-admin out/gpio-admin.1.gz
.PHONY: all

dist: out/$(PACKAGE).tar.gz
.PHONY: dist

package: out/$(PACKAGE).tar.gz
	mkdir -p out/package
	cp out/$(PACKAGE).tar.gz out/package/$(PROJECT)_$(VERSION).orig.tar.gz
	(cd out/package && tar xzf $(PROJECT)_$(VERSION).orig.tar.gz)
	(cd out/package/$(PACKAGE) && dh_make)
.PHONY: package

out/$(PACKAGE).tar.gz:
	mkdir -p out/
	ln -s $(PWD) out/$(PACKAGE)
	tar czf out/$(PACKAGE).tar.gz \
		--dereference \
		--exclude-vcs \
		--exclude="out" \
		-C out/ $(PACKAGE)
	rm out/$(PACKAGE)

$(OUTDIR)/gpio-admin: $(OBJS)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -c -o $@

out/gpio-admin.1.gz: man/gpio-admin.1
	gzip -c $< > $@

install: all
	groupadd -f --system gpio
	mkdir -p $(DESTDIR)/bin/
	install -g gpio -m u=rwxs,g=rxs,o= $(OUTDIR)/gpio-admin $(DESTDIR)/bin/
	mkdir -p $(DESTDIR)/share/man/man1/
	install out/*.1.gz $(DESTDIR)/share/man/man1/

.PHONY: install

uninstall:
	rm -vf $(DESTDIR)/bin/gpio-admin $(DESTDIR)/share/man/man1/gpio-admin.1.gz
.PHONY: uninstall

clean :
	rm -rf out
.PHONY: clean

again: clean all
.PHONY: again
