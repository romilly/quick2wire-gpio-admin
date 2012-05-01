
CC=gcc
CFLAGS=-Wall -O2

ARCH:=$(shell uname -m)
OUTDIR=out/$(ARCH)
SRCDIR=src

SRC=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRC:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

ifndef PREFIX
PREFIX=/usr/local
endif


all: $(OUTDIR)/gpio-admin
.PHONY: all

$(OUTDIR)/gpio-admin: $(OBJS)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -c -o $@

install: all
	groupadd -f --system gpio
	install -g gpio -m u=rwxs,g=rxs,o=rx $(OUTDIR)/gpio-admin $(PREFIX)/bin
.PHONY: install

uninstall:
	rm -vf $(PREFIX)/bin/gpio-admin
.PHONY: uninstall

clean :
	rm -rf $(OUTDIR) *~
.PHONY: clean

real-clean: clean
	rm -rf out
.PHONY: real-clean

again: clean all
.PHONY: again
