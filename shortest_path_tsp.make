SHELL := powershell.exe 
	.SHELLFLAGS := -NoProfile -Command  
CC=g++
PPYTHON = c:/users/bruno/appdata/local/programs/python/python314
PMPL17 = d:/cpp/matplotlibcpp17
PPYBIND11 = d:/cpp/pybind11
IDIR = -I $(PPYTHON)/include -I $(PMPL17)/include -I $(PPYBIND11)/include -I ./include
LIB = -L $(PPYTHON)/libs -lpython314
CFLAGS= -Wall -g -fvisibility=hidden
LFLAGS= -Wall 
CVERSION=c++17
SDIR = ./src
BUILD = ./build
SRCFILE = shortest_path_tsp
OBJDIR = ./objects
NAME_EXE = $(BUILD)/$(SRCFILE).exe
NAME_OBJ = $(OBJDIR)/$(SRCFILE).o

_OBJ = $(SRCFILE).o args_handle.o csv.o point.o plotpaths.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

$(OBJDIR)/%.o: $(SDIR)/%.cpp
	$(CC) --std=$(CVERSION) -c -o $@ $< $(IDIR) $(CFLAGS)

$(SRCFILE): $(OBJ)
	$(CC) --std=$(CVERSION) -o $(BUILD)/$@ $^ $(LFLAGS) $(LIB)

.PHONY: clean
clean:
	@write-host "Clean $(SRCFILE) object file in $(OBJDIR) and executable in $(BUILD)"
	@if (test-path $(NAME_OBJ)) { rm $(NAME_OBJ)} else {write-host "The file $(NAME_OBJ) does not exist"}
	@if (test-path $(NAME_EXE)) { rm $(NAME_EXE)} else {write-host "The file $(NAME_EXE) does not exist"}

.PHONY: clean_all
clean_all:
	@write-host "Clean all object files in $(OBJDIR) and $(SRCFILE).exe in $(BUILD)"
	@rm $(OBJDIR)/*.o
	@if (test-path $(NAME_EXE)) { rm $(NAME_EXE)} else {write-host "The file $(NAME_EXE) does not exist"}
