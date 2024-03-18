CC=gcc
CFLAGS=-Wall -Wextra

SRCDIR=cinta
OBJDIR=obj
TESTDIR=tests

SRCFILES := $(shell find $(SRCDIR) -name "*.c")
ALLFILES := $(SRCFILES) $(shell find $(SRCDIR) -name "*.h")
OBJFILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
TESTFILES := $(shell find $(TESTDIR) -name "*.c")


# Create obj directory at the beginning
$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)


.PHONY: format, clean 


test: $(TESTFILES) $(SRCFILES)
	$(CC) -o $@ $^ $(CFLAGS)
	./test
	
format:
	clang-format -i $(SRCDIR)/*.c $(TESTDIR)/*.c include/*.h

clean:
	rm -rf $(OBJDIR) test



