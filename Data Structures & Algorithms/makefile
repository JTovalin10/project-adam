# Define the C++ compiler to use
CXX = g++

# Compiler flags:
# -Wall: turn on all warnings
# -Wextra: turn on extra warnings
# -g: include debugging information
# -std=c++17: enforce the C++17 standard
CXXFLAGS = -Wall -Wextra -g -std=c++17

# Linker flags (not strictly needed for this basic project, but good practice)
LDFLAGS =

# Define the name of the final executable program
TARGET = project-adam

# Define the source files (add all your .cpp files here)
SOURCES = main.cpp

# Define the object files (automatically generated from sources)
OBJECTS = $(SOURCES:.cpp=.o)

# ----------------- BUILD RULES -----------------

# The default target (what runs when you just type 'make')
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

# Rule to compile each .cpp file into a .o object file
# The header file is implicitly used by main.cpp, so it doesn't need to be listed here.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ----------------- CLEAN -----------------

# Rule to clean up the directory by removing compiled files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Tell make that 'all' and 'clean' are not files
.PHONY: all clean