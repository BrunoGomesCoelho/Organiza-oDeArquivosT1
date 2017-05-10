#include <stdio.h>
#include <stdlib.h>

#include <utils.h>


void printRegFieldMain(t_field field) {
	int fieldPos = -1;

	while (fieldPos < 0 || fieldPos >= 9) {
		printf("Digite o número correspondente ao campo que quer pesquisar nos registros, ou 0 para abortar e voltar ao menu\n");
		printf("1 - Domain\n");
		printf("2 - Documento\n");
		printf("3 - Nome\n");
		printf("4 - Cidade\n");
		printf("5 - Estado\n");
		printf("6 - Data e hora de criação\n");
		printf("7 - Data e hora de última atualização\n");
		printf("8 - Ticket\n");
	
		scanf("%d", &fieldPos);
	
		if (fieldPos < 0 || fieldPos >= 9) 
			printf("Valor inválido digitado, por favor tente de novo.\n");
			
		if (fieldPos == 0) {
			printf("Voltando ao menu\n");
			return;
		}
	}
	
	if (fieldPos == 1) 
		printf("\t\t\tDomain: \t\t\t%s\n", field.domain);
	if (fieldPos == 2) 
		printf("\t\t\tDocument Number: \t\t%s\n", field.document_number);
	if (fieldPos == 3) 
		printf("\t\t - \t\t%s\n", field.name);
	if (fieldPos == 4) 
		printf("\t\t\tCity: \t\t\t\t%s\n", field.city);
	if (fieldPos == 5) 
		printf("\t\t\tState: \t\t\t\t%s\n", field.state);
	if (fieldPos == 6) 
		printf("\t\t\tDate and time created: \t\t%s\n", field.dateTimeOri);
	if (fieldPos == 7) 
		printf("\t\t\tDate and time last updated: \t%s\n", field.dateTimeUpd);
	if (fieldPos == 8)
		printf("\t\t\tTicket number: \t\t\t%s\n", field.ticket);
	printf("\t\t\t========================================================\n\n");
}


