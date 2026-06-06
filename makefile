# Commands:
# mingw32-make       = compile only
# mingw32-make run   = compile and run
# mingw32-make clean = delete build/main.exe

CXX = g++
SRC = src/main.cpp
OUT = build\main.exe
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

all:
	if not exist build mkdir build
	$(CXX) $(SRC) -o $(OUT) $(LIBS)

run: all
	$(OUT)

clean:
	if exist $(OUT) del $(OUT)

.PHONY: all run clean