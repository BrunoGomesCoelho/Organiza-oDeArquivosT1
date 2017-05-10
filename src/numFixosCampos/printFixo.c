#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <utils.h>


void fixed_printDataBase(FILE *fp, int n) {
	t_field aux; 
	int i; 
	char keepPrinting;

	// Read every record
	for (i = 0; !feof(fp); i++) {

		// Read the fields
		aux = readFields(fp);

		if(!feof(fp)) {
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
t_field fixed_findRecord(FILE *fp, int n, int offset) {
	t_field aux;

	// Go to the offset-th record
	fseek(fp, calculateRecordSize(aux) * offset, SEEK_SET);

	// Read the fields
	aux = readFields(fp);
	
	return aux;
}


void fixed_printRecord(FILE *fp, int n, int offset) {
	t_field aux;

	// If the offset isn't valid, just return
	if (offset < 0 || offset >= n) {
		printf("Please, request a valid register number\n");
		return;
	}

	// Go to the offset-th record
	fseek(fp, calculateRecordSize(aux) * offset, SEEK_SET);

	// Read the fields
	aux = readFields(fp);

	// Print them
	printField(aux, offset);
	
	// Frees used memory
	freeFields(aux);

	// Make the file pointer return to the begging of the file
	rewind(fp);
} 


/* Prints a record given its number 
void fixed_printRecord(FILE *fp, int n, int offset) {
	t_field aux;

	// If the offset isn't valid, just return
	if (offset < 0 || offset >= n) {
		printf("Please, request a valid register number\n");
		return;
	}

	// Reads the correct record
	aux = fixed_findRecord(fp, n, offset);
	
	// If the register was not found, return to the main menu
	if(!found) {
		printf("Por favor digite um número de registro válido! Voltando ao menu\n");
		return;
	}

	// Print them
	printField(aux, offset);
	
	// Frees used memory
	freeFields(aux);

	// Make the file pointer return to the begging of the file
	rewind(fp);
} */
