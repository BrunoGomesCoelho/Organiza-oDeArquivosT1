#ifndef _PrintSelected_
#define _PrintSelected_

#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

//Necess�rias
void print_selected(FILE *file, int reg_type, int reg_offset, int field_offset);

//�teis
int jump_to_register(FILE *file, int type, int offset);

#endif //PrintSelected
