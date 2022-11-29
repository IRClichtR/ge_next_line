#include <stdio.h>

void	testitest()
{
	static int	lol = 1;
	lol++;
	printf("%d\n", lol);
}

int	main(void)
{
	testitest();
	testitest();
	testitest();
	return (0);
}
