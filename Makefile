CC				= g++
CC_FLAGS 		= -g -Wall -std=c++17
BUILD_DIR		= ./bin
SRC_DIR			= ./src


build:
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/gitc $(SRC_DIR)/gitc.cpp
	@echo "Build Complete"

clean:
	rm -r $(BUILD_DIR)/*

run:
	$(BUILD_DIR)/gitc