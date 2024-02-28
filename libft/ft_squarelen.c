#include "libft.h"

int	ft_squarelen(char **square)
{
	int	i;

	i = 0;
	if (!square)
		return (0);
	while (square[i])
		i++;
	return (i);
}
