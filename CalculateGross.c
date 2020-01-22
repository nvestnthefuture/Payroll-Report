#include <stdio.h>
#include <stdlib.h>

double CalculateGross(double hrs, double rate)
	
{	

	double gross;
	
	if(hrs > 40)
	{
		gross = ((rate * 40) + ((1.5 * rate) * (hrs - 40)));

	}

	else
	{
		gross = hrs * rate;


	}


		return(gross);

}



