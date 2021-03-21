/********************************

Title: Hello World
Originated from (http://www.asic-world.com/systemc/first1.html)
Author: Roy Tsai
Date: Mar. 19, 2021

********************************/

#include "hello.h"
//sc_main always in top_level
int sc_main(int argc, char* argv[]){
	
	hello_world h1("HELLO");
	h1.hello_proc();
	
	return (0);
}