#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>	// strcmp
#include <ctype.h> 	// isdigit

#include <utils.h>


// TODO: Simplificar a readLine, não precisa ter um seprador e um fim_linha.
// TODO: Traduzir para inglês.
char *readLine(FILE *stream, char separador, char fim_linha) {
    /* Le de um stream um input até encontrar o char separador,  fim_linha ou ser o fim do arq.
    Alocamos 50 bytes pra o input, e caso passe disso, incrementamos de 50 em 50 até ter toda a mensagem. 
    Depois, eliminamos bytes desnecessários */
    int i = 0, realloc_count = 0; //realloc_count guarda a qtd de reallocs ja feitos
    char letra, *string;
    string = (char *) malloc(50 * sizeof(char));
    letra = fgetc(stream);


    while (letra != separador && letra != fim_linha && letra != EOF) { 
        //leia até o usario pressionar separador, fim_lina ou ser o fim do arquivo
        string[i] = letra;
        i++;
        letra = fgetc(stream);
        if (i >= 50*(realloc_count +1)) { 
            //se houver mais chars do que o que já alocamos, realloc mais
            string = (char *) realloc(string, 50 * (realloc_count +2)*sizeof(char));
            realloc_count++;
        }
    } // i sai com o tamanho da string
    string = realloc(string, (i+1)*sizeof(char)); //elimina bytes desnecessários
    string[i] = '\0'; //adicionando um \0 no fim da string
    return string;
}

// TODO: pode ser simplificada, receber um char **fields e iterar sobre ele, acredito que fique mais elegante // ltkills
void printField(char *name, char *domain, char *document_number, char *city, 
				char *state, char *dateTimeOri, char *dateTimeUpd, int offset, int ticket) {
				
	if (strcmp(name, "null")) 
		printf("\t%d - %s\n", offset, name);
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
}


/* OBS: Quem for ler o input, mantenha-se atento ao fato que qualquer modificação aqui pode resultar em mudanças
		na verificação do input durante a busca por um campo (Bruno). */
bool verifyInputDocument(char *doc) {
	// example of a valid input : 000.394.411/0001-09
	
	// Verifies the size of the input and the special characters.
	if ( strlen(doc) != SIZE_DOCUMENT || doc[3] != '.' || doc[7] != '.' ||
		 doc[11] != '/' || doc[16] != '-')
		 	 return false;
	
	// Verifies the digits
	if ( isdigit(doc[0]) && isdigit(doc[1]) && isdigit(doc[2]) && isdigit(doc[4]) && isdigit(doc[5]) && isdigit(doc[6]) &&
		 isdigit(doc[8]) && isdigit(doc[9]) && isdigit(doc[10]) && isdigit(doc[12]) && isdigit(doc[13]) && isdigit(doc[14]) && 
		 isdigit(doc[15]) && isdigit(doc[17]) && isdigit(doc[18]) ) return true;
	return false;
}


// TODO: Criar os outros verificadores para os campos de tamanho fixo.




/*Loads the record into t_field struct*/
t_field readRecord(FILE *input) {
    char *string;
    t_field field;
    field.data = malloc(sizeof(char *)*8);

    for(int i = 0; i < 8; i++) {
        string = readLine(input, ';', '\n');
        field.data[i] = string;
        field.dataSize[i] = strlen(string) + 1; // strlen(string) + \0 + ;
    }

    // fixes sizes of these fields
    field.dataSize[1] = field.dataSize[5] =
        field.dataSize[6] = field.dataSize[7] = SIZE_FIXED;


    return field;
}


void freeRecord(t_field field) {
    int i;
    for(i = 0; i < 8; i++) free(field.data[i]);
    free(field.data);
}


void printRecord(t_field field) { // for debbuging

    for(int i = 0; i < 8; i++) 
        printf("%s;", field.data[i]);
    printf("#\n");
}
