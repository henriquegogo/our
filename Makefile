BINDIR?=/usr/bin
CFLAGS?=-Wpedantic -Wall -Wextra

all: ewmh

ewmh:
	$(CC) $(CFLAGS) ewmh-support.c -lX11 -o ewmh-support

install:
	install -d ${BINDIR}
	install -m 755 ewmh-support ${BINDIR}

uninstall:
	rm ${BINDIR}/xeletools
	rm ${BINDIR}/ewmh-support
		
clean:
	rm ewmh-support
