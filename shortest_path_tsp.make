CC=g++
PPYTHON = c:/users/bruno/appdata/local/programs/python/python312
PMPL17 = d:/cpp/matplotlibcpp17
PPYBIND11 = d:/cpp/pybind11
IDIR = -I $(PPYTHON)/include -I $(PMPL17)/include -I $(PPYBIND11)/include -I $(PXTL)/include -I $(PXTENSOR)/include -I ./include
LIB = -L $(PPYTHON)/libs -lpython312
CFLAGS=-Wall -g
LFLAGS=-Wall
CVERSION=c++17
SDIR = .\src
BIN = .\bin
SRCFILE = shortest_path_tsp

OBJDIR = .\objects
_OBJ = $(SRCFILE).o csv.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

$(OBJDIR)/%.o: $(SDIR)/%.cpp
	$(CC) --std=$(CVERSION) -c -o $@ $< $(IDIR) $(CFLAGS)

$(SRCFILE): $(OBJ)
	$(CC) --std=$(CVERSION) -o $(BIN)/$@ $^ $(LFLAGS) $(LIB)

clean:
	@echo Clean main app object file in $(OBJDIR) and executable in $(BIN)
	del /Q /F $(BIN)\$(SRCFILE).exe
	del /Q /F $(OBJDIR)\$(SRCFILE).o

clean_o:
	@echo Clean all object files in $(OBJDIR) and executable in $(BIN)
	del /Q /F $(BIN)\$(SRCFILE).exe
	del /Q /F $(OBJDIR)\*.o

