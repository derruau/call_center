# DOESN'T WORK FOR NOW

CC=gcc
RM=rm

SRC_PATH=src/
BUILD_PATH=build/
BIN_PATH=bin/

CFLAGS= -Wall
LDFLAGS=

FILES=($wildcard $(SRC_PATH)*.c)
OBJFILES=($wildcard $(BUILD_PATH)*.o)
TARGET=call_center

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(BIN_PATH)$(TARGET) $(BUILD_PATH)$(OBJFILES) $(LDFLAGS)

$(OBJFILES): $(FILES)
	$(CC) $CFLAGS -c $(BUILD_PATH)$(OBJFILES) $(SRC_PATH)$(FILES) 

.PHONY: clean
clean:
	$(RM) build/*.o