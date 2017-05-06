#ifndef _UTILS_H_
#define _UTILS_H_

#define OPTION int
#define TYPE_REG int
#define FIELD int


enum {
	INVALID,
	DOMAIN,
	DOCUMENT,
	NAME,
	CITY,
	STATE,
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


typedef enum {
	ALGO,
    // NONE,om essa linha não compila, está redefinindo não do outro enum.
    // file organization types
} FTYPE;

#endif
