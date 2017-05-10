#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>	// strcmp
#include <ctype.h> 	// isdigit

#include <utils.h>


/* Reads input from a given stream (stdin in our case).
	Reads until it finds either the a 'r' or the parameters separator or endLine
	We start off allocating 50 bytes for the input and in case we need more, we increment
	in 50 bytes until the whole message has been read. */
char *readLine(FILE *stream, char separator, char endLine) {
    int i = 0, reallocCount = 0;
    char letter, *string;
    char carriageReturn = '\r';
    string = (char *) malloc(50 * sizeof(char));
    letter = fgetc(stream);


    while (letter != separator && letter != endLine && letter != carriageReturn && letter != EOF) { 
        // Reads until it finds separator, endLine, 'r' or a EOF.
        string[i] = letter;
        i++;
        letter = fgetc(stream);
        if (i >= 50*(reallocCount +1)) { 
            // If there's more characters than we currently have, allocate more
            string = (char *) realloc(string, 50 * (reallocCount +2)*sizeof(char));
            reallocCount++;
        }
    } // i leaves the while with the size of the string
    string = realloc(string, (i+1)*sizeof(char)); // Removes uncessary bytes
    string[i] = '\0'; // Adds a \0 to the end.
    return string;
}


/* Reads all the fields in a register. Does not read the register size, possible delimiters, etc */
t_field readFields(FILE *fp) {
    int domain_size, name_size, city_size, state_size;
    t_field field;
    char c; 

    fread(&c, sizeof(char), 1, fp);

    if (!feof(fp)) {
        fseek(fp, -1, SEEK_CUR);

        // Reads the domain
        fread(&domain_size, sizeof(int), 1, fp);
        field.domain = (char *) malloc(sizeof(char) * (domain_size));
        fread(field.domain, sizeof(char), domain_size, fp);
        
        // Reads the document number
        field.document_number = (char *) malloc(sizeof(char) * (SIZE_FIXED));
        fread(field.document_number, sizeof(char), SIZE_FIXED, fp);

        // Reads the name 
        fread(&name_size, sizeof(int), 1, fp);
        field.name = (char *) malloc(sizeof(char) * (name_size));
        fread(field.name, sizeof(char), name_size, fp);

        // Reads the state name
        fread(&state_size, sizeof(int), 1, fp);
        field.state = (char *) malloc(sizeof(char) * (state_size));
        fread(field.state, sizeof(char), state_size, fp);
        
        // Reads the city name
        fread(&city_size, sizeof(int), 1, fp);
        field.city = (char *) malloc(sizeof(char) * (city_size));
        fread(field.city, sizeof(char), city_size, fp);

        // Reads the date and time when the domain was created
        field.dateTimeOri = (char *) malloc(sizeof(char) * (SIZE_FIXED));
        fread(field.dateTimeOri, sizeof(char), SIZE_FIXED, fp);

        // Reads the date and time of when the file was last modified
        field.dateTimeUpd = (char *) malloc(sizeof(char) * (SIZE_FIXED));
        fread(field.dateTimeUpd, sizeof(char), SIZE_FIXED, fp);

        // Read the ticket number
        field.ticket = (char *) malloc(sizeof(char) * (SIZE_FIXED));
        fread(field.ticket, SIZE_FIXED, 1, fp);
        
    }
    
    return field;
}


/* Frees all the memory used storing a field */
void freeFields(t_field field) {
	free(field.domain);
	free(field.document_number);
	free(field.name);
	free(field.city);
	free(field.state);
	free(field.dateTimeOri);
	free(field.dateTimeUpd);
	free(field.ticket);
}


/* Calculates the size of a register */
int calculateRecordSize(t_field field) {
    int regSize = 0, i;

    for(i = 0; i < 8; i++) {
        if(i == 2 || i == 3 || i == 4 || i == 0) // if variable-sized field
            regSize += field.dataSize[i];
        else
            regSize += SIZE_FIXED;
    }

    return regSize;
}


/* Prints all the fields in a given register */
void printField(t_field field, int offset) {

	printf("\n");
				
	if (strcmp(field.name, "null")) 
		printf("\t%d - \t\t%s\n", offset, field.name);
	if (strcmp(field.domain, "null")) 
		printf("\t\t\tDomain: \t\t\t%s\n", field.domain);
	if (strcmp(field.document_number, "null")) 
		printf("\t\t\tDocument Number: \t\t%s\n", field.document_number);
	if (strcmp(field.city, "null")) 
		printf("\t\t\tCity: \t\t\t\t%s\n", field.city);
	if (strcmp(field.state, "null")) 
		printf("\t\t\tState: \t\t\t\t%s\n", field.state);
	if (strcmp(field.dateTimeOri, "null")) 
		printf("\t\t\tDate and time created: \t\t%s\n", field.dateTimeOri);
	if (strcmp(field.dateTimeUpd, "null")) 
		printf("\t\t\tDate and time last updated: \t%s\n", field.dateTimeUpd);
	if (strcmp(field.ticket, "null"))
		printf("\t\t\tTicket number: \t\t\t%s\n", field.ticket);
	printf("\t\t\t========================================================\n\n");
}


/* Loads the record into t_field struct */
t_field readRecord(FILE *input) {
    char *string, size;
    int i, j;
    t_field field;
    field.data = malloc(sizeof(char *)*8);

    for(i = 0; i < 8; i++) {
        string = readLine(input, ';', '\n');
        size = strlen(string);
        
        // Removes any accented characters from the string
		for(j = 0; j < size; j++) {
			if ( (unsigned char) string[j] == (unsigned char) 0xED) // í
				string[j] = 'i';
			else if ((unsigned char) string[j] == (unsigned char) 0xCD) // Í
				string[j] = 'I';
			else if ((unsigned char) string[j] == (unsigned char) 0xE7) // ç
				string[j] = 'c';
			else if ((unsigned char) string[j] == (unsigned char) 0xC7) // Ç
				string[j] = 'C';
			else if ((unsigned char) string[j] == (unsigned char) 0xE3) // ã
				string[j] = 'a';
			else if ((unsigned char) string[j] == (unsigned char) 0xC3) // Ã
				string[j] = 'A';
			else if ((unsigned char) string[j] == (unsigned char) 0xE1) // á
				string[j] = 'a';				
		}
		
        field.data[i] = string;
        field.dataSize[i] = size + 1; // strlen(string) + \0
        
        // If its a fixed sized field, we check if it's not bigger than what we store
        if(i == 1 || i == 5 || i == 6 || i == 7) 
        	if(strlen(field.data[i]) > SIZE_FIXED)
        		printf("Campo '%s' será truncado devido ao seu tamanho\n", field.data[i]);
    }
    
    // Reading extra \n
    string = readLine(input, '\n', '\n');
    free(string);

    return field;
}


/* Asks the user if he wants to continue printing the registers. */
char userContinue() {
	int count = 0;
	char c = 0;
	printf("Digite 'p' para o próximo registro ou 'c' para abortar\n");
	while (c != 'p' && c != 'c') {
		count++;
		c = getchar();
		
		// If the user seems not to understand, we carry on nonetheless.
		if (count == 20) {
			printf("Você parece estar com dificuldade para ir ao próximo registro");
			printf("ou abortar, já foram 20 tentativas.\n");
			printf("Continuando automaticamente para o próximo registo\n");
			break;
		}
	}
	return c;
}


/* Frees the memory in a record. */
void freeRecord(t_field field) {
    int i;
    for(i = 0; i < 8; i++) free(field.data[i]);
    free(field.data);
}

