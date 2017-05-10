#ifndef _PRINTTAMANHO_H_
#define _PRINTTAMANHO_H_

#include <stdio.h>
#include <utils.h>

void size_printDataBase(FILE *fp, int n);
void size_printRecord(FILE *fp, int n, int offset);
t_field size_findRecord(FILE *fp, int n, int offset);

#endif
