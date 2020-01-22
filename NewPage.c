#include <stdio.h>
#include <stdlib.h>


void NewPage(FILE *outFile, int pageNumber)
{
	if(pageNumber > 0)
	{
	   
	    fprintf(outFile, "\n\t\t\t\t\t\tPage: %d\n\f\n\n\t\t\t\t\t ACME\n\t\t\t\nEmp#\tName\t\t     Dept.\t          New YTD\t     Gross\t          FICA\t          Net\n\n",pageNumber);			 						
	
	}
	
	  else
	    {
		
	       

	      fprintf(outFile, "Emp#\tName\t\t\tDept.\tNew YTD\tGross\tFICA\tNet\n\n");									

	    }

	




}






