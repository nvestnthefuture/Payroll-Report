#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <monetary.h>




double CalculateGross(double, double);
double CalculateFICA(double, double);
void NewPage(FILE*, int);

double main()
{
	//FileIn FileOut Declaration
	FILE *inFile;
	FILE *outFile;
	
	//Initialization
	//Actual input path and file name
	char fileInName[21];
	char fileOutName[21];
	char response;
	
	//Ask user to enter the file name
	printf("Enter the name & path of the input file [max 20 characters]: ");
	scanf("%s", fileInName);

	
	//ie. inFile fopen notes example("seqio1.txt", "r")
	inFile = fopen(fileInName, "r");

	if(inFile == NULL)
	  {
		printf("Input file does NOT EXIST! Program terminating.");

		//Exit program exit(0) indicates program is a success
		//Exit(1) indicates a program failure
		exit(1);
	  }

	//outfile
	

	//Ask user for input statement
	printf("Enter the name and path of the file to hold the results [max 20 characters]: ");

	//Taking in input
	scanf("%s", fileOutName);

	//Do not overwrite an existing file by accident - Choice Y or N 
	if((outFile = fopen(fileOutName, "r")) != NULL)
	  {
		printf("\nA file by the name %s exists.\n", fileOutName);
		printf("Do you wish to overwrite (Y or N): ");

		//Skip<cr> in buffer with "%*c, i.e., one character - white space
		scanf("%*c %c", &response);

		if((response == 'n') || (response == 'N'))
	   	  {
			//Close the file
			fclose(outFile);
		
			printf("\nProgram aborted to prevent overwriting!");
		
			//Exit
			exit(1);
	   	  }
	   }
		
		//outFile
		outFile	= fopen(fileOutName, "w");

		if(outFile == NULL)
		{
		   printf("Sorry Charlie, could not create the outputfile! Program terminating.");
			
		   //Exit
		   exit(1);

		}
		
	  
		
	//Variables & Initialization
	//Employee Number
	int employeeNumber;

	//Last Name
	char surName[20];

	//First Name
	char givenName[20];

	//Department Name
	char departmentName[10];

	//Old Department Name
	char oldDepartmentName[10];

	//Year To Date
	double yTD;

	//Pay Rate
	double payRate;

	//Hours worked
	double hoursWorked;

	//Gross
	double gross;
	
	//Per Person
	double grossPerPerson;
	double ficaPerPerson;
	double netPerPerson;

	//Per Department
	double grossPerDepartment;
	double ficaPerDepartment;
	double netPerDepartment;
	

	//Per Page Totals
	double pageTotalGross;
	double pageTotalFICA;
	double pageTotalNet;

	//Grand Totals
	double grandTotalGross;
	double grandTotalFICA;
	double grandTotalNet;

	//Line counter
	int lineCount = 0;
	
	//Page Count
	int pageCount = 0;

	fprintf(outFile, "\f\n\n\t\t\t                           ACME Sports Inc.\t\t\t\n\t\t\t\t\t\"We are the best, you use the best!\"\n\n");
	fprintf(outFile, "********************************************************************************************************************\n");
	NewPage(outFile, pageCount); 
	
	//Inc Page Count
	pageCount++;	

	//Reading the file	
	while((fscanf(inFile,"%d", &employeeNumber))!=EOF)
	   {

		//Scan in order of the attributes
		fscanf(inFile, "%s", surName);
		fscanf(inFile, "%s", givenName);
		fscanf(inFile, "%s", departmentName);
		fscanf(inFile, "%lf", &yTD);
		fscanf(inFile, "%lf", &payRate);
		fscanf(inFile, "%lf", &hoursWorked);

		//Calculate Payroll PerPerson Totals
		grossPerPerson = CalculateGross(hoursWorked, payRate);
		ficaPerPerson = CalculateFICA(grossPerPerson, yTD);
		netPerPerson = grossPerPerson - ficaPerPerson;
		yTD = yTD + grossPerPerson;

		//Calculate Grand Totals
		grandTotalGross += grossPerPerson;
		grandTotalFICA += ficaPerPerson;
		grandTotalNet += netPerPerson;


		//String Compare Old Department & Department Name
		if(strcmp(oldDepartmentName,"")!=0 && strcmp(oldDepartmentName, departmentName)!=0)
		{
			//Print Department Totals
			fprintf(outFile,"\nDepartment Totals: \t\t\t\t\t   $%10.2lf\t   $%10.2lf\t   $%10.2lf\n", grossPerDepartment, ficaPerDepartment, netPerDepartment);
			
			//Reset Department Totals
			grossPerDepartment = 0;
			ficaPerDepartment = 0;
			netPerDepartment = 0;
			strcpy(oldDepartmentName, departmentName);
		}
			
		 
		   if(lineCount == 4)
		    {
			if(strcmp(oldDepartmentName,"")!=0 && strcmp(oldDepartmentName, departmentName)!=0)
			{
				fprintf(outFile,"\nDepartment Totals: \t\t\t\t   $%10.2lf\t\t   $%10.2lf\t\t   $%10.2lf\n", grossPerDepartment, ficaPerDepartment, netPerDepartment);
				//fprintf(outFile,"\nDepartment Totals: \t\t\t\t\t\t$%10.2lf   $%10.2lf    $%10.2lf\n", grossPerDepartment, ficaPerDepartment, netPerDepartment);
			
				//Reset Department Totals
				grossPerDepartment = 0;
				ficaPerDepartment = 0;
				netPerDepartment = 0;
			}

			//Print Page Totals
			fprintf(outFile,"\nPage Totals: \t\t\t\t      $%7.2lf\t\t$%7.2lf\t\t$%7.2lf\n", pageTotalGross, pageTotalFICA, pageTotalNet);
			
			NewPage(outFile, pageCount);									

			lineCount = 0;

			//Inc Page Count
			pageCount++;

			//Reset Page Totals
			pageTotalFICA = 0;
			pageTotalGross = 0;
			pageTotalNet = 0;

	            }

		//Inc Line Count	
		lineCount++;

		//Calculate Department Totals
		grossPerDepartment += grossPerPerson;
		ficaPerDepartment += ficaPerPerson;
		netPerDepartment += netPerPerson;

		//Print to the file
		fprintf(outFile, "\n%d\t%-10s\t%-10s\t%s\t$%10.2lf\t$%10.2lf\t$%10.2lf\t$%10.2lf\n", employeeNumber, givenName, surName, departmentName, yTD, grossPerPerson, ficaPerPerson,   	netPerPerson);
		
		strcpy(oldDepartmentName, departmentName);
		
		//Page Totals Per Person
		pageTotalFICA += ficaPerPerson;
		pageTotalGross += grossPerPerson;
		pageTotalNet += netPerPerson;


	     }
		fprintf(outFile,"\nDepartment Totals: \t\t\t    $%7.2lf\t$%7.2lf\t$%7.2lf\n", grossPerDepartment, ficaPerDepartment, netPerDepartment);
		fprintf(outFile,"\nPage Totals: \t\t\t\t\t      $%7.2lf\t$%7.2lf\t$%7.2lf\n", pageTotalGross, pageTotalFICA, pageTotalNet);
		//Print Report Summary,Records Proccessed, Total Gross, Total FICA & Total Net
		fprintf(outFile, "\t\t\t\t\n*Report Summary*\n\n");
		fprintf(outFile, "Records Proccessed: \t %d\n",(int)((pageCount)*4));
		fprintf(outFile, "Total Gross: \t\t\t$%7.2lf\n", grandTotalGross);
		fprintf(outFile, "Total FICA: \t\t\t$%7.2lf\n", grandTotalFICA);
		fprintf(outFile, "Total Net: \t\t\t$%7.2lf\n\n\t\t\t\t                                             Page: %d\n", grandTotalNet, pageCount);



		//Close the inFile
		fclose(inFile);

		//Close the outFile
		fclose(outFile);

		return 0;
        

}//End Of Program*I coded until the sun came up. I couldn't hone in the formatting process. Tried and tried and tried and tried....







