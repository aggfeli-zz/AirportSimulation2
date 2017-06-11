#ifndef __TSEvr__
#define __TSEvr__

#include <stdio.h>
#define SIZE 30
#define MaxSize 511
typedef char keyType[5];

typedef struct data {
        keyType ICAO;
        char 	IATA[4];
        char 	City[SIZE];
        char 	Name[SIZE];
        char 	Country[SIZE];
} TStoixeiouEvr;

void TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source);

TStoixeiouEvr * TSEvr_readValue (FILE *from);

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem);

#endif
