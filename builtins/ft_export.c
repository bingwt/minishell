/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/03/26 21:54:04 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_var(char *cmd, t_list **envll)
{
	t_list	*env;

	if (!ft_strchr(cmd, '='))
		env = ft_lstnew(ft_strjoin(cmd, "="));
	else
		env = ft_lstnew(ft_strdup(cmd));
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

static char	*find_end(char *start)
{
	char	*end;

	end = start + 1;
	while (!*end)
		end++;
	return (end);
}

static t_list	*find_token(char *cmd, char *token, t_list *env)
{
	char	*content;
	char	**env_token;
	char	*start;
	char	*end;

	env_token = ft_calloc(3, sizeof(char *));
	while ((token[0] != '\0') && env)
	{
		content = (char *) env->content;
		start = ft_strchr(content, '=');
		end = find_end(start);
		env_token[0] = ft_substr(content, 0, content - start);
		env_token[1] = ft_substr(content, start - content, end - start);
		if (ft_strchr(cmd, '='))
			if (!ft_strcmp(token, env_token[0]))
				break ;
		env = env->next;
	}
	return (env);
}

void	export_var(char *cmd, t_list **envll)
{
	t_list	*env;
	char	**args;
	char	*token;

	env = *envll;
	args = ft_split(cmd, '=');
	token = args[0];
	if (!valid_token(token))
		return ;
	env = find_token(cmd, token, env);
	free_strs(args);
	if (env)
	{
		env->content = ft_strdup(cmd);
		return ;
	}
	if (!env)
		create_var(cmd, envll);
}

void	ft_export(char **args, t_list **envll)
{
	int		i;

	i = 1;
	if (!args[1])
		print_env(envll);
	else
	{
		while (args[i])
			export_var(args[i++], envll);
	}
}
