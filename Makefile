BINDIR?=/usr/bin
CFLAGS?=-Wpedantic -Wall -Wextra

all: ewmh visiblewins

ewmh:
	$(CC) $(CFLAGS) ewmh-support.c -lX11 -o ewmh-support

visiblewins:
	$(CC) $(CFLAGS)	visible-windows.c -lX11 -o visible-windows

install:
	install -d ${BINDIR}
	install -m 755 ewmh-support ${BINDIR}
	install -m 755 visible-windows ${BINDIR}

uninstall:
	rm ${BINDIR}/ewmh-support
	rm ${BINDIR}/visible-windows
		
clean:
	rm ewmh-support
	rm visible-windows
