#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	fd;
	FILE	*ptr;
	int	count;

	count = 1;
	fd = open("lorem_ipsum.txt", O_RDONLY);
	char	*line;

	while (!feof(ptr))
	{
		line  = get_next_line(fd);
		printf("line read = %s\n", line);
		free(line);
		printf("number of calls : %d", count++);
		ptr++;
	}	
}

// main bonus
