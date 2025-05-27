CC=g++
PPYTHON = /home/bvermeulen/.pyenv/versions/3.13.3
PMPL17 = /home/bvermeulen/Python/cpp/matplotlibcpp17
PPYBIND11 = /home/bvermeulen/Python/cpp/pybind11
IDIR = -I $(PPYTHON)/include/python3.13 -I $(PMPL17)/include -I $(PPYBIND11)/include -I ./include
LIB = -L$(PPYTHON)/lib -lpython3.13
CFLAGS=-Wall -g -fvisibility=hidden
LFLAGS=-Wall
CVERSION=c++17
SDIR = ./src
BUILD = ./build
SRCFILE = shortest_path_tsp
OBJDIR = ./objects
NAME_EXE = $(BUILD)/$(SRCFILE)
NAME_OBJ = $(OBJDIR)/$(SRCFILE).o

_OBJ = $(SRCFILE).o args_handle.o csv.o point.o plotpaths.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

$(OBJDIR)/%.o: $(SDIR)/%.cpp
	$(CC) --std=$(CVERSION) -c -o $@ $< $(IDIR) $(CFLAGS)

$(SRCFILE): $(OBJ)
	$(CC) --std=$(CVERSION) -o $(BUILD)/$@ $^ $(LFLAGS) $(LIB)

.PHONY: clean
clean:
	echo "Clean $(SRCFILE) object file in $(OBJDIR) and executable in $(BUILD)"
	rm $(NAME_OBJ)
	rm $(NAME_EXE)

.PHONY: clean_all
clean_all:
	echo "Clean all object files in $(OBJDIR) and $(SRCFILE).exe in $(BUILD)"
	rm $(OBJDIR)/*.o
	rm $(NAME_EXE)
