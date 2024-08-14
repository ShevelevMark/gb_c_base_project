TARGET_NAME := run

CC := gcc
CFLAGS := -std=c11
LFLAGS :=
DEBUG_FLAGS := -O2 -Wall -g -D _DEBUG
RELEASE_FLAGS := -O3

SRC_DIR := ./src
OBJ_DIR := ./obj
INC_DIR := ./inc
BIN_DIR := ./bin
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INC := -I $(INC_DIR)

.PHONY: clean debug release build help

help:
	@echo Run make with one of the two options:
	@echo debug: $(DEBUG_FLAGS)
	@echo release: $(RELEASE_FLAGS)

debug: CFLAGS += $(DEBUG_FLAGS)
release: CFLAGS += $(RELEASE_FLAGS)

debug: build
release: build

build: $(OBJ)
	$(CC) $(OBJ) -o $(BIN_DIR)/$(TARGET_NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -rf ./bin/*
	rm -rf ./obj/*