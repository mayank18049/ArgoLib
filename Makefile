# TODO ADD BASIC COMPILAION FOR ARGOLIB
# EXECUTABLES
CC = gcc
MD = mkdir
# DIRECTORIES
INCLUDES = -I./include -I$(ARGOBOTS_INSTALL_DIR)/include -I./include/scheds -I./include/utils
BUILDDIR = ./lib
SRC = ./src
SCHED_SRC = $(SRC)/scheds
# CFLAGS
# OPT = -O3
# LIBS = -largolib -labt
CFLAGS  = --shared -fpic 
# the build target executable
TARGET = argo

# RULES
all: $(BUILDDIR)/lib$(TARGET).so

$(BUILDDIR)/lib$(TARGET).so:
	mkdir -p $(BUILDDIR)	
	$(CC) $(INCLUDES) $(CFLAGS) -o $(BUILDDIR)/lib$(TARGET).so $(SRC)/$(TARGET)lib.c $(SCHED_SRC)/customscheduler.c

.phony:
clean:
	rm -rf $(BUILDDIR)
