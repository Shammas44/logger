# TIPS 
# ===========================
#
# enable core
# 	ulimit -c unlimited
#
# disable core
# 	ulimit -c 0
#
# debug thread with following compiler flag:
# 	-fsanitize=thread
#
# ===========================

# Library name
# ---------------------------
LIB_NAME = logger

# FLAGS
# ---------------------------
CC = gcc
FLAGS = -Wall -Wextra -Werror -g

# Directories
# ---------------------------
SRC_DIR = src
INC_DIR = src/include
BIN_DIR = bin

# Include directories
# ---------------------------
INC_DIRS = $(INC_DIR)
INC = $(foreach dir,$(INC_DIRS),-I $(dir))

# Library sources
# ---------------------------
LIB_SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_OBJS = $(LIB_SRC_FILES:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

# Main application source files
# ---------------------------
MAIN_SRC_FILES = main.c
MAIN_OBJS = $(MAIN_SRC_FILES:%.c=$(BIN_DIR)/%.o)

# Main application executable
# ---------------------------
MAIN_EXEC = main

# Link against the library
# ---------------------------

# Add the include directory of the librairies to the include path
INC_LIB_DIR:=$(shell find lib -type d -name "include" \; 2>/dev/null)
INC_STATIC_LIB:=$(foreach dir,$(INC_LIB_DIR),-I $(dir))

# Add the bin directory of the librairies to the include path
LIB_BIN_DIR:=$(shell find lib -type d -name "bin" \; 2>/dev/null)
INC_STATIC_BIN:=$(foreach dir,$(LIB_BIN_DIR),-L $(dir))

# Add the librairies to the include path
LIBS_BASENAME:= $(shell find lib -mindepth 1 -maxdepth 1 -type d -exec basename {} \; 2>/dev/null)
INC_LIBS:=$(foreach dir,$(LIBS_BASENAME),-l $(dir))

EXTRA_LIBS = -l ssl -l crypto
LIBS = $(INC_STATIC_BIN) $(INC_STATIC_LIB) $(INC_LIBS) $(EXTRA_LIBS) 
LINK = -L $(BIN_DIR) -l $(LIB_NAME)
INC = -I src/include -I /usr/local/include

# Phony targets
# ---------------------------
.PHONY: all library clean_o clean_bin clean bear main exec

# Targets
# ---------------------------

#default target
all: library

# Generate compile_commands.json file for clangd
bear:
	make clean; bear -- make all

# Lib shortcut target
library: lib$(LIB_NAME).a

# Rule to build library
lib$(LIB_NAME).a: $(LIB_OBJS)
	ar rcs $(BIN_DIR)/$@ $^

# Rule to build library object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

# Remove every object files and binary files
clean: clean_o clean_bin

# Remove every object file in the project
clean_o: 
	@echo "cleaning..."
	find . -name "*.o" -delete

# Remove every exectuable file in the root directory
clean_bin:
	find ./$(BIN_DIR) -type f -perm +111 -maxdepth 1 -delete;
	find ./$(BIN_DIR)/*.a -delete   

# Rule to build main application
main: library main.o
	$(CC) $@.c -o $(BIN_DIR)/$@ $(INC) $(LINK) $(LIBS)

# Rule to build main application object files
main.o: main.c
	$(CC) $(INC) -c $< -o $@

# Rule to execute the main application
exec: main
	./bin/main
