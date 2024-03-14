#include "minishell.h"

int	wait_cids(t_arg *args, pid_t *cids)
{
	int	i;
	int	j;
	int	exit_status;

	i = 0;
	j = 0;
	while (!args[i].last)
		i++;
	while (j <= i)
	{
		waitpid(cids[j], &exit_status, 0);
		j++;
	}
	return (exit_status);
}

pid_t	*read_cids(t_arg *args, int *pipe)
{
	int		i;
	int		j;
	pid_t	*cid;
	char	*temp;

	close(pipe[1]);
	i = 0;
	while (i < 100000)
		i++;
	i = 0;
	while (!args[i].last)
		i++;
	temp = NULL;
	cid = ft_calloc(i + 1, sizeof(pid_t));
	j = 0;
	while (j <= i)
	{
		temp = get_next_line(pipe[0]);
		cid[j] = ft_atoi(temp);
		free(temp);
		j++;
	}
	close(pipe[0]);
	return (cid);
}

void	write_cid(pid_t pid, int pipe)
{
	char	*res;

	res = ft_itoa(pid);
	write(pipe, res, ft_strlen(res));
	write(pipe, "\n", 1);
	close(pipe);
	free(res);
}
