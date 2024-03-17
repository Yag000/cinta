CC=gcc
CFLAGS=-Wall -Wextra
EXEC=main

SRCDIR=src
OBJDIR=obj
TESTDIR=tests

SRCFILES := $(shell find $(SRCDIR) -name "*.c")
SRCFILES_NO_MAIN := $(filter-out $(SRCDIR)/main.c, $(SRCFILES))
ALLFILES := $(SRCFILES) $(shell find $(SRCDIR) -name "*.h")
OBJFILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
TESTFILES := $(shell find $(TESTDIR) -name "*.c")


# Create obj directory at the beginning
$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)


.PHONY: all, clean 

all: $(EXEC)

main: $(OBJFILES) 
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TESTFILES) $(SRCFILES_NO_MAIN)
	$(CC) -o $@ $^ $(CFLAGS)
	./test
	
format:
	clang-format -i $(SRCDIR)/*.c $(SRCDIR)/**/*.c

clean:
	rm -rf $(OBJDIR) $(EXEC) test



