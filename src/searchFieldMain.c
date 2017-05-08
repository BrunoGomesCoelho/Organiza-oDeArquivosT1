#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <stdbool.h>
#include <string.h>	// strlen

#include <inputFieldMain.h>
#include <searchFieldMain.h>
#include <utils.h>


t_searchField searchFieldMain() {
	bool validInput = false;
	int op = -1;
	char memError[100] = "em formato não válido digitado. Por favor tente de novo ou digite uma string vazia para abortar\n";
	t_searchField search;
	search.fieldType = INVALID;
	
	// TODO: explicar como devera ser digitado os inputs com tamanho fixo.
	while( !validInput) {	
		while (op >= 0 && op < 9) {
			// TODO: Reordenar isso
			printf("Digite o número correspondente ao campo que quer pesquisar nos registros, ou 0 para abortar e voltar ao menu\n");
			printf("1 - Domain\n");
			printf("2 - Documento\n");
			printf("3 - Nome\n");
			printf("4 - Cidade\n");
			printf("5 - Estado\n");
			printf("6 - Data e hora de criação\n");
			printf("7 - Data e hora de última atualização\n");
			printf("8 - Ticket\n");
		
			scanf("%d", &op);
		
			if (op < 0 || op >= 9) 
				printf("Valor inválido digitado, por favor tente de novo.\n");
				
			if (op == 0)
				return search;
		}
	
		// reads the user input
		printf("Digite o campo: ");
		search.fieldType = op;
		search.query = readLine(stdin, '\n', '\n');
		
		// if the user has decided to abortar
		if (strlen(search.query) == 0) {
			search.fieldType = INVALID;
			return search;
		}
		
		// Verifies  the user input
		if (op == DOCUMENT && verifyInputDocument(search.query) == false)
			printf("Documento %s", memError);
		else if ( (op == DATE_CREATED || op == DATE_UPDATED) && verifyInputDateAndTime(search.query) == false) 
			printf("Data %s", memError);
		else if ( op == TICKET && verifyInputTicket(search.query) == false)
			printf("Ticket %s", memError);
		else
			return search;				 
	}
	return search;
}

