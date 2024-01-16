CC=g++
CFLAGS=-I. -Wall -g
DEPS = csv.h
OBJ = shortest_path_tsp.o csv.o

#%.o: %.cpp (DEPS)
%.o: %.cpp
	$(CC) --std=c++17 -c -o $@ $< $(CFLAGS)

shortest_path_tsp: $(OBJ)
	$(CC) --std=c++17 -o $@ $^ $(CFLAGS)

clean_o:
	del $(OBJ)

clean:
	del $(OBJ) shortest_path_tsp.exe

