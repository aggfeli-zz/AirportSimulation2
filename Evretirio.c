#include "Evretirio.h"
#include "TSDDA.h"
#include <stdlib.h>

#include <assert.h>
#include <string.h>
#define Simple 1 /* 0 for AVL - any Evr integer for Simple  */

/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - mporeite na xrhsimopoihsete 
   thn  domh #if ... #else ...#endif gia na diaforopihsete tis dyo ylopoihseis  */
   
#if (Simple)
#include "BST/ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
#include "AVL/ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif


typedef struct EvrNode{
       TStoixeiouEvr *DataArray; /* array of size MaxSize */
       int Index;              /* index of first available element in array */
       typos_deikti TreeRoot;     /* Root of DDA */
} EvrNode;

EvrPtr EvrConstruct(){
/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - 
	mporeite na xrhsimopoihsete thn  domh #if ... #else ...#endif */
	EvrPtr EvrNode;
	EvrNode = malloc(sizeof(EvrNode));  
	assert(EvrNode);	
   	EvrNode->DataArray = (TStoixeiouEvr *)malloc (MaxSize * sizeof(TStoixeiouEvr));
	for(EvrNode->Index = 0; EvrNode->Index < MaxSize; ++EvrNode->Index) {
   		strncpy(EvrNode->DataArray[EvrNode->Index].City, "0", SIZE-1);
   		strncpy(EvrNode->DataArray[EvrNode->Index].Country, "0", SIZE-1);
   		strncpy(EvrNode->DataArray[EvrNode->Index].IATA, "0", 3);
   		strncpy(EvrNode->DataArray[EvrNode->Index].ICAO, "0", 4);
		strncpy(EvrNode->DataArray[EvrNode->Index].Name, "0", SIZE-1);
   	}
   	EvrNode->Index = 0;
   	typos_deikti TreeRoot;
#if (Simple)
   	printf("use simple BST\n");
   	Tree_dimiourgia(&TreeRoot);
#else   
   printf("use AVL BST\n");
    AVLTree_dimiourgia(&TreeRoot);
#endif
	return EvrNode;
}

int Evr_Insert(EvrPtr E, TStoixeiouEvr *Data)
{
	int error = 0,i = 0, n = 9;
	TStoixeiouDDA stoixeio;
	assert(E != NULL);
	while(i < MaxSize){
		TSDDA_setKey(&(stoixeio.key), Data[i].ICAO);
		TSDDA_setIndex(&(stoixeio.arrayIndex), E->Index);
		if(strcmp(E->DataArray[E->Index].ICAO , "0") == 0 ){
			TSDDA_setKey (&(E->DataArray[E->Index].ICAO), stoixeio.key);
			TSEvr_setValue (&(E->DataArray[E->Index]), Data[i]);
			#if (Simple)
	   			printf("use simple BST\n");
	   			Tree_eisagogi(&(E->TreeRoot), stoixeio, &error);

			#else   
			    printf("use AVL BST\n");
			    AVLTree_dimiourgia(&(E->TreeRoot));
			#endif
			++E->Index;				
		}	
		else
			++E->Index;
			i++;
	}

	return E->Index;
}

int EvrSearch(EvrPtr E, keyType key, int * found)
{ 
	int i = 0;
	TStoixeiouDDA stoixeio;
	TSDDA_setKey(&(stoixeio.key), key);
	typos_deikti deiktis = NULL;
	assert(E != NULL);
	#if (Simple)
   	/*	printf("use simple BST\n");*/
   		Tree_anazitisi(E->TreeRoot, stoixeio, &deiktis, found);
	#else   
		/*printf("use AVL BST\n");*/
		AVLTree_anazitisi(E->TreeRoot, stoixeio, &deiktis, found);
	#endif	
	return 1; 
}


int Evr_PrintAll(EvrPtr E, FILE *out, int * counter)
{
	typos_deikti a = E->TreeRoot;

/* endo-diadromh - use recursion with apaidi-depaidi */ 
/* example of use */
#if (Simple)
    a=Tree_apaidi(a);
#else   
    a=AVLTree_apaidi(a);
#endif
}


void Evr_katastrofi(EvrPtr *E)
{
	assert(*E);
	free(*E);
	*E = NULL;
	assert(*E==NULL);
}



