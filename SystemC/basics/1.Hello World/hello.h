/********************************

Title: Hello World
Originated from (http://www.asic-world.com/systemc/first1.html)
Author: Roy Tsai
Date: Mar. 19, 2021

********************************/

//My first program in SystemC.

#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include "systemc.h"

SC_MODULE(hello_world){ //"hello_world" is the module name
	
	SC_CTOR(hello_world){}
	
	void hello_proc();
};

#endif