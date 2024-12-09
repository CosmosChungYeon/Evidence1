# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC = main.exe
    NULL_DEVICE = nul
else
    RM = rm -f
    EXEC = main
    NULL_DEVICE = /dev/null
endif

# Variables
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O2 -g
SRC = DH.c test.c rand.c array_func.c calc_operations.c basic_func.c main.c
OBJ = $(patsubst %.c, %.o, $(SRC))

# Default goal
all: $(EXEC)

# Link object files to create the executaWble
$(EXEC): $(OBJ)
	@echo "Linking files into $(EXEC)..."
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Compile source files into object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	@echo "Cleaning up..."
	$(RM) $(OBJ) $(EXEC) 2> $(NULL_DEVICE) || true

# Run the program
run: $(EXEC)
	@echo "Running the program..."
	./$(EXEC)

# Test target for checking the compilation environment
test:
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Source Files: $(SRC)"
	@echo "Object Files: $(OBJ)"

.PHONY: all clean run test