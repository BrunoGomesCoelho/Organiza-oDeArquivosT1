#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>


#define OPTION int
#define TYPE_REG int
#define FIELD int

// Size of the fields that hava a fixed length, as chars
#define SIZE_FIXED 30


typedef struct {
    int dataSize[8];
    char **data;
	char *domain;
	char *document_number;
	char *name;
	char *city;
	char *state;
	char *dateTimeOri;
	char *dateTimeUpd;
	char *ticket;
} t_field;


enum {
	INVALID,
	DOMAIN,
	DOCUMENT,
	NAME,
	STATE,
	CITY,
	DATE_CREATED,
	DATE_UPDATED,
	TICKET
};


enum {
    NONE,
    READ_FROM_FILE,
    PRINT_ALL,
    SEARCH_BY_FIELD,
    SEARCH_BY_RECORD,
    SEARCH_BY_RECORD_BY_FIELD,
    EXIT
};


enum {
	SIZE_INDICATOR = 1,
	DELIMITER,
	FIXED_FIELDS
};

typedef struct  {
    int domain_size, document_number_size, name_size, city_size, state_size;
    int dateTimeOri_size, dateTimeUpd_size, record_size;
} RECORD_SIZE;


void printField(t_field field, int ticket);

char *readLine(FILE *stream, char separador, char fim_linha);

t_field readFields(FILE *fp);

void freeFields(t_field field);

int calculateRecordSize(t_field field);

bool verifyInputDocument(char *doc);

t_field readRecord(FILE *input);

void printRecord(t_field field);

char userContinue();

void freeRecord(t_field field);

#endif
