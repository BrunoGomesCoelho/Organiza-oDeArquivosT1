#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

FILE *size_readDataBase(FILE *input, int *nregs, int *nfields) {
    FILE *output = fopen("answer.dat", "wb+");
    char zeroe[30] = "000000000000000000000000000000";
    int i, regSize = 0;
    t_field field;
    *nfields = 8;


    for(*nregs = 0; !feof(input); (*nregs)++) {
        field = readRecord(input);
        if(feof(input)) break;

        // Calculate and write the size of the record (including string terminators '\0')
        regSize = calculateRecordSize(field);
        fwrite(&regSize, sizeof(int), 1, output);

        // Write record
        for(i = 0; i < (*nfields); i++) {
            if( i == 0 || i == 2 || i == 3 || i == 4 ) // If variable-sized field
                fwrite(&field.dataSize[i], sizeof(int), 1, output);

            // Writes the string
            fwrite(field.data[i], sizeof(char), field.dataSize[i], output); 

            // If we need to fill with zeroes (for fixed-size fields)
            if(i == 1 || i == 5 || i == 6 || i == 7) 
                fwrite(zeroe, sizeof(char), SIZE_FIXED - (field.dataSize[i]), output);
        }
        freeRecord(field);
    }

    freeRecord(field);
    
	rewind(output);
    return output;
}

