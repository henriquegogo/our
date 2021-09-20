BINDIR?=/usr/bin
XSESSIONSDIR?=/usr/share/xsessions
CFLAGS?=-Wpedantic -Wall -Wextra

all:
	$(CC) $(CFLAGS) xeletools.c -lX11 -o xeletools

install:
	install -d ${BINDIR}
	install -m 755 xeletools ${BINDIR}

uninstall:
	rm ${BINDIR}/xeletools
		
clean:
	rm xeletools
