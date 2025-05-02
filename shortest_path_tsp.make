CC=g++
PPYTHON = c:/users/bruno/appdata/local/programs/python/python313
PMPL17 = c:/data/cpp/matplotlibcpp17
PPYBIND11 = c:/data/cpp/pybind11
IDIR = -I $(PPYTHON)/include -I $(PMPL17)/include -I $(PPYBIND11)/include -I ./include
LIB = -L $(PPYTHON)/libs -lpython313
CFLAGS=-Wall -g -fvisibility=hidden
LFLAGS=-Wall
CVERSION=c++17
SDIR = .\src
BUILD = .\build
SRCFILE = shortest_path_tsp
OBJDIR = .\objects

_OBJ = $(SRCFILE).o args_handle.o csv.o point.o plotpaths.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

$(OBJDIR)/%.o: $(SDIR)/%.cpp
	$(CC) --std=$(CVERSION) -c -o $@ $< $(IDIR) $(CFLAGS)

$(SRCFILE): $(OBJ)
	$(CC) --std=$(CVERSION) -o $(BUILD)/$@ $^ $(LFLAGS) $(LIB)

.PHONY: clean
clean:
	@echo Clean main app object file in $(OBJDIR) and executable in $(BUILD)
	del $(BUILD)\$(SRCFILE).exe
	del $(OBJDIR)\$(SRCFILE).o

.PHONY: clean_o
clean_o:
	@echo Clean all object files in $(OBJDIR) and executable in $(BUILD)
	del $(OBJDIR)\*.o
	del $(BUILD)\$(SRCFILE).exe
