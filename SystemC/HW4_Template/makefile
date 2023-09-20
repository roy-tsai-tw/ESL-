#
#  Makefile for Assignment 4
#
#  by Alan Su
#  alansuphd@mail.ncku.edu.tw
#
#  modified by Tsung-Ying(Roy) Tsai

CC = g++
PCFLAG = -O1 -Wall -c
POFLAG = -O1 -Wall
HDR = Node.h List.h
SRC = main.cpp
OBJ = main.o
TARGET = list

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(POFLAG) $(LIB) $(OBJ) -o $@

clean:
	rm $(OBJ)
	rm $(TARGET)
