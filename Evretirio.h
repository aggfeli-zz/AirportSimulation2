#ifndef __Evr__
#define __Evr__

#include <stdlib.h>
#include <stdio.h>
#include "TSEvr.h"

typedef struct EvrNode *EvrPtr;

EvrPtr EvrConstruct();
void EvrDestruct(EvrPtr *E);

int EvrInsert(EvrPtr E, TStoixeiouEvr Data);
int EvrSearch(EvrPtr E, keyType key, int * found);
int EvrPrintAll(EvrPtr E, FILE *out, int *counter);

#endif
