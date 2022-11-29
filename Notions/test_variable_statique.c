#include <stdio.h>

void	fct(void);

int	main(void)
{
	fct();
	fct();
	return (0);
}
void	fct(void)
{
	static int	i;

	i = 0;
	printf("%d\n", i);
	i+=1;
}
