# Makefile for compiling C project

# 변수 정의
CC = gcc
CFLAGS = -g
SRC = basic_func.c main.c
OBJ = $(SRC:.c=.o)
EXEC = main.exe

# 기본 목표
all: $(EXEC)

# 실행 파일 생성
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# 객체 파일 생성
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean 목표: 생성된 파일 삭제
clean:
	del $(OBJ) $(EXEC)

# run 목표: 프로그램 실행
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
