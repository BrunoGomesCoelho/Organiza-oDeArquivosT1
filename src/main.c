
/*==========Integrantes==========*/
// Alex Sander Ribeiro da Silva 9779350
// Bruno Gomes Coelho 9791160
// Gabriel de Melo Cruz 9763043
// Marcello Pagano Silva 9791031


// TODO: Colocar os nomes dos integrantes em todos os arquivos

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include <utils.h>
#include <printFixo.h>
#include <printDelimitador.h>
#include <printTamanho.h>
#include <readFixo.h>
#include <readDelimitador.h>
#include <readTamanho.h>
#include <searchFieldTamanho.h>
#include <searchFieldFixo.h>
#include <searchFieldDelimitador.h>

void printMenu() {
	printf("\n\n");
	printf("\tEscolha uma das seguintes funções abaixo:\n");
    printf("1 - Ler a partir do arquivo\n");
    printf("2 - Imprimir todos os dados\n");
    printf("3 - Procurar por campo\n");
    printf("4 - Procurar por número do registro\n");
    printf("5 - Procurar por números de registro e de campo\n");
    printf("6 - Sair\n");
}

void closeFiles(FILE *input, FILE *output) {
    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[]) {
    OPTION op = NONE;
    TYPE_REG regType = NONE;
    FILE *input = fopen("Dominios.csv", "r+"), *output;
    bool read = false;
    int nregs, nfields; // offset = 0; variavel nao usado
    int offset;
    char endPrint[37] = "Fim da impressão, voltando ao menu\n\0";
    char errorAlreadyRead[48] = "Arquivo já lido, abortando e voltando ao menu\n\0";
    char errorNotRead[64] = "Arquivo .csv ainda não foi lido, abortando e voltando ao menu\n\0";
    
    while (regType < 1 || regType > 3) {
    	printf("\n");
        printf("Digite 1 para registros de tamanho variável com indicador de tamanho\n");
	    printf("Digite 2 para registros de tamanho variável com delimitadores entre registros\n");
	    printf("Digite 3 para registros de tamanho variável com número fixo de campos\n");
	    scanf("%d", &regType);
    }
    
	/////////////////////////////////////////////////////////// DEBUGGING ///////////////////////////////////////////////////////////  
	char placeholder[50] = "Função ainda não implementada.\n";
   
	setlocale(LC_ALL, "Portuguese");
   
    while(op != EXIT) {
        printMenu();
        scanf("%d", &op);
        
    	// if the csv file has already been read, abort
        if (op == READ_FROM_FILE && read) {
        	printf("%s", errorAlreadyRead);
        	continue;
    	}
        
        // if the csv file has not yet been read, abort these functions
        if (op == PRINT_ALL || op == SEARCH_BY_RECORD || op == SEARCH_BY_FIELD ||
        	op == SEARCH_BY_RECORD_BY_FIELD) {
        	 if (!read) {
        	 	printf("%s", errorNotRead);	
        	 	continue;
    	 	}
	 	}
        
        switch(regType) {
        	case SIZE_INDICATOR:
				switch(op) {
				    case READ_FROM_FILE:
                        output = size_readDataBase(input, &nregs, &nfields);
                        read = true;
				        break;
				    case PRINT_ALL:				    
						size_printDataBase(output, nregs);
				        printf("%s\n\n", endPrint);
				        break;
				    case SEARCH_BY_RECORD:
						printf("\n\nDigite qual o numero do registro procurado\n"); 
				    	scanf("%d", &offset);
						size_printRecord(output, nregs, offset);
				        break;
				    case SEARCH_BY_FIELD:
				    	// ponteiro para o arquivo e a qtd de registros
					    size_searchField(output, nregs);
				        break;
				    case SEARCH_BY_RECORD_BY_FIELD:
				    	printf("%s", placeholder);
				        break;
				    case EXIT:
				        //closeFiles(input, output); // fclose and frees
				        break;
				    default:
				        printf("Opcao Invalida, voltando ao menu\n");
				        break;
				}
                break;

			case DELIMITER:
				switch(op) {
				    case READ_FROM_FILE:
	                    output = delimiter_readDataBase(input, &nregs, &nfields);
                        read = true;
				        break;
				    case PRINT_ALL:
				    	delimiter_printDataBase(output, nregs);
				    	printf("%s\n\n", endPrint);
				        break;
				    case SEARCH_BY_RECORD:
				    	printf("\n\nDigite qual o numero do registro procurado\n"); 
				    	scanf("%d", &offset);
						delimiter_printRecord(output, nregs, offset); 
				        break;
				    case SEARCH_BY_FIELD:
				    	// ponteiro para o arquivo e a qtd de registros
					    delimiter_searchField(output, nregs);
				        break;
				    case SEARCH_BY_RECORD_BY_FIELD:
				    	printf("%s", placeholder);
				        break;
				    case EXIT:
				        //closeFiles(input, output); // fclose and frees
				        break;
				    default:
				        printf("Opcao Invalida\n");
				        break;
				}
                break;
			
			case FIXED_FIELDS:
				switch(op) {
				    case READ_FROM_FILE:
                        output = fixed_readDataBase(input, &nregs, &nfields);
                        read = true;
				        break;
				    case PRINT_ALL:
				    	fixed_printDataBase(output, nregs);
				        printf("%s\n\n", endPrint);
				        break;
				    case SEARCH_BY_RECORD:
						printf("\n\nDigite qual o numero do registro procurado\n"); 
				    	scanf("%d", &offset);
				    	fixed_printRecord(output, nregs, offset);
				        break;
				    case SEARCH_BY_FIELD:
				    	// ponteiro para o arquivo e a qtd de registros
					    fixed_searchField(output, nregs);
				        break;
				    case SEARCH_BY_RECORD_BY_FIELD:
				    	printf("%s", placeholder);
				        break;
				    case EXIT:
				        //closeFiles(input, output); // fclose and frees
				        break;
				    default:
				        printf("Opcao Invalida\n");
				        break;
				}
                break;
		}
    }
    closeFiles(input, output);
    return 0;
}
