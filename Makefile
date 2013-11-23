# Mostly 'borrowed' from
# http://www.puxan.com/Computers/Howto-write-generic-Makefiles
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

# Declaration of variables
CC = g++
CC_FLAGS = -w

OBJECT_DIR = obj

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# File names
EXEC = sfml-tetris
SOURCES = $(wildcard *.cpp)
OBJ = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst %,$(OBJECT_DIR)/%,$(OBJ))

# Main target
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(CC_FLAGS) $(LIBS)

# To obtain object files
$(OBJECT_DIR)/%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

$(OBJECTS): | $(OBJECT_DIR)

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECT_DIR)/*.o

