/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/03/16 03:59:51 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_var(char *cmd, char *token, t_list **envll)
{
	t_list	*env;

	token = ft_strdup(cmd + 6);
	env = ft_lstnew(token);
	ft_lstadd_back(envll, env);
}

void	print_env(t_list **envll)
{
	t_list	*env;
	char	**var;

	env = *envll;
	while (env)
	{
		var = ft_split((char *) env->content, '=');
		printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		env = env->next;
		free_strs(var);
	}
}

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
		if (ft_strchr(cmd, '='))
			if (!ft_strncmp(token + 6, content, ft_strchr(content, '=') - content))
				break ;
		env = env->next;
	}
	free_strs(args);
	// printf("env: %p\n", env);
	if (env)
	{
		env->content = ft_strdup(cmd + 6);
		return ;
	}
	if (!env && ft_strchr(cmd, '='))
		create_var(cmd, token, envll);
	else if (!ft_strcmp(cmd, "export"))
		print_env(envll);
}
