/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/03/08 16:19:18 by btan             ###   ########.fr       */
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
	while ((token[0] != '\0') && env)
	{
		content = (char *) env->content;
		if (!ft_strncmp(token + 6, content, ft_strchr(content, '=') - content))
			break ;
		env = env->next;
	}
	free_strs(args);
	if (env)
	{
		env->content = ft_strdup(cmd + 6);
		return ;
	}
	if (!env && ft_strchr(cmd, '='))
	{
		token = ft_strdup(cmd + 6);
		env = ft_lstnew(token);
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
