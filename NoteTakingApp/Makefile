FLAGS = -pedantic-errors -std=c++17
GXX = g++

# List my source files
# cpp_engine/src/cpp_search.cpp cpp_engine/src/search_engine.cpp

# Final executable target
TARGET = cpp_search

all: $(TARGET)

# Link all object files to create the final executable
$(TARGET): cpp_engine/src/search_engine.o cpp_engine/src/cpp_search.o
	$(GXX) $(FLAGS) $^ -o $(TARGET)

# Pattern rule to compile .cpp files into .o files
cpp_engine/src/search_engine.o: cpp_engine/src/search_engine.cpp cpp_engine/include/search_engine.h
	$(GXX) $(FLAGS) -c $< -o $@

cpp_engine/src/cpp_search.o: cpp_engine/src/cpp_search.cpp cpp_engine/include/note.h cpp_engine/include/search_engine.h
	$(GXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) cpp_engine/src/cpp_search.o cpp_engine/src/search_engine.o

.PHONY: all clean