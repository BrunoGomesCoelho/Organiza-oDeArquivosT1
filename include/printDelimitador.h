#ifndef _SEARCHINDICADORTAMANHO_H_
#define _SEARCHINDICADORTAMANHO_H_

#include <stdio.h>
#include <utils.h>

void delimiter_printDataBase(FILE *fp, int n);
void delimiter_printRecord(FILE *fp, int n, int offset);
t_field delimiter_findRecord(FILE *fp, int n, int offset);

#endif
