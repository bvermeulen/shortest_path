CC=g++
PPYTHON = c:/users/bruno/appdata/local/programs/python/python313
PMPL17 = d:/cpp/matplotlibcpp17
PPYBIND11 = d:/cpp/pybind11
IDIR = -I $(PPYTHON)/include -I $(PMPL17)/include -I $(PPYBIND11)/include -I ./include
LIB = -L $(PPYTHON)/libs -lpython313
CFLAGS=-Wall -g
LFLAGS=-Wall
CVERSION=c++17
SDIR = ./src
BUILD = ./build
SRCFILE = shortest_path_tsp
OBJDIR = ./objects

_OBJ = $(SRCFILE).o csv.o point.o plotpaths.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

$(OBJDIR)/%.o: $(SDIR)/%.cpp
	$(CC) --std=$(CVERSION) -c -o $@ $< $(IDIR) $(CFLAGS)

$(SRCFILE): $(OBJ)
	$(CC) --std=$(CVERSION) -o $(BUILD)/$@ $^ $(LFLAGS) $(LIB)

clean:
	@echo Clean main app object file in $(OBJDIR) and executable in $(BUILD)
	rm $(BUILD)/$(SRCFILE).exe
	rm $(OBJDIR)/$(SRCFILE).o

clean_o:
	@echo Clean all object files in $(OBJDIR) and executable in $(BUILD)
	rm $(OBJDIR)/*.o
	rm $(BUILD)/$(SRCFILE).exe

