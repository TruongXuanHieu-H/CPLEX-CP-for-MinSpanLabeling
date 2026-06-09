CPLEXDIR=/opt/ibm/ILOG/CPLEX_Studio222
CONCERTDIR=$(CPLEXDIR)/concert

SYSTEM=x86-64_linux
LIBFORMAT=static_pic

CXX=g++

CXXFLAGS= \
    -std=c++20 \
    -O3 \
    -fPIC \
    -fexceptions \
    -DNDEBUG \
    -DIL_STD \
    -I$(CPLEXDIR)/cplex/include \
    -I$(CONCERTDIR)/include

LDFLAGS= \
    -L$(CPLEXDIR)/cplex/lib/$(SYSTEM)/$(LIBFORMAT) \
    -L$(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

LIBS= \
    -lilocplex \
    -lconcert \
    -lcplex \
    -lm \
    -lpthread \
    -ldl

TARGET=build/cplex_cp

SRC=$(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)