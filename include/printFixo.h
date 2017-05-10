#ifndef _PRINTFIXO_H_
#define _PRINTFIXO_H_

#include <stdio.h>
#include <utils.h>


void fixed_printDataBase(FILE *fp, int n);
void fixed_printRecord(FILE *fp, int n, int offset);
t_field fixed_findRecord(FILE *fp, int n, int offset);

#endif
