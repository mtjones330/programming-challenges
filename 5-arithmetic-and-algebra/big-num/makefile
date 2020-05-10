CC := g++
CPPFLAGS := -std=c++11 -Wall -Wextra -Werror -g
SRCDIR := src
MAINDIR := $(SRCDIR)/main
TESTDIR := $(SRCDIR)/test
OBJDIR := build
BINDIR := bin
OBJS := $(addprefix $(OBJDIR)/,big-num-tests.o big-num.o)

all: $(OBJS) | $(BINDIR)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(BINDIR)/big-num-tests

$(OBJDIR)/big-num-tests.o: $(TESTDIR)/big-num-tests.cpp $(OBJDIR)/big-num.o
	$(CC) $(CPPFLAGS) -c $(TESTDIR)/big-num-tests.cpp -o $(OBJDIR)/big-num-tests.o

$(OBJDIR)/big-num.o: $(MAINDIR)/big-num.cpp $(MAINDIR)/big-num.h
	$(CC) $(CPPFLAGS) -c $(MAINDIR)/big-num.cpp -o $(OBJDIR)/big-num.o

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf build bin