#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>
#include <readTamanho.h>

void size_printDataBase(FILE *fp, int n) {
	t_field aux; 
	char c, keepPrinting;
	int i, record_size; 

	// Read every record
	for (i = 0; !feof(fp); i++) {
		
	    fread(&c, sizeof(char), 1, fp);
		if(!feof(fp)) {		
			
			fseek(fp, -1, SEEK_CUR);
		
			// Reads the size of the register
			fread(&record_size, sizeof(int), 1, fp);

			// Read the fields
			aux = readFields(fp);

			// Print them
			printField(aux, i);
			
			// Free the memory
			freeFields(aux);
			
			// Asks the user to press enter to continue
			keepPrinting = userContinue();
			if (keepPrinting == 'c') {
				printf("Abortando... ");
				break;
			}
		} 
	}

	// Make the file pointer return to the begging of the file
	rewind(fp);
}


/* Finds a given field given ints position. */
t_field size_findRecord(FILE *fp, int n, int offset) {
	t_field aux;
	int record_size, i = 0;

	for (i = 0; i < offset; i++) {
		// Read's the record's size
		fread(&record_size, sizeof(int), 1, fp);
		
		aux = readFields(fp);
		freeFields(aux);	
	}

	// Reads the size of the wanted register
	fread(&record_size, sizeof(int), 1, fp);

	// Read the fields
	aux = readFields(fp);

	return aux;
}


void size_printRecord(FILE *fp, int n, int offset) {
	t_field aux;

	// If the offset isn't valid, just return
	if (offset < 0 || offset >= n) {
		printf("Por favor digite um número de registro válido\n");
		return;
	}
	
	// Read the fields from the requested offset
	aux = size_findRecord(fp, n, offset);
	
	// Prints it
	printField(aux, offset);
	
	// Frees used memory
	freeFields(aux);

	// Make the file pointer return to the begging of the file
	rewind(fp);
} 
