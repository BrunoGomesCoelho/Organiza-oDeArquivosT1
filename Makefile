################################ VARIABLES ####################################

CC=gcc
CFLAGS = -g -Wall
# Add the files that need to be compiled, like: src/file_name.c
SRCS= src/main.c src/searchFieldMain.c src/printRegFieldMain.c src/utils.c src/inputFieldMain.c src/indicadorTamanho/* src/delimitador/*  src/numFixosCampos/*
INCLUDE=./include
EXEC=trabalho
OUTPUT=answer.dat

###############################################################################

all: compile

compile:
	$(CC) $(CFLAGS) -I$(INCLUDE) $(SRCS) -o $(EXEC)

run: clear
	./$(EXEC)

clear:
	# Uncomment the next line if its the not the first time the program is being run.
	#rm $(EXEC) $(OUTPUT)

