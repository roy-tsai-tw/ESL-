SYSTEMC_DIR = /usr/local/systemc-2.3.3
TARGET     = dma
BUILDFLAGS  = -g3
CXX         = g++ -pthread
INCFLAGS    = -I. -I${SYSTEMC_DIR}/include
LDFLAGS     = -L${SYSTEMC_DIR}/lib-linux64 -lsystemc -lm
SRC_CPPHEAD = dma
SRC_CPPHEAD2 = cpu
SRC_CPPHEAD3 = memory
SRC_CPP     = $(SRC_CPPHEAD:=.cpp} $(SRC_CPPHEAD2:=.cpp} $(SRC_CPPHEAD3:=.cpp} 
MAIN        = main.cpp
OBJECTS     = $(SRC_CPPHEAD:=.o) $(SRC_CPPHEAD2:=.o) $(SRC_CPPHEAD3:=.o)

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
    
 
