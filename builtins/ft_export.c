/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/03/17 01:58:57 by btan             ###   ########.fr       */
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

int	valid_token(char *token)
{
	if (ft_isalpha(*token) || *token == '_')
		token++;
	else
	{
		handle_error(token, "NOT_VALID_ID");
		get_exit_status(unshift_exitcode(1));
		return (0);
	}
	while (*token)
	{
		if (!ft_isalnum(*token) && *token != '_')
		{
			handle_error(token, "NOT_VALID_ID");
			get_exit_status(unshift_exitcode(1));
			return (0);
		}
		token++;
	}
	return (1);
}

static t_list	*find_token(char *cmd, char *token, t_list *env)
{
	char	*content;

	while ((token[0] != '\0') && env)
	{
		content = (char *) env->content;
		if (ft_strchr(cmd, '='))
			if (!ft_strncmp(token + 6, content, \
				ft_strchr(content, '=') - content))
				break ;
		env = env->next;
	}
	return (env);
}

void	ft_export(char *cmd, t_list **envll)
{
	t_list	*env;
	char	**args;
	char	*token;

	env = *envll;
	args = ft_split(cmd, '=');
	token = args[0];
	if (!valid_token(token + 6))
		return ;
	env = find_token(cmd, token, env);
	free_strs(args);
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
