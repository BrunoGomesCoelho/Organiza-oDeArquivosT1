################################ VARIABLES ####################################

CC=gcc
CFLAGS = -g -Wall
# Add the files that need to be compiled, like: src/file_name.c
SRCS= src/main.c src/searchFieldMain.c src/printRegFieldMain.c src/utils.c src/inputFieldMain.c src/indicadorTamanho/* src/delimitador/*  src/numFixosCampos/*
INCLUDE=./include
EXEC=trabalho
OUTPUT=answer.dat

###############################################################################

all: clear1 compile

compile:
	$(CC) $(CFLAGS) -I$(INCLUDE) $(SRCS) -o $(EXEC)

run: clear2
	./$(EXEC)


############ FOR DEBUGGING ONLY, REMOVE LATER ############
# Remove "-g" from CFLAGS, only necessary for valgrind.
# VALFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
# just a test

val: $(EXEC)
	valgrind $(VALFLAGS) ./$(EXEC)

clear1:
	# rm $(EXEC) $(OUTPUT)
	find . -type f -name '*~' -delete

clear2:
	# rm $(EXEC) $(OUTPUT)
	# rm "answer.dat"

