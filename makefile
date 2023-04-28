CC = gcc
LDFLAGS = 

SRCS = main.c
OBJS = $(SRCS:.c=.o)

TARGET = dna

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)