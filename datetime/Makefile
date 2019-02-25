CXXFLAGS=-g -Wall -O0

BINARIES=date_test

all:$(BINARIES)

date_test: Date.h Date.cc Date_test.cc

$(BINARIES):
	g++ $(CXXFLAGS) $(filter %.cc, $^) -o $@


clean:
	rm -rf $(BINARIES)