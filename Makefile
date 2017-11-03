PROJ_NAME = sums

SRC_DIR = src
BIN_DIR = bin

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow --pedantic-errors -std=c11 -g

$(BIN_DIR)/$(PROJ_NAME): $(SRC_DIR)/*.c
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm $(BIN_DIR)/* -rf
