# TODO ADD BASIC COMPILAION FOR PROGRAM
# EXECUTABLES
CC = gcc
MD = mkdir
# DIRECTORIES
INCLUDES = -I$(ARGOBOTS_INSTALL_DIR)/include -I$(ARGOLIB_INSTALL_DIR)/include
LINKOBJ = -L$(ARGOLIB_INSTALL_DIR)/lib -L$(ARGOBOTS_INSTALL_DIR)/lib -largo -labt
# RPATH = -Wl,-rpath=$(ARGOBOTS_INSTALL_DIR)/lib/libabt.so -Wl,-rpath=$(ARGOLIB_INSTALL_DIR)/lib/libargo.so
# CFLAGS
OPT = -O3
# CFLAGS  = --shared -fpic
# the build target executable
TARGET = fibonacci

# RULES
all: $(TARGET).out

$(TARGET).out:	
	$(CC) $(INCLUDES) $(OPT) $(RPATH) $(LINKOBJ)  -o $(TARGET).out $(TARGET).c

.phony:
clean:
	rm -rf $(TARGET).out
