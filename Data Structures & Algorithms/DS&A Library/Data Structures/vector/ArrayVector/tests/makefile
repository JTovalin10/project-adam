# Define the C++ compiler to use
CXX = g++

# Compiler flags
# - Wall: turn on all warnings
# -Wextra: turn on extra warnings
# -g: include debugging information
# -std=c++17: enforce C++17 standard
CXXFLAG = -Wall -Wextra -g -std=c++17

# Linked Flags
# LDFLAGS = 

# Define the name of the final executeable program
TARGET = Vector

# Define the source files
SOURCES = 

# DEfine the object files
OBJECTS = $(SOURCES:.cpp=.o)

# --- BUILD RULES ---

# Default target
all: $(TARGET)

# Rule to lnk the object files into the final executable
$(TARGET): $(OBJECTS) $(CXX) $(LDFLAGS)