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
# -I <searchpath to include files>
# -L <searchpath to the lib file>
# -l<thelibname>

# Compiler
CC = gcc
CXX = g++

# Flags
# CFLAGS = -g -Wall -O3
CFLAGS = -g -Wall -O3 -fPIC
CXXFLAGS = $(CFLAGS)

# Commands
RM = rm -f

# Files
TARGET = main
SRC_H = mapper.h
SRC_CC = main.cc mapper.cc mapper_graphics.cc
OBJS = $(subst .h,.o, $(SRC_H)) $(subst .cc,.o, $(SRC_CC)) *.exe

# Rules
# all: $(TARGET)

$(TARGET): main.cc mapper.cc mapper_graphics.cc mapper.h mapper_graphics.h
	$(CXX) $(CXXFLAGS) main.cc mapper.cc mapper_graphics.cc -o main  -Wl,--allow-multiple-definition -I"C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\include\SDL2" -L"C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\lib" -lmingw32 -lSDL2main -lSDL2

# $(TARGET): main.cc mapper.o mapper_graphics.o mapper.h mapper_graphics.h
# 	$(CXX) $(CXXFLAGS) main.cc mapper. mapper_graphics.o -o main  -Wl,--allow-multiple-definition
# mapper.o: mapper.cc mapper.h
# 	$(CXX) $(CXXFLAGS) mapper.cc -o mapper.o 
# mapper_graphics.o: mapper_graphics.cc mapper_graphics.h
# 	$(CXX) $(CXXFLAGS) mapper_graphics.cc -o mapper_graphics.o  -I"C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\include\SDL2" -L"C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\lib" -lmingw32 -lSDL2main -lSDL2

# all: $(TARGET)
	
# $(TARGET): main.cc mapper.o mapper_graphics.o
# 	$(CXX) $(CXXFLAGS) -o main main.cc mapper.o mapper_graphics.o -Wl,--allow-multiple-definition
# mapper.o: mapper.h mapper.cc
# 	$(CXX) $(CXXFLAGS) -o mapper.o mapper.cc mapper.h
# mapper_graphics.o: mapper_graphics.cc mapper_graphics.h
# 	$(CXX) $(CXXFLAGS) -o mapper_graphics.o mapper_graphics.cc mapper_graphics.h -I./SDL/x86_64-w64-mingw32/include/SDL2 -L./SDL/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2


# i686-w64-mingw32
# $(CXX) mapper_graphics.cc -I./SDL/x86_64-w64-mingw32/include/SDL2 -L./SDL/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -o mapper_graphics.o
# `pkg-config --cflags --libs sdl`
# $(CC) -c mapper_graphics.cc -I./SDL/x86_64-w64-mingw32/include/SDL2 -L./SDL/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -o mapper_graphics.o
# $(CC) mapper_graphics.cc -I./SDL/x86_64-w64-mingw32/include/SDL2 -L./SDL/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2
# $(CXX) $(CXXFLAGS) -o mapper_graphics.o mapper_graphics.cc -I"C:/Program Files/SDL2-2.0.9/include"  -L"C:/Program Files/SDL2-2.0.9/lib/x64" -L"SDL2main" -L"SDL2" -L"SDL"



clean :
	$(RM) $(OBJS)
