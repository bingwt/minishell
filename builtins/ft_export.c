/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 14:57:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *cmd, t_list **envll)
{
	t_list	*env;
	char	**args;
	char	*content;
	char	*token;

	env = *envll;
	args = ft_split(cmd, '=');
	token = args[0];
	while (env)
	{
		content = (char *) env->content;
		if (!ft_strncmp(token + 7, content, ft_strchr(content, '=') - content))
			break ;
		env = env->next;
	}
	free_strs(args);
	if (env)
	{
		printf("Already exists!\n");
		return ;
	}
	if (!env && ft_strchr(cmd, '='))
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
