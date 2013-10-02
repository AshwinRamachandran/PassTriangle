CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-Wall

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: PassTriangle

PassTriangle: $(OBJS)
	$(CXX) $(CPPFLAGS) -o PassTriangle $(OBJS)

main.o: main.cpp

clean: dist-clean
	$(RM) $(OBJS)

dist-clean:
	$(RM) PassTriangle
