/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:21:46 by btan              #+#    #+#             */
/*   Updated: 2024/03/27 12:58:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	intlen(int n)
//{
//	int	len;
//
//	len = 0;
//	if (n <= 0)
//		len++;
//	while (n != 0)
//	{
//		n /= 10;
//		len++;
//	}
//	return (len);
//}
//
//void	ft_exit(char *str)
//{
//	int		status;
//
//	if (!str)
//		exit(0);
//	if (ft_isdigit(*str) || *str == '-' || *str == '+')
//		status = ft_atoi(str);
//	else
//	{
//		handle_error(str, "INVALID_EXIT");
//		exit(2);
//	}
//	if (str[intlen(status)] && !ft_isdigit(str[intlen(status)]))
//	{
//		handle_error("exit", "TOO_MANY_ARGS");
//		exit(1);
//	}
//	exit(status);
//}

void	ft_exit(char **args)
{
	int	status;

	status = 0;
	printf("exit\n");
	if (!args[1])
		exit(0);
	if (ft_isalnum(args[1][0]) || args[1][0] == '-' || args[1][0] == '+')
	{
		while (args[1][++status])
		{
			if (!ft_isdigit(args[1][status]))
			{
				handle_error(args[1], "INVALID_EXIT");
				get_exit_status(unshift_exitcode(2));
				return ;
			}
		}
		status = ft_atoi(args[1]);
	}
	if (args[2])
	{
		handle_error(args[0], "TOO_MANY_ARGS");
		get_exit_status(unshift_exitcode(1));
		return ;
	}
	exit(status);
}
