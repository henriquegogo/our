BINDIR?=/usr/bin
CFLAGS?=-Wpedantic -Wall -Wextra

all: focuswin

ewmh:
	$(CC) $(CFLAGS) ewmh-support.c -lX11 -o ewmh-support

focuswin:
	$(CC) $(CFLAGS)	focuswin.c -lX11 -o focuswin

install:
	install -d ${BINDIR}
	install -m 755 ewmh-support ${BINDIR}
	install -m 755 focuswin ${BINDIR}

uninstall:
	rm ${BINDIR}/ewmh-support
	rm ${BINDIR}/focuswin
		
clean:
	rm ewmh-support
	rm focuswin
