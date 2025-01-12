# Define directory paths
SRC         := ./src
BIN         := ./bin
BUILD_DIR   := ./build
INCLUDE     := ./include

# Collect all C source files in the directory
SOURCE_FILES = $(wildcard $(SRC)/*.c)
TMP_SOURCE_FILES := $(SOURCE_FILES:$(SRC)/%=%) # Remove the src/ prefix
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(TMP_SOURCE_FILES:.c=.o)) # Append build/ and .o

###########################################################################################
#	BUILD
###########################################################################################

all: clean compile

# Compile object files
object: $(OBJ_FILES)

# Compile the 
compile: $(INCLUDE) $(SRC)/json_dsl.cpp $(BIN)
	g++ -I $(INCLUDE) $(SRC)/**.cpp -o $(BIN)/test -std=c++11

compile_ta: $(INCLUDE) $(SRC)/json_dsl.cpp $(BIN)
	g++ -I $(INCLUDE) $(SRC)/**.cpp -DTA_WAY -o $(BIN)/test -std=c++11

# Compile each source file into its object file individually
$(BUILD_DIR)/%.o: $(SRC)/%.c | $(BUILD_DIR)
	g++ -I $(INCLUDE) -c $< -o $@

##########################################################################################
#	UTILITIES
###########################################################################################

# Clean up build artifacts
clean:
	@rm -rf $(BUILD_DIR) $(BIN) .vscode .out

# Ensure that the build and bin directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN):
	mkdir -p $(BIN)
	
