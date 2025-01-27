# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Include headers
INCLUDES = -I.

# Source files and output executable
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

ifeq ($(OS),Windows_NT)
  EXEC = build/mps-helper.dll
  LDFLAGS = -shared -lwinmm
  CFLAGS += -D_WIN32
  DEL = powershell -ExecutionPolicy Bypass -File helper.ps1
else
  ifeq ($(shell uname),Darwin)
    EXEC = build/libmps-helper.dylib
    LDFLAGS = -shared
    SONAME = -Wl,-install_name,@rpath/libmps-helper.dylib
  else ifeq ($(shell uname),Linux)
    EXEC = build/libmps-helper.so
    LDFLAGS = -shared -Wl,-rpath,'$$ORIGIN'
  endif
  DEL = rm -f $(SRCDIR)/*.o $(EXEC) build
endif


# Default target
all: $(EXEC)

# Link the object files into the final executable
$(EXEC): $(OBJECTS)
	mkdir build
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile each .c file into a .o file
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(EXEC)
		$(CC) $(CFLAGS) test/main.c $(INCLUDES) -o build/test -Lbuild -lmps-helper
# Clean the build
clean:
	$(DEL)