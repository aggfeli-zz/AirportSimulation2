/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			: Ageliki Felimega
Skopos				: skeleton main for askhsh 3
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include <windows.h>
#include "TSEvr.h"
#include "Evretirio.h"
#include "TSDDA.h"


int erwthma_3(EvrPtr E, TStoixeiouDDA * s, int erwthma);
void erwthma_4(EvrPtr E, TStoixeiouDDA * s, int erwthma, int sum_of_found);

int main(int argc, char *argv[])
{ 
	EvrPtr E = NULL;
	TStoixeiouEvr *Data;
	TStoixeiouDDA *s;
	FILE *fp, *fp1;
	int error = 1, i = 0, found = 0, sum_not_found = 0, sum_of_found = 0;
	char temp[100], *str;


	fp = fopen("ICAO_Random_Input-Windows.txt", "r+");
	if (fp == NULL) {
        perror("Failed to open file \"ICAO_Random_Input-Windows\"");
    }
	printf("RANDON INPUT\n");
	
  	E = EvrConstruct();

	Data = TSEvr_readValue (fp);
	
	LARGE_INTEGER frequency;       /*  ticks per second */
    LARGE_INTEGER t1, t2;            /* ticks */
    double elapsedTime;

    QueryPerformanceFrequency(&frequency);		 /*	 get ticks per second */
    QueryPerformanceCounter(&t1);				 /*	 start timer */
    
    int sum;
	sum = Evr_Insert(E, Data);
	printf("Exoun eisaxthei %d stoixeia apo to random\n", sum);
	
    QueryPerformanceCounter(&t2);					 /* stop timer */

    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;				/* compute and print the elapsed time in millisec */
    printf("O xronos pou xreiasthke gia na eisax8oun ta dedomena apo to arxeio einai: %g msec\n", elapsedTime);
    
	fclose(fp);

	/*   Erwthma 3    */
	
	int erwthma = 3;
	sum_of_found = erwthma_3(E, s, erwthma);
	
	
  	/*   Erwthma 4    */
  	
  	erwthma = 4;
	erwthma_4(E, s, erwthma, sum_of_found);
	
    Evr_katastrofi(&E); 
    
    
    /*    erwthma 7   */
    
    fp = fopen("ICAO_Sorted_Input-Windows.txt", "r+");
	if (fp == NULL) {
        perror("Failed to open file \"ICAO_Sorted_Input-Windows\"");
    }
	printf("SORTED INPUT\n");
	
 	E = EvrConstruct(); 

	Data = TSEvr_readValue (fp);

    QueryPerformanceFrequency(&frequency);			/*	 get ticks per second */
    QueryPerformanceCounter(&t1);					/*	 start timer */

	sum = Evr_Insert(E, Data);
	printf("Exoun eisaxthei %d stoixeia apo to sorted\n", sum);
	
    QueryPerformanceCounter(&t2);				/*	 stop timer */
    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;	/*	 compute and print the elapsed time in millisec */
    printf("O xronos pou xreiasthke gia na eisax8oun ta dedomena apo to arxeio einai: %g msec\n", elapsedTime);
    
	fclose(fp);
    
    /*   Erwthma 7.3    */
	
	erwthma = 7;
	sum_of_found = erwthma_3(E, s, erwthma);
	
	
  	/*   Erwthma 7.4    */
  	
  	erwthma = 7;
	erwthma_4(E, s, erwthma, sum_of_found);
	
	
    Evr_katastrofi(&E);
    
  	return 0;
}


int erwthma_3(EvrPtr E, TStoixeiouDDA * s, int erwthma)
{
	FILE *fp;
	fp = fopen("ICAO_SEARCH-Windows.txt", "r+");
	if (fp == NULL) {
        perror("Failed to open file \"ICAO_SEARCH-Windows\"");
    }
    int i = 0, found = 0, sum_not_found = 0, sum_of_found = 0;

  	s = read_value(fp);												/* Divazei olo to periexomeno tou arxeiou*/
  	fclose(fp);

  	if( erwthma == 3)											/*Dhmiourgia tou random arxeiou ektypwshs gia to erwthma 3*/
  	{
  		fp = fopen("ICAO_FOUND_random.txt", "rb+");
    	if(fp == NULL) /*if file does not exist, create it */
    	{
        	fp = fopen("ICAO_FOUND_random.txt", "wb");
        	if (fp == NULL)
            	perror("Failed to open file \"ICAO_FOUND_random.txt\"");
    	}
  	}
  	else														/*Dhmiourgia tou sorted arxeiou ektypwshs gia to erwthma 7.3*/
  	{
  		fp = fopen("ICAO_FOUND_sorted.txt", "rb+");
    	if(fp == NULL) /*if file does not exist, create it */
    	{
        	fp = fopen("ICAO_FOUND_sorted.txt", "wb");
        	if (fp == NULL)
            	perror("Failed to open file \"ICAO_FOUND_sorted.txt\"");
    	}
  	}
  	LARGE_INTEGER frequency;        /* ticks per second */
    LARGE_INTEGER t1, t2;           /* ticks */
    double elapsedTime;

    QueryPerformanceFrequency(&frequency);							 /* get ticks per second */
    QueryPerformanceCounter(&t1);									 /* start timer */
    
  	i = 0;
  	clock_t t = clock();
	while(i < 9000 && strlen(s[i].key) == 5){
	  	EvrSearch(E, s[i].key, &found);
	  	if (found == 1)
		{
			sum_of_found++;
			TSDDA_writeValue(fp, s[i].key);
	  	} 
	  	else sum_not_found++;
	  
	  	i++;
	}
	t = clock() - t;
	
    QueryPerformanceCounter(&t2);												 /* stop timer */

    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;		/* compute and print the elapsed time in millisec */
    printf("Erwthsh 3: O xronos einai: %g msec\n", elapsedTime);
	printf("Found %d ICAO in %f secs and not found %d ICAO\n\n", sum_of_found, (double) t /CLOCKS_PER_SEC, sum_not_found);	
  	fclose(fp);

	return sum_of_found;
}


void erwthma_4(EvrPtr E, TStoixeiouDDA * s, int erwthma, int sum_of_found)
{
	FILE *fp;
	if( erwthma == 4)										/*An einai to erwthma 4, anoigei to antistoixo arxeio random*/
	{
		fp = fopen("ICAO_FOUND_random.txt", "r+");
		if (fp == NULL) {
        	perror("Failed to open file \"ICAO_FOUND_random.txt\"");
    	}
	}
	else													/*Alliws an einai to erwthma 7.4 anoigei to sorted*/
	{
		fp = fopen("ICAO_FOUND_sorted.txt", "r+");
		if (fp == NULL) {
        	perror("Failed to open file \"ICAO_FOUND_random_sorted.txt\"");
    	}
	}
    int i = 0, found = 0, sum_not_found = 0;
  	s = read_value(fp);
  	fclose(fp);
  	
	LARGE_INTEGER frequency;        /* ticks per second */
    LARGE_INTEGER t1, t2;           /* ticks */
    double elapsedTime;

    QueryPerformanceFrequency(&frequency);							/* get ticks per second */
    QueryPerformanceCounter(&t1);								/* start timer */
    
  	clock_t t = clock();
  	int sum_of_found1 = 0;
  	sum_not_found = 0;
  	if( erwthma == 4)											/*An einai to erwthma 4, dhmiourgei to antistoixo arxeio random output*/
  	{
  		fp = fopen("ICAO_FOUND_random_output.txt", "rb+");
	    if(fp == NULL) 											/*An to arxeio den uparxei to dhmioyrgei */
	    {
	        fp = fopen("ICAO_FOUND_random_output.txt", "wb");
	        if (fp == NULL)
	            perror("Failed to open file \"ICAO_FOUND_random_output.txt\"");
	    }
  	}
  	else														/*An einai to erwthma 7.4, dhmiourgei to antistoixo arxeio sorted output*/
  	{
  		fp = fopen("ICAO_FOUND_sorted_output.txt", "rb+");
	    if(fp == NULL) 											/*An to arxeio den uparxei to dhmioyrgei */
	    {
	        fp = fopen("ICAO_FOUND_sorted_output.txt", "wb");
	        if (fp == NULL)
	            perror("Failed to open file \"ICAO_FOUND_sorted_output.txt\"");
	    }
  	}
    i = 0;
	while(i < 9000 && sum_of_found1 < sum_of_found){
	  	EvrSearch(E, s[i].key, &found);
	  	
	  	if (found == 1)
		{
			sum_of_found1++;
			TSDDA_writeValue(fp, s[i].key);
	  	} 
	  	else sum_not_found++;
	  	i++;
	}
	
	
    QueryPerformanceCounter(&t2);										/* stop timer */

    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;			/* compute and print the elapsed time in millisec */
    printf("Erwthsh 4: O xronos einai: %g msec\n", elapsedTime);
    
	t = clock() - t;
	printf("Found %d ICAO in %f secs and not found %d ICAO\n\n", sum_of_found1, (double) t /CLOCKS_PER_SEC, sum_not_found);	
  	fclose(fp);
	
	return;
}


