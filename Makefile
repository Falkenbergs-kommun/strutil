CXX=gcc
DESTDIR=/usr/local/lib
INCDIR=/usr/include
SRC=strutil.c
CXXFLAGS= -c \
	-Wall \
	-Wextra \
	-pedantic \
	-Wvla \
	-fPIC \
	-O2

CXXFLAGS_TEST= -Wall \
	-Wextra \
	-pedantic \
	-Wvla \
	-O2

all: strutil.o
	gcc -shared -o libstrutil.so strutil.o

install:
	cp -v strutil.h $(INCDIR)
	cp -v libstrutil.so $(DESTDIR)
	chmod 0755 $(DESTDIR)/libstrutil.so
	ldconfig

strutil.o:
	$(CXX) $(CXXFLAGS) $(SRC) -o strutil.o

uninstall:
	rm -v $(DESTDIR)/libstrutil.so
	rm -v $(INCDIR)/strutil.h

clean:
	rm strutil.o
	rm libstrutil.so
	rm test

test:
	gcc strutil.c -o test $(CXXFLAGS_TEST)