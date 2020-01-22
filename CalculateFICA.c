#include <stdio.h>
#include <stdlib.h>

double CalculateFICA(double grossPay, double yearToDate)
{
	
	double ficaTaxRate;
	double ficaLimit;
	double totalTaxRate;
	
	FILE *ficaFile = fopen("FICARATE.txt", "r");
	fscanf(ficaFile,"%lf%lf", &ficaTaxRate, &ficaLimit);
	fclose(ficaFile);

	if(yearToDate >= ficaLimit)
	{
		totalTaxRate = 0;

	}

	   else
	{
		if(yearToDate + grossPay <= ficaLimit)
		{
			totalTaxRate = grossPay * ficaTaxRate;

		}

		else
		{
			totalTaxRate = (ficaLimit - yearToDate) * ficaTaxRate;

		}


	}



		return(totalTaxRate);

}

