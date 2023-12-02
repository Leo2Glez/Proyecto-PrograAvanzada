#OBJS specifies which files to compile as part of the project
SRC_DIR = src
TEMP_DIR = temp
BIN_DIR = bin
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(TEMP_DIR)/%.o,$(SRCS))
OBJ_NAME = $(BIN_DIR)/pongo

# Flags for linking
LINK_FLAGS =-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -Wnarrowing -w -Wl,-subsystem,windows 

#This is the target that compiles our executable
$(OBJ_NAME) : $(OBJS) 
	g++ -std=c++17 -g $(OBJS) -I$(INCLUDE_DIR) $(LINK_FLAGS) -o $(OBJ_NAME)

all : $(OBJ_NAME)

run: $(OBJ_NAME)
	$(OBJ_NAME)

$(TEMP_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -c $< -o $@ -I$(INCLUDE_DIR)

.PHONY: clean
clean:
	rm -f $(OBJS) $(OBJ_NAME)
