# Makefile for compiling C project (Cross-platform)

# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del
    EXEC = main.exe
else
    RM = rm -f
    EXEC = main
endif

# Variables
CC = gcc
CFLAGS = -g -O2
SRC = DH.c test.c rand.c array_func.c calc_operations.c basic_func.c main.c
# Explicitly define OBJ files
OBJ = $(patsubst %.c, %.o, $(SRC))

# Default goal
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	$(RM) $(OBJ) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run