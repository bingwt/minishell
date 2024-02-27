#include "libft.h"

int	ft_cubelen(char ***cube)
{
	int	i;

	i = 0;
	if (!cube)
		return (0);
	while (cube[i])
		i++;
	return (i);
}
