BINDIR?=/usr/bin
CFLAGS?=-Wpedantic -Wall -Wextra

all: ourwin

ourewmh:
	$(CC) $(CFLAGS) ourewmh.c -lX11 -o ourewmh

ourwin:
	$(CC) $(CFLAGS)	ourwin.c -lX11 -o ourwin

install:
	install -d ${BINDIR}
	install -m 755 ourewmh ${BINDIR}
	install -m 755 ourwin ${BINDIR}

uninstall:
	rm ${BINDIR}/ourewmh
	rm ${BINDIR}/ourwin
		
clean:
	rm ourewmh
	rm ourwin
