/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 14:00:52 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *cmd, t_list **envll)
{
	t_list	*env;

	if (ft_strchr(cmd, '='))
	{
		env = ft_lstnew(ft_strdup(cmd + 7));
		ft_lstadd_back(envll, env);
	}
	else
	{
		env = *envll;
		while (env)
		{
			printf("declare -x %s\n", (char *) env->content);
			env = env->next;
		}
	}
}
