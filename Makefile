CC = gcc
CFLAGS = -g -Wall

TARGET = gcd
SRCS = gcd.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
	@echo compiling done

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	
