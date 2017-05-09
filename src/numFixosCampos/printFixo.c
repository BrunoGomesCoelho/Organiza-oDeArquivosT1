#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>

/*
	
	1 dominio 			string
	2 documento 		string
	3 nome 				string
	4 cidade			string
	5 uf 				string
	6 dataHora 			string
	7 dataHoraAtuli 	string
	8 ticket 			string

*/

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
