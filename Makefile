# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
BUILDDIR = build

# Source and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
TARGET = $(BUILDDIR)/asmxplr

.PHONY: all clean run

# Default target
all: $(TARGET)

# Build the executable in build/
$(TARGET): $(OBJS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files to .o in obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj/ directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Create build/ directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean objects and executable
clean:
	rm -rf $(OBJDIR) $(BUILDDIR)

# Run the executable
run: $(TARGET)
	$(TARGET)
