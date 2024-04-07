/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:13 by btan              #+#    #+#             */
/*   Updated: 2024/04/07 15:18:13 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list *envll)
{
	while (envll)
	{
		printf("%s\n", (char *) envll->content);
		envll = envll->next;
	}
	get_exit_status(unshift_exitcode(0));
}
