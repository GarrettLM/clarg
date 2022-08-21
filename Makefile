CC = gcc
CFlags = -Wall
LDFlags = -lm

libclargparse.a: clargparse.o
	ar rcs $@ $< clargparse.h

test: test.o
	$(CC) $(LDFLAGs) $< -lclargparse -o $@

test.o: clargparsetest.c
	$(CC) $(CFLAGS) -c $< -o $@

libclargparse.so: clargparse.h clargparse.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ clargparse.c -lc

.PHONY: clean
clean:
	rm -f libclargparse.so libclargparse.a clargparse.o

.PHONY: install
install:
	mv libclargparse.a /usr/local/lib/libclargparse.a
	cp clargparse.h /usr/local/include/clargparse.h

.PHONY: uninstall
uninstall:
	rm /usr/local/lib/libclargparse.a
