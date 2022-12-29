# ArgoLib
Simple fork join wrapper for C/C++ which uses Argobots ULTs.
TODOs
Work with lambdas

ADD $(ARGOLIB_INSTALL_DIR) = /path/to/current/directory
ADD $(ARGOBOTS_INSTALL_DIR) = /path/to/argobots/install
ADD $(LD_LIBARAY_PATH) = $(ARGOBOTS_INSTALL_DIR)/lib:$(LD_LIBRARY_PATH)
ADD $(LD_LIBARAY_PATH) = $(ARGOLIB_INSTALL_DIR)/lib:$(LD_LIBRARY_PATH)
make 
cd examples/fibonacci/ && make && ./fibonacci.out
