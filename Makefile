CC				= g++
CC_FLAGS 		= -g -Wall
BUILD_DIR		= ./bin
SRC_DIR			= ./src


build:
	$(CC) $(CC_FLAGS) -o ./bin/gitc $(SRC_DIR)/gitc.cpp
	@echo "Build Complete"

clean:
	rm -r $(BUILD_DIR)/*