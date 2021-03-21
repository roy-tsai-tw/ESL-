LIB_DIR=-L/usr/systemc/lib-linux64
INC_DIR=-I/usr/systemc/include
TARGET     = hello
BUILDFLAGS  = -g3
CXX         = g++ -pthread
INCFLAGS    = ${INC_DIR}
LDFLAGS     = ${LIB_DIR} -lsystemc -lm
SRC_CPPHEAD = hello
SRC_CPP     = $(SRC_CPPHEAD:=.cpp}
MAIN        = main.cpp
OBJECTS     = $(SRC_CPPHEAD:=.o)

EXE = $(TARGET)

all: $(EXE)

$(EXE): $(MAIN) $(OBJECTS) $(HEADERS)
	@echo "$@ building..."
	$(CXX) $(INCFLAGS) $(MAIN) $(OBJECTS) $(LDFLAGS) -o $@
	@echo ""
	@echo "$@ build done successfully..."
	@echo ""

%.o:%.cpp %.h
	$(CXX) -c $< $(INCFLAGS)

clean:
	rm -f $(EXE) \
	rm -f *.o
