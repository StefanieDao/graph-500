CC = g++
CFLAGS = -g -Wall -std=c++17
TARGET = bfs

all: ${TARGET}

${TARGET}: ${TARGET}.cpp
		${CC} ${CFLAGS} -o ${TARGET} ${TARGET}.cpp
.PHONY: clean
clean:
	rm -rf ${TARGET}
