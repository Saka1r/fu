CXX = g++ -std=c++17
CFLAGS = -O2 -static 
LIB = -I/src/zlib/ -L/src/zlib/lib/ -lz
NAME_PROJECT = fu

SRC = src/main.cpp src/init.cpp src/add.cpp src/file.cpp src/objects.cpp src/commit.cpp src/back.cpp src/decoder.cpp
OBJ = $(SRC:.cpp=.o)

default: build

.PHONY: run
run: build
	./$(NAME_PROJECT)
	
.PHONY: build
build: $(NAME_PROJECT)

$(NAME_PROJECT): $(OBJ)
	@echo "Linking..."
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

%.o: %.cpp
	@echo "Compiling $<"
	$(CXX) $(CFLAGS) -c $< -o $@

.SILENT: clean
.PHONY: clean
clean:
	rm -rf $(NAME_PROJECT) $(OBJ)
	rm -rf .fu
