CC=gcc
CFLAGS=-Wall -Wextra

SRCDIR=cinta
OBJDIR=obj
EXAMPLEDIR=examples

SRCFILES := $(shell find $(SRCDIR) -name "*.c")
OBJFILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
EXAMPLEFILES := $(shell find $(EXAMPLEDIR) -name "*.c")

# Create obj directory at the beginning
$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

examples: $(EXAMPLEFILES) $(OBJFILES)
	$(CC) -o example $(EXAMPLEFILES) $(OBJFILES) $(CFLAGS)

fmt: format

format:
	clang-format -i $(SRCDIR)/*.c $(EXAMPLEDIR)/*.c $(SRCDIR)/*.h

clean:
	rm -rf $(OBJDIR) example
