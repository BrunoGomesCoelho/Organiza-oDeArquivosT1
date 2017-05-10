#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>


void delimiter_printDataBase(FILE *fp, int n) {
	t_field aux;
	char delim, keepPrinting;
	int i;

	for(i = 0; !feof(fp); i++){

		// Read the fields
		aux = readFields(fp);

		// If the file is not over yet
		if (!feof(fp)) {
			// Print them
			printField(aux, i);
				
			// Frees used memory
			freeFields(aux);
			
			// Read the delimiter
			fread(&delim, sizeof(char), 1, fp);
			
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
t_field delimiter_findRecord(FILE *fp, int n, int offset) {
	t_field aux;
	char delim;
	int i = 0;

	for (i = 0; i < offset; i++) {
		// Read the fields
		aux = readFields(fp);

		// Frees used memory
		freeFields(aux);
		
		// Read the delimiter
		fread(&delim, sizeof(char), 1, fp);
		
	}

	// Read the fields from the requested offset
	aux = readFields(fp);

	return aux;
}


/* Prints a record given its number */
void delimiter_printRecord(FILE *fp, int n, int offset) {
	t_field aux;
	
	// Reads the correct record
	aux = delimiter_findRecord(fp, n, offset);
	
	// If the offset isn't valid, return to the main menu
	if (offset < 0 || offset >= n) {
		printf("Por favor digite um número de registro válido! Voltando ao menu\n");
		return;
	}

	// Prints it
	printField(aux, offset);

	// Frees used memory
	freeFields(aux);	

	// Make the file pointer return to the begging of the file
	rewind(fp);
} 


