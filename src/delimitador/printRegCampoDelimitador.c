#include <stdio.h>
#include <stdlib.h>

#include <printDelimitador.h>
#include <printRegFieldMain.h>


/* Prints the field of a specific register */
void delimiter_printRecordField(FILE *fp, int n) {
	int regPos;
	
	printf("\n\nDigite o número do registro que deseja acessar: \n");
	scanf("%d", &regPos);
	
	// If the regPos isn't valid, return to the main menu
	if (regPos < 0 || regPos >= n) {
		printf("Por favor digite um número de registro válido! Voltando ao menu\n");
		return;
	}
	
	// Reads the register
	t_field field = delimiter_findRecord(fp, n, regPos);
	
	// Ask the user what field he wants and prints it
	printRegFieldMain(field);
}
