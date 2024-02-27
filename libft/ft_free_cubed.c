#include "libft.h"

void	ft_free_cubed(char ****cube)
{
	int	i;

	i = 0;
	if (!cube || !*cube)
		return ;
	while ((*cube)[i])
	{
		ft_free_split(&(*cube)[i]);
		i++;
	}
	free(*cube);
	*cube = NULL;
}
