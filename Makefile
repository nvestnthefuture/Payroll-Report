PayrollMakeFile: Initialization.o CalculateGross.o CalculateFICA.o NewPage.o
	gcc -o PayrollMakeFile Initialization.o CalculateGross.o CalculateFICA.o NewPage.o

Initialization.o: SourceDirectory/Initialization.c
	gcc -c -o Initialization.o SourceDirectory/Initialization.c

CalculateGross.o: SourceDirectory/CalculateGross.c
	gcc -c -o CalculateGross.o SourceDirectory/CalculateGross.c

CalculateFICA.o: SourceDirectory/CalculateFICA.c
	gcc -c -o CalculateFICA.o SourceDirectory/CalculateFICA.c

NewPage.o: SourceDirectory/NewPage.c
	gcc -c -o NewPage.o SourceDirectory/NewPage.c
