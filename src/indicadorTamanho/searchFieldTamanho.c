#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>	// strcmp, strlen

#include <utils.h>
#include <readTamanho.h>

#include <searchFieldMain.h>


void size_searchField(FILE *fp, int n) {
	t_searchField search;
	t_field field;
	char c, askContinue;
	bool found = false;
	int i, record_size;
	
	// Gets the field to be searched from the user
	search = searchFieldMain();
	
	// If the user has decided to abort at the end of the last function, we abort
	if (search.fieldType == INVALID)
		return;
	// If the there is used memory("\0"), free it before aborting
	if (strlen(search.query) == 0) {
		free(search.query);
		return;
	}

	for (i = 0; (!feof(fp)); i++) {
		
	    fread(&c, sizeof(char), 1, fp);
	    if (!feof(fp)) {	    
	       	
	       	fseek(fp, -1, SEEK_CUR); 
       		fread(&record_size, sizeof(int), 1, fp);

			// Reads a field
			field = readFields(fp);
		
			// Verifies if its the field the user is looking for, with the corrects contents
			if( searchFound(search, field)) {
			
				printField(field, i);
				found = true;
				
				// Asks the user if he wants to continue the search.
				askContinue = continueSearch();
				if (askContinue == 'c') {
					printf("Abortando a pesquisa... ");
					freeFields(field);
					break;
				}
			}		
			
			// Frees used memory
			freeFields(field);
		}
	}
	
	// Frees used memory
	free(search.query);
	
	if(!found)
		printf("Campo não encontrado em nenhum registro do arquivo.\n");
	printf("Retornando ao menu\n");
	
	rewind(fp);
}


