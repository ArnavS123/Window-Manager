CC = gcc
CFLAGS = -std=c11 -g

SRCS = pa1.c
OBJS = $(SRCS:.c=.o)
TARGET = pa1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) *~
