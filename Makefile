APPNAME := BlackJack_App
CC := gcc
CFLAGS := -Wall -O2
OBJDIR := obj

SRCFILES := $(wildcard *.c)
OBJFILES := $(patsubst %.c,obj/%.o,$(SRCFILES))

.PHONY: clean all dirs

all: dirs $(APPNAME)

clean:
	rm -Rf $(OBJDIR) $(APPNAME)

dirs: 
	@mkdir -p $(OBJDIR)

$(APPNAME): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(APPNAME)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
