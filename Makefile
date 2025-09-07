CXX = clang++ -std=c++23
CFLAGS = -O2 
NAME_PROJECT = fu

SRC = src/main.cpp src/init.cpp src/add.cpp

default: build

.PHONY: run
run: build
	./$(NAME_PROJECT)
	
.PHONY: build
build:
	@echo "Start build"
	$(CXX) $(CFLAGS) -o $(NAME_PROJECT) $(SRC)

.SILENT: clean
.PHONY: clean
clean:
	rm -rf $(NAME_PROJECT)
	rm -rf .fu
	