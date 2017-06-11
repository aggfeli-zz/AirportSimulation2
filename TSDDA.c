#include "TSDDA.h"
#include <string.h>
#include <stdlib.h>

int TSDDA_setValue (TStoixeiouDDA *target, TStoixeiouDDA source)
{
	strncpy(target->key, source.key, 4);
	target->arrayIndex = source.arrayIndex;
}

void TSDDA_setKey(keyType * key, keyType Val)
{
	strncpy(*key, Val, 4);
}

int TSDDA_setIndex(int * Index, int Val)
{
	*Index = Val;
}

int TSDDA_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return (strcmp(s1.key,s2.key) == 0);
}

int TSDDA_mikrotero(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return (strcmp(s1.key,s2.key) > 0);
}

int TSDDA_megalytero(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return (strcmp(s1.key,s2.key) < 0);
}

TStoixeiouDDA * read_value(FILE *from)
{
	char temp[10];
	int i = 0;
	TStoixeiouDDA * s;
	s = (TStoixeiouDDA *)malloc(9000 * sizeof(TStoixeiouDDA));
	while (fgets(temp, 10, from) > 0 && i < 9000 ){
		strcpy(s[i].key, temp);
		i++;
	}
	return s;
}

int TSDDA_writeValue(FILE *to, TStoixeiouDDA key)
{
	int fd;
	fd = fprintf(to, "%s\r\n", key);
	return fd;	
}

/* The Following are already Implemented using Above */

int TSDDA_mikrotero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{ 
    return TSDDA_mikrotero(s1,s2)||TSDDA_iso(s1,s2);
}

int TSDDA_megalytero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
    return TSDDA_megalytero(s1,s2)||TSDDA_iso(s1,s2);
}

int TSDDA_diaforo(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
    return !TSDDA_iso(s1,s2);
}
