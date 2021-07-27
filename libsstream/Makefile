\GCC=gcc
DEBUG=-g -Wall

OBJDIR=./obj
INCDIR=./include
SRCDIR=./src
LIBDIR=./lib
TESTDIR=./test

reqdirs:
	if [ ! -d $(OBJDIR) ]; then
		mkdir $(OBJDIR)
	fi
	if [ ! -d $(LIBDIR) ]; then
		mkdir $(LIBDIR)
	fi
	if [ ! -d $(TESTDIR) ]; then
		mkdir $(TESTDIR)
	fi

$(OBJDIR)/libsstream.o : $(SRCDIR)/libsstream.c $(INCDIR)/libsstream.h reqdirs
	$(GCC) $(DEBUG) -c -o $(OBJDIR)/libsstream.o $(SRCDIR)/libsstream.c -I$(INCDIR)

libsstream: $(OBJDIR)/libsstream.o
	ar rcs $(LIBDIR)/libsstream.a $(OBJDIR)/libsstream.o

test: libsstream $(SRCDIR)/testlib.c
	$(GCC) $(DEBUG) -o $(TESTDIR)/testlib $(SRCDIR)/testlib.c -I$(INCDIR) -L$(LIBDIR) -lsstream

clean:
	rm $(LIBDIR)/*.a
	rm $(OBJDIR)/*.o
	rm $(TESTDIR)/*
