#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>

FILE *fixed_readDataBase(FILE *input, int *nregs, int *nfields) {
    FILE *output = fopen("answer.dat", "wb+");
    char zeroe[30] = "000000000000000000000000000000";
    int i;
    t_field field;
    *nfields = 8;


    for(*nregs = 0; !feof(input); (*nregs)++) {
        field = readRecord(input);
        if(feof(input)) break;

        // Write record
        for(i = 0; i < (*nfields); i++) {
            if( i == 0 || i == 2 || i == 3 || i == 4) // If variable-sized field
                fwrite(&field.dataSize[i], sizeof(int), 1, output);

            fwrite(field.data[i], sizeof(char), field.dataSize[i], output); // Writes the string

            if(i == 1 || i == 5 || i == 6 || i == 7) // If we need to fill with zeroes (for fixed-size fields)
                fwrite(zeroe, sizeof(char), SIZE_FIXED - (field.dataSize[i]), output);
        }
        freeRecord(field);
    }

    freeRecord(field);

	rewind(output);

    return output;
}
