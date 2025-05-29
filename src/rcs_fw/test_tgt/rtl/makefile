SRC_DIR := ./src
INCLUDEDIRS := ./inc
INCLUDES := $(foreach inc, $(INCLUDEDIRS), -I$(inc))
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -shared
CPPFLAGS := -fPIC

fw_so.so:$(OBJ_FILES)
	g++ $(LDFLAGS) -o fw_sim.so $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	g++ $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf *.so	
