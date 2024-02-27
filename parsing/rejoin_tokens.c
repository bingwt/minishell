#include "../minishell.h"

static t_arg	init_t_arg(void)
{
	t_arg	arg;

	arg.last = 0;
	arg.in_i = 0;
	arg.out_i = 0;
	arg.cmd_i = 0;
	arg.in = NULL;
	arg.out = NULL;
	arg.cmd = NULL;
	return (arg);
}

t_arg	rejoin_tokens(char ***in)
{
	int		i;
	int		a;
	t_arg	*args;

	i = 0;
	a = 0;
	args = ft_calloc(ft_cubelen(in) + 1, sizeof(t_arg));
	while (in[i])
	{
