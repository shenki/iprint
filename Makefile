#! /usr/bin/make

CFLAGS = -Wall

default: i

clean:
	rm -f i

install: i i.1
	install ./i $(DESTDIR)/usr/bin
	install -D -m644 ./i.1 $(DESTDIR)/usr/share/man/man1/i.1
	ln -s i.1 $(DESTDIR)/usr/share/man/man1/iprint.1

