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
	8 ticket 			int 

*/

void fixed_printDataBase(RECORD_SIZE *size, FILE *fp, int n) {
	char *domain, *document_number, *name, *city, *state, *dateTimeOri;
	char *dateTimeUpd;
	int ticket, i;

	for (i = 0; i < n; i++) {

		// Malloc the strings 
		domain = (char *) malloc(sizeof(char) * size->domain_size); 
		document_number = (char *) malloc(sizeof(char) 
			* size->document_number_size);
		name = (char *) malloc(sizeof(char) * size->name_size); 
		city = (char *) malloc(sizeof(char) * size->city_size);
		state = (char *) malloc(sizeof(char) * size->state_size);
		dateTimeOri = (char *) malloc(sizeof(char) * size->dateTimeOri_size);
		dateTimeUpd = (char *) malloc(sizeof(char) * size->dateTimeUpd_size);

		// Read the field
		fread(domain, sizeof(char), size->domain_size, fp);
		fread(document_number, sizeof(char), size->document_number_size, fp);
		fread(name, sizeof(char), size->name_size, fp);
		fread(city, sizeof(char), size->city_size, fp);
		fread(state, sizeof(char), size->state_size, fp);
		fread(dateTimeOri, sizeof(char), size->dateTimeOri_size, fp);
		fread(dateTimeUpd, sizeof(char), size->dateTimeUpd_size, fp);
		fread(&ticket, sizeof(int), 1, fp);

		// Print the field
		if (strcmp(name, "null")) 
			printf("\t%d - %s\n", i, name);
		if (strcmp(domain, "null")) 
			printf("\t\t\tDomain: \t%s\n", domain);
		if (strcmp(document_number, "null")) 
			printf("\t\t\tDocument Number: \t%s\n", document_number);
		if (strcmp(city, "null")) 
			printf("\t\t\tCity: \t%s\n", city);
		if (strcmp(state, "null")) 
			printf("\t\t\tState: \t%s\n", state);
		if (strcmp(dateTimeOri, "null")) 
			printf("\t\t\tDate and time created: \t%s\n", dateTimeOri);
		if (strcmp(dateTimeUpd, "null")) 
			printf("\t\t\tDate and time last updated: \t%s\n", dateTimeUpd);
		printf("\t\t\tTicket number: \t%d\n", ticket);

		// Free the strings
		free(name);
		free(domain);
		free(document_number);
		free(city);
		free(state);
		free(dateTimeOri);
		free(dateTimeUpd);

	}

	// Make the file pointer return to the begging of the file
	rewind(fp);
}

void fixed_printRecord(RECORD_SIZE *size, FILE *fp, int n, int offset) {
	// char *domain, *document_number, *name, *city, *state, *dateTimeOri;
	// char *dateTimeUpd;

	// Make the file pointer return to the begging of the file
	rewind(fp);
}