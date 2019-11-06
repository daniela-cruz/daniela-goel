CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g

OBJ_DIR:= ../../obj

INCLUDE_DIR:= ../person_list ../so_list ../dll
SRC_DIR:=../../src

DEPENDENCIES:= $(addprefix $(OBJ_DIR)/, dll.o sl.o vector.o person_list.o)

OBJ:= $(addprefix $(OBJ_DIR)/, pq.o)


all: pq_test.out

pq_test.out: pq_test.o $(OBJ) $(DEPENDENCIES)
	$(CC) pq_test.o $(OBJ) $(DEPENDENCIES) -o $@ 
	rm pq_test.o
	
pq_test.o: pq_test.c pq.h $(SRC_DIR)/person_list/person_list.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIR:%=-I %)

$(OBJ_DIR)/pq.o: pq.c pq.h $(SRC_DIR)/so_list/sl.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIR:%=-I %)

.PHONY:
	clean
clean:
	rm pq_test.out $(OBJ)


