# Hello_World

This is the first program in SystemC.

## Getting Started

These instructions will let you know the basic idea of what SystemC is.

### Prerequisites

You need to install SystemC and GCC/G++ Compiler first. 
* [Download SystemC](https://www.accellera.org/downloads/standards/systemc)

### A simple code

This example is from "asic-world.com".

```
  1 // All systemc modules should include systemc.h header file
  2 #include "systemc.h"
  3 // Hello_world is module name
  4 SC_MODULE (hello_world) {
  5   SC_CTOR (hello_world) {
  6     // Nothing in constructor 
  7   }
  8   void say_hello() {
  9     //Print "Hello World" to the console.
 10     cout << "Hello World.\n";
 11   }
 12 };
 13 
 14 // sc_main in top level function like in C++ main
 15 int sc_main(int argc, char* argv[]) {
 16   hello_world hello("HELLO");
 17   // Print the hello world
 18   hello.say_hello();
 19   return(0);
 20 }
```

You may want to separate this example into 3 parts, i.e. hello.h, hello.cpp, and main.cpp.
It will look like the following code:

1.hello.h
```
#include "systemc.h"

SC_MODULE(hello_world){ //"hello_world" is the module name
	
	SC_CTOR(hello_world){}
	
	void hello_proc();
};
```

2.hello.cpp
```
#include "hello.h"

void hello_world::hello_proc(){ //Process
		
		std::cout << "Hello World.\n" << endl;
		
	}
```

3.main.cpp

```
#include "hello.h"
//sc_main always in top_level
int sc_main(int argc, char* argv[]){
	
	hello_world h1("HELLO");
	h1.hello_proc();
	
	return (0);
}
```

After Compiling, you may find some problems.

```
/tmp/ccHm0lx3.o: In function `sc_main':
main.cpp:(.text+0x3c): undefined reference to `hello_world::hello_world(sc_core::sc_module_name)'
collect2: error: ld returned 1 exit status
make: *** [hello] Error 1
```

### Solving this problem.

Place an "Include-guard" in hello.h as below,

```
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include "systemc.h"

SC_MODULE(hello_world){ //"hello_world" is the module name
	
	SC_CTOR(hello_world){}
	
	void hello_proc();
};

#endif
```

Finally you solved.

```
[Newbie@ helloworld]$ make
g++ -pthread -c hello.cpp -I/usr/systemc/include
hello building...
g++ -pthread -I/usr/systemc/include main.cpp hello.o -L/usr/systemc/lib-linux64 -lsystemc -lm -o hello

hello build done successfully...
```
Execute it:
```
[Newbie@ helloworld]$ ./hello

        SystemC 2.3.3-Accellera --- Mar 15 2021 22:20:55
        Copyright (c) 1996-2018 by all Contributors,
        ALL RIGHTS RESERVED
Hello World.

```
### The make file I used
You only need to change LIB_DIR, INC_DIR, TARGET, and SRC_CPPHEAD.
```
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
```

### The end of this readme.md
