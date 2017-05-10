#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <ctype.h> 	// isdigit
#include <string.h>	// strlen

#include <utils.h>


bool verifyInputDocument(char *doc) {
	// example of a valid input : 000.394.411/0001-09
	
	// Verifies the size of the input and the special characters.
	if ( strlen(doc) >= SIZE_FIXED || doc[3] != '.' || doc[7] != '.' ||
		 doc[11] != '/' || doc[16] != '-')
		 	 return false;
	
	// Verifies the digits
	if ( isdigit(doc[0]) && isdigit(doc[1]) && isdigit(doc[2]) && isdigit(doc[4]) && 
		 isdigit(doc[5]) && isdigit(doc[6]) && isdigit(doc[8]) && isdigit(doc[9]) && 
		 isdigit(doc[10]) && isdigit(doc[12]) && isdigit(doc[13]) && isdigit(doc[14]) && 
		 isdigit(doc[15]) && isdigit(doc[17]) && isdigit(doc[18]) ) return true;
	return false;
}


bool verifyInputDateAndTime(char *date) {
	/* Example of a valid input: 17/12/2004 17:03:07
		if its a single digit date/time, we consider there is a leading zero.
		Ex: 04/02/2004 08:03:07 */
		
	// Verifies the size of the input and the special characters
	if (strlen(date) >= SIZE_FIXED || date[2] != '/' || date[5] != '/' || 
		date[10] != ' ' || date[13] != ':' || date[16] != ':') return false;
		
	// Verifies the digits
	if( isdigit(date[0]) && isdigit(date[1]) && isdigit(date[3]) && isdigit(date[4]) && 
		isdigit(date[6]) && isdigit(date[7]) && isdigit(date[8]) && isdigit(date[9]) && 
		isdigit(date[11]) && isdigit(date[12]) && isdigit(date[14]) && isdigit(date[15]) && 
		isdigit(date[17]) && isdigit(date[18]) ) return true;
	return false;
}


bool verifyInputTicket(char *ticket) {
	int i;
	
	// Verifies the size of the ticket
	if (strlen(ticket) >= SIZE_FIXED) {
		printf("Tamanho do ticket excedido seu limite\n");
		return false;
	}
	
	// Verifies if all the characters are indeed numbers
	for (i = 0; i < strlen(ticket); i += 1) 
		if(!isdigit(ticket[i]))
			return false;
	return true;
}



