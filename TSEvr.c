#include "TSEvr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source)
{
	
	strncpy(target->IATA, source.IATA, 4);  
	strncpy(target->City, source.City, SIZE);
	strncpy(target->Name, source.Name, SIZE);
	strncpy(target->Country, source.Country, SIZE);
}

TStoixeiouEvr * TSEvr_readValue (FILE *from)
{
	int fd, i = 0, j = 0;
	char temp[100], *str;
	TStoixeiouEvr * Elem;
	Elem = (TStoixeiouEvr *)malloc (MaxSize * sizeof(TStoixeiouEvr));
	while(fgets(temp, 100, from) > 0 && j < MaxSize)
  	{	
  		i = 0;
    	str = strtok(temp, "%");
	   	while( str != NULL ) 
   		{
      		if(i==0) strncpy(Elem[j].ICAO, str, 4);
      		else if (i==1) strncpy(Elem[j].IATA, str, 4);
      		else if(i==2) strncpy(Elem[j].City, str, SIZE-1);
      		else if(i==3) strncpy(Elem[j].Name, str, SIZE-1);
      		else strncpy(Elem[j].Country, str, SIZE-1);
      		str = strtok(NULL, "%");
      		i++;
      		j++;
   		}
	}
	return Elem;
}


int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem)
{
	int fd;
	fd=fprintf(to, "%d--", Elem);
	return fd;	
}

