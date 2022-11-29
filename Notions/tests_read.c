#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
// point to the fileread frm left to righ
	FILE * fPointer;

// open the file you need to read
	fPointer = fopen("lorem_ipsum.txt", "r");

// store the content of file into an array
	char	singleline[16000];

//run a loop to read the file from begining to end
	while (!feof(fPointer))
	{
// fgets get a line (read until the end of the line)
		fgets(singleline, 16000, fPointer);
// put print out the single line
		puts(singleline);
	}
	fclose(fPointer);
}
