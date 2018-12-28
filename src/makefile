# Aristos Athens
# Makefile for compiling mapper files.

# Notes:
# .o is binary file type.
#
# CC is the c compiler to use.
# CXX is c++ compiler to use.
# CFLAGS are the compilation flags for c source files.
# CXXFLAGS are the compilation flags for c++ source files.
# CPPFLAGS are the flags for the c-preprocessor (used by c and c++).
#
# -o is flag for writing the build output to an output file.
# 	ex: gcc [options] [source files] [object files] -o output file
# -O sets the compiler's optimization level.
# -c compiles source files without linking.
# -g -g requests that the compiler and linker generate and retain source-level
#  	debugging/symbol information in the executable itself. Useful for debugging.
# -Wall show proper warnings

# Compiler
CC = gcc
CXX = g++

# Flags
CFLAGS = -g -Wall -O3
CXXFLAGS = $(CFLAGS)

# Commands
RM = rm -f

# Files
TARGET = main
SRC_H = mapper.h
SRC_CC = main.cc mapper.cc
OBJS = $(subst .h, .o, $(SRC_H)) $(subst .cc, .o, $(SRC_CC))

# Rules
$(TARGET): main.cc mapper.o
	$(CXX) $(CFLAGS) -o main main.cc mapper.o
mapper.o: mapper.h mapper.cc
	$(CXX) $(CFLAGS) -c mapper.cc

clean :
	$(RM) $(OBJS)
