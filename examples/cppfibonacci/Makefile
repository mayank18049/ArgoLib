# TODO ADD BASIC COMPILAION FOR PROGRAM
# EXECUTABLES
CC = g++
MD = mkdir
# DIRECTORIES
INCLUDES = -I$(ARGOBOTS_INSTALL_DIR)/include -I$(ARGOLIB_INSTALL_DIR)/include
LINKLIB = -L$(ARGOLIB_INSTALL_DIR)/lib -L$(ARGOBOTS_INSTALL_DIR)/lib 
LINKOBJ = -largo -labt
# RPATH = -Wl,-rpath=$(ARGOBOTS_INSTALL_DIR)/lib/libabt.so -Wl,-rpath=$(ARGOLIB_INSTALL_DIR)/lib/libargo.so
# CFLAGS
OPT = -O3 
# CFLAGS  = -fsanitize=address
# the build target executable
TARGET = fibonacci

# RULES
all: $(TARGET).out

$(TARGET).out:	
	$(CC) $(INCLUDES) $(OPT) $(CFLAGS) $(RPATH) $(LINKLIB)  -o $(TARGET).out $(TARGET).cpp $(LINKOBJ)

.phony:
clean:
	rm -rf $(TARGET).out
