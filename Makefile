# Makefile for SDL3 program

# Compiler and flags
CXX = gcc
CXXFLAGS = -I/usr/local/include -L/usr/local/lib -lSDL3 -lncurses
SRC = main.c music.c library.c tui.c
OUT = a

# Compile the program
$(OUT): $(SRC)
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS)

# Run the program
run: $(OUT)
	./$(OUT)

# Clean up generated files
clean:
	rm -f $(OUT)
